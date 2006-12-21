#ifndef TWOKNOBS_H
#define TWOKNOBS_H

#include "TwoKnobsBase.h"
#include <string>

/// A plugin widget which combines two Knob plugins. Signals
/// are generated when the knob values change.
class QT_WIDGET_PLUGIN_EXPORT TwoKnobs : public TwoKnobsBase
{
    Q_OBJECT

public:
    TwoKnobs( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~TwoKnobs();

    void setTitles(std::string titleKnobOne, std::string titleKnobTwo);
    void setRanges(double knobOneMin, double knobOneMax,
       double knobTwoMin, double knobTwoMax);
	void setValues(double val1, double val2);
	void setScaleMaxMajor(int knobNum, int ticks);
	void setScaleMaxMinor(int knobNum, int ticks);

public slots:
    virtual void knobOneChangedSlot(double);
    virtual void knobTwoChangedSlot(double);

signals:
    void knobOneChanged(double);
    void knobTwoChanged(double);

};

#endif // TWOKNOBS_H
