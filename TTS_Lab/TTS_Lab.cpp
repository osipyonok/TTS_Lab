#include "TTS_Lab.h"


TTS_Lab::TTS_Lab(QWidget *parent)
	: QMainWindow(parent)
{
	function<void(bool, bool)> init = [this](bool displayToolBar, bool displayStatusBar) { // yes, i just want to use functional
		ui.setupUi(this);
		if(!displayToolBar) ui.mainToolBar->close();
		if(!displayStatusBar) ui.statusBar->close();
		this->setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);

		connect(ui.runTTSButton, SIGNAL(clicked(bool)), this, SLOT(runButtonPressed(bool)));
		connect(&runTTSWatcher, SIGNAL(finished()), this, SLOT(play()));
		connect(ui.volumeSlider, SIGNAL(valueChanged(int)), &player, SLOT(setVolume(int)));
		connect(ui.volumeSlider, SIGNAL(valueChanged(int)), ui.volumeLabel, SLOT(setNum(int)));
		connect(ui.stopPlayingButton, SIGNAL(clicked(bool)), &player, SLOT(stop()));
		connect(ui.exitButton, SIGNAL(clicked(bool)), this, SLOT(close(bool)));
	};
	
	init(false, false);
}


void TTS_Lab::runButtonPressed(bool) {
	QString textToSpeech = ui.textField->toPlainText();
	runTTSAsync = QtConcurrent::run(runTTSWrapper, tts, textToSpeech);
	runTTSWatcher.setFuture(runTTSAsync);	
}


QString runTTSWrapper(TextToSpeechEngine & tts, QString & text) {
	return tts.speechText(text);
}


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
	QtConcurrent::run(QApplication::quit);
}
