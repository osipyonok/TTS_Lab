#include "TextToSpeechEngine.h"

#include <QByteArray>
#include <QDataStream>
#include <QTemporaryDir>
#include <QUuid>

namespace
{
    const auto CUSTOM_SILENCE_NAME = QStringLiteral("_.mp3");

    auto _GetRandomString()
    {
        return QUuid::createUuid().toString(QUuid::StringFormat::WithoutBraces);
    }
}

TextToSpeechEngine::TextToSpeechEngine(const QString& i_patterns)
    : m_patterns_location(i_patterns)
    , mp_working_dir(std::make_unique<QTemporaryDir>())
{
    init();
}


TextToSpeechEngine::~TextToSpeechEngine()
{
}


void TextToSpeechEngine::splitWord(const QString & word, StringHash & sHash, int pos, vector<QString> & files) {
    if (word.isNull() || word.isEmpty()) return;
    if (pos >= word.length()) return;

    for (int i = word.length() - 1; i >= pos; --i) {
        long long cur = sHash.str(pos, i);
        if (patterns.find(cur) != patterns.end()) {
            files.push_back(patterns[cur].second);
            splitWord(word, sHash, i + 1, files);
            return;
        }
    }
    qDebug() << "There is a problem with word" << word << " at index " << pos << endl;
    splitWord(word, sHash, pos + 1, files);
}

QString TextToSpeechEngine::getSilencePath()
{
    QDir dir(m_patterns_location);
    QFileInfo file(dir.absoluteFilePath(CUSTOM_SILENCE_NAME));
    if (file.exists())
        return file.absolutePath();

    return QStringLiteral(R"(:/DefaultSegments/silence.mp3)");
}


QString TextToSpeechEngine::speechText(QString text) {
    prepare(text);
    auto words = text.split(" ");
    std::vector<QString> files;
    
    const auto path_to_silence = getSilencePath();
    for (QString word : words) {
        files.push_back(path_to_silence);
        StringHash sHash(word);
        int len = word.length();
        splitWord(word, sHash, 0, files);
    }

    QString pathToResult = mp_working_dir->filePath(_GetRandomString() + QString(".mp3"));
    QFile resultFile(pathToResult);
    resultFile.open(QIODevice::ReadWrite);
    QByteArray mergedFiles;
    QDataStream mergedStream(&mergedFiles, QIODevice::ReadWrite);
    for (const auto& file_path : files)
    {
        QFile file(file_path);
        auto ok = file.open(QIODevice::ReadOnly);
        Q_ASSERT(ok);
        if (!ok)
            continue;
        mergedStream << file.readAll();
    }

    resultFile.write(mergedFiles);
    resultFile.flush();
    resultFile.close();

    return pathToResult;
}


void TextToSpeechEngine::init() {
    QDir dir(m_patterns_location);
    QDirIterator it(dir.absolutePath(), QStringList() << "*.mp3", QDir::Files);
    while (it.hasNext())
    {
        QString filePath = it.next();
        QFileInfo fileInfo(filePath);
        qDebug() << fileInfo.suffix() << endl;

        QString word = fileInfo.fileName().remove(QString(".") + fileInfo.suffix());
        StringHash sHash(word);

        patterns[sHash.str()] = make_pair(word, fileInfo.absoluteFilePath());
    }
}


void TextToSpeechEngine::prepare(QString & s)
{
    s = s.toLower();
    s = s.trimmed();
    s = s.remove("'");
    s = s.remove("`");
    s = s.remove(QRegExp("[.!?\\-\,/\[\]\(\)]"));
    s = s.replace(QRegExp("\\s+"), " ");
    s = s.replace(QString("@"), QString::fromUtf8(u8"собака"));
}
