#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TTS_Lab.h"
#include "TextToSpeechEngine.h"
#include <qstring.h>
#include <QtConcurrent\qtconcurrentrun.h>
#include <QtConcurrent\qtconcurrentmap.h>
#include <qfuturewatcher.h>
#include <qmediaplayer.h>
#include <qurl.h>
#include <functional>
#include <memory>

class QTemporaryDir;

class TTS_Lab : public QMainWindow
{
    Q_OBJECT

public:
    TTS_Lab(QWidget *parent = Q_NULLPTR);
    ~TTS_Lab() override;

public slots:
    void runButtonPressed(bool);
    void play(QString file = "");
    void close(bool);
    void updateToPattersFolder();

private:
    QString m_selected_patterns_dir;
    Ui::TTS_LabClass ui;
    std::unique_ptr<TextToSpeechEngine> mp_tts;
    std::unique_ptr<QTemporaryDir> mp_patterns_copy;
    QFuture<QString> runTTSAsync;
    QFutureWatcher<QString> runTTSWatcher;
    QMediaPlayer player;
};

QString runTTSWrapper(TextToSpeechEngine & tts, QString & text);
