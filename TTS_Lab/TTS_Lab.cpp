#include "TTS_Lab.h"

#include <QDir>
#include <QDebug>
#include <QFileDialog>
#include <QSettings>
#include <QStringList>
#include <QMessageBox>
#include <QTemporaryDir>

namespace
{
    const auto CACHED_PATTERNS_PATH_KEY = QStringLiteral("CachedPattersPath");

    std::unique_ptr<QSettings> _GetSettings()
    {
        return std::make_unique<QSettings>("KNU", "TTS LAB");
    }
}

TTS_Lab::TTS_Lab(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.mainToolBar->close();
    ui.statusBar->close();
    setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);

    auto p_settings = _GetSettings();
    auto previously_used_path = p_settings->value(CACHED_PATTERNS_PATH_KEY);
    if (previously_used_path.isValid())
        m_selected_patterns_dir = previously_used_path.toString();

    updateToPattersFolder();

    [[maybe_unused]]
    bool is_connected = false;
    is_connected = connect(ui.runTTSButton, SIGNAL(clicked(bool)), this, SLOT(runButtonPressed(bool)));
    Q_ASSERT(is_connected);
    is_connected = connect(&runTTSWatcher, SIGNAL(finished()), this, SLOT(play()));
    Q_ASSERT(is_connected);
    is_connected = connect(ui.volumeSlider, SIGNAL(valueChanged(int)), &player, SLOT(setVolume(int)));
    Q_ASSERT(is_connected);
    is_connected = connect(ui.volumeSlider, SIGNAL(valueChanged(int)), ui.volumeLabel, SLOT(setNum(int)));
    Q_ASSERT(is_connected);
    is_connected = connect(ui.stopPlayingButton, SIGNAL(clicked(bool)), &player, SLOT(stop()));
    Q_ASSERT(is_connected);
    is_connected = connect(ui.exitButton, SIGNAL(clicked(bool)), this, SLOT(close(bool)));
    Q_ASSERT(is_connected);
    is_connected = connect(ui.selectFolderButton, &QAbstractButton::clicked, this, [this]
    {
        auto patterns_dir_path = QFileDialog::getExistingDirectory(this,
                                                                   QString::fromUtf8(u8"Виберіть папку з паттернами"), 
                                                                   m_selected_patterns_dir);
        if (patterns_dir_path.isEmpty())
        {
            return;
        }

        m_selected_patterns_dir = patterns_dir_path;
        auto p_settings = _GetSettings();
        p_settings->setValue(CACHED_PATTERNS_PATH_KEY, m_selected_patterns_dir);
        mp_patterns_copy = std::make_unique<QTemporaryDir>();
        qDebug() << "Used internal patters storage:" << mp_patterns_copy->path();
        QDir patterns_dir(patterns_dir_path);
        for (const auto& file : patterns_dir.entryList(QDir::Files))
        {
            QFile::copy(patterns_dir.absoluteFilePath(file), mp_patterns_copy->filePath(file));
        }
        updateToPattersFolder();
    });
    Q_ASSERT(is_connected);
}


void TTS_Lab::runButtonPressed(bool) {
    QString textToSpeech = ui.textField->toPlainText();
    runTTSAsync = QtConcurrent::run(runTTSWrapper, std::ref(*mp_tts), textToSpeech);
    runTTSWatcher.setFuture(runTTSAsync);    
}


QString runTTSWrapper(TextToSpeechEngine & tts, QString & text) {
    return tts.speechText(text);
}


TTS_Lab::~TTS_Lab() = default;

void TTS_Lab::play(QString file)
{
    if (file == "") {
        play(this->runTTSAsync.result());
        runTTSAsync = QFuture<QString>();
    } else {
        player.stop();
        player.setPlaylist(Q_NULLPTR);
        player.setVolume(ui.volumeSlider->value());
        player.setMedia(QUrl::fromLocalFile(file));
        player.play();
    }
}


void TTS_Lab::close(bool)
{
    QApplication::quit();
}

void TTS_Lab::updateToPattersFolder()
{
    player.stop();
    mp_tts.reset();
    QDir dir(m_selected_patterns_dir);
    const bool exists = dir.exists();
    if (exists)
    {
        ui.runTTSButton->setEnabled(true);
        ui.stopPlayingButton->setEnabled(true);
        ui.patternsFolder->setText(dir.absolutePath());
        mp_tts = std::make_unique<TextToSpeechEngine>(dir.absolutePath());
    }
    else
    {
        ui.runTTSButton->setEnabled(false);
        ui.stopPlayingButton->setEnabled(false);
        ui.patternsFolder->setText("");
    }
}
