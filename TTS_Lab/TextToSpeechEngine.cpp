#include "TextToSpeechEngine.h"


TextToSpeechEngine::TextToSpeechEngine()
{
	init();
}


TextToSpeechEngine::~TextToSpeechEngine()
{
/*	QString tempDirPath = QString::fromUtf8(R"(C:\VS\TTS_Lab\TTS_Lab\patterns\temp\)");
	QDir tempDir(tempDirPath);
	tempDir.setNameFilters(QStringList() << "*.*");
	tempDir.setFilter(QDir::Files);
	foreach(QString tempFile, tempDir.entryList())
	{
		tempDir.remove(tempFile);
	}*/
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


QString TextToSpeechEngine::speechText(QString text) {
	prepare(text);
	auto words = text.split(" ");
	vector<QString> files;

	for (QString word : words) {
		StringHash sHash(word);
		int len = word.length();
		splitWord(word, sHash, 0, files);
		files.push_back(u8"C:\\VS\\TTS_Lab\\TTS_Lab\\patterns\\_.mp3");
	}
	files.pop_back();

	QString command = "";
	bool isFirst = true;
	for (QString file : files) {
		if (isFirst) {
			isFirst = false;
		} else {
			command += "+";
		}

		command += "\"";
		command += file;
		command += "\"";
	}

	QString newFileName = QString("temp\\") + randomString(16) + QString(".mp3");
	QString pathToResult = QString::fromUtf8("\"C:\\VS\\TTS_Lab\\TTS_Lab\\patterns\\") + newFileName + "\"";
	command += QString(" ") + pathToResult;
	for (auto & ch : command) if (ch == '/') ch = '\\';
	command = QString("copy /b ") + command;

	QString pathToBat = QString::fromUtf8(u8"C:\\VS\\TTS_Lab\\TTS_Lab\\run.bat");
	QFile bat(pathToBat);
	if (bat.open(QIODevice::ReadWrite)) {
		QTextStream stream(&bat);
		stream.setCodec("Windows-1251");
		stream << QString("chcp 1251") << endl;
		stream << command << endl;
		stream.flush();
	}
	bat.close();

	int res = QProcess::execute(pathToBat);
	QFile::remove(pathToBat);

	return QString::fromUtf8(R"(C:\VS\TTS_Lab\TTS_Lab\patterns\)") + newFileName;
}


void TextToSpeechEngine::init() {
	QDir dir(patternsDir);
	QDirIterator it(patternsDir, QStringList() << "*.mp3", QDir::Files);
	while (it.hasNext())
	{
		QString filePath = it.next();
		QFileInfo fileInfo(filePath);
		qDebug() << fileInfo.suffix() << endl;
		QString file = filePath.remove(patternsDir);
		file = file.remove(file.left(1));

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
