#pragma once
#include <qstring.h>
#include <qdiriterator.h>
#include <qdir.h>
#include <qfile.h>
#include <qdebug.h>
#include "StringHash.h"
#include <map>
#include <qprocess.h>
#include <iostream>

using namespace std;

const QString pathToTemp = QString::fromUtf8(R"(C:\VS\TTS_Lab\TTS_Lab\Temp)");
const QString patternsDir = "patterns";


class TextToSpeechEngine
{
public:
	TextToSpeechEngine();
	~TextToSpeechEngine();
	QString speechText(QString text);
	void splitWord(const QString & word, StringHash & sHash, int pos, vector<QString> & files);
	
private:
	map<long long, pair<QString,QString>> patterns;

	void init();
	static void prepare(QString & s);
};

namespace {
	const QString alpha = "qwertyuiopasdfghjklzxcvbnm1234567890QWERTYUIOPASDFGHJKLZXCVBNM_";
	inline QString randomString(uint len = 16) {
		QString res;
		while (len--) res += alpha[(alpha.length() + ((int)time(0) + rand()) % alpha.length()) % alpha.length()];
		return res;
	}
};

