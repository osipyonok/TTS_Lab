#pragma once
#include <qstring.h>
#include <qdiriterator.h>
#include <qdir.h>
#include <qfile.h>
#include <qdebug.h>
#include "StringHash.h"
#include <map>
#include <iostream>
#include <memory>

class QTemporaryDir;

class TextToSpeechEngine
{
public:
    TextToSpeechEngine(const QString& i_patterns);
    ~TextToSpeechEngine();
    QString speechText(QString text);
    
private:
    std::map<long long, pair<QString,QString>> patterns;
    QDir m_patterns_location;
    std::unique_ptr<QTemporaryDir> mp_working_dir;

    void init();
    static void prepare(QString & s);
    void splitWord(const QString & word, StringHash & sHash, int pos, std::vector<QString> & files);
    QString getSilencePath();
};
