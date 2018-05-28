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

class TTS_Lab : public QMainWindow
{
	Q_OBJECT

public:
	TTS_Lab(QWidget *parent = Q_NULLPTR);

public slots:
	void runButtonPressed(bool);
	void play(QString file = "");
	void close(bool);

private:
	Ui::TTS_LabClass ui;
	TextToSpeechEngine tts;
	QFuture<QString> runTTSAsync;
	QFutureWatcher<QString> runTTSWatcher;
	QMediaPlayer player;
};

QString runTTSWrapper(TextToSpeechEngine & tts, QString & text);
