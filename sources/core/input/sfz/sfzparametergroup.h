#ifndef SFZPARAMETERGROUP_H
#define SFZPARAMETERGROUP_H

#include "sfzparameter.h"
#include "basetypes.h"
class SoundfontManager;

class SfzParameterGroup
{
public:
    // Chargement
    SfzParameterGroup() {}
    void operator << (SfzParameter param) { _listeParam << param; }

    // Décodage
    void decode(SoundfontManager * sf2, EltID idElt) const;
    QList<int> getSampleIndex(SoundfontManager * sf2, EltID idElt, QString pathSfz) const;
    void adaptOffsets(int startLoop, int endLoop, int length);
    void adjustStereoVolumeAndCorrection(QString path, int defaultCorrection);
    bool sampleValid(QString path) const;
    void checkFilter();
    void adjustVolume(double offset);
    void adjustCorrection(int offset, int defaultCorrection);
    void removeOpCode(SfzParameter::OpCode opcode)
    {
        for (int i = _listeParam.size() - 1; i >= 0; i--)
            if (_listeParam.at(i).getOpCode() == opcode)
                _listeParam.removeAt(i);
    }

    // Lecture
    bool isDefined(SfzParameter::OpCode opcode) const
    {
        bool bRet = false;
        for (int i = 0; i < _listeParam.size(); i++)
            if (_listeParam.at(i).getOpCode() == opcode)
                bRet = true;
        return bRet;
    }
    int getIntValue(SfzParameter::OpCode opcode) const
    {
        int iRet = 0;
        for (int i = 0; i < _listeParam.size(); i++)
            if (_listeParam.at(i).getOpCode() == opcode)
                iRet = _listeParam.at(i).getIntValue();
        return iRet;
    }
    double getDoubleValue(SfzParameter::OpCode opcode) const
    {
        double dRet = 0;
        for (int i = 0; i < _listeParam.size(); i++)
            if (_listeParam.at(i).getOpCode() == opcode)
                dRet = _listeParam.at(i).getDoubleValue();
        return dRet;
    }
    QString getStrValue(SfzParameter::OpCode opcode) const
    {
        QString strRet = "";
        for (int i = 0; i < _listeParam.size(); i++)
            if (_listeParam.at(i).getOpCode() == opcode)
                strRet = _listeParam.at(i).getStringValue();
        return strRet;
    }
    static double percentToDB(double percent) { return log10(percent / 100.) * 20.; }

private:
    QList<SfzParameter> _listeParam;
    static QStringList getFullPath(QString base, QStringList directories);
    static double log2m1200(double value) { return 1200. * qLn(value) / 0.69314718056 /* ln(2) */; }
    static double d1200e2(int value) { return qPow(2., value / 1200.); }
    static void addSeconds(double value, AttributeType champ, SoundfontManager * sf2, EltID id);
    void getKeynumValues(double &baseValue, int &keynum, SfzParameter::OpCode opCodeKeynum, SfzParameter::OpCode opCodeBase) const;
    static QString getName(QString name, int maxCharacters, int suffixNumber, QString suffix = "");
};

#endif // SFZPARAMETERGROUP_H
