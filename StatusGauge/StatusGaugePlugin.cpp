// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=* 
// ** Copyright UCAR (c) 1990 - 2016                                         
// ** University Corporation for Atmospheric Research (UCAR)                 
// ** National Center for Atmospheric Research (NCAR)                        
// ** Boulder, Colorado, USA                                                 
// ** BSD licence applies - redistribution and use in source and binary      
// ** forms, with or without modification, are permitted provided that       
// ** the following conditions are met:                                      
// ** 1) If the software is modified to produce derivative works,            
// ** such modified software should be clearly marked, so as not             
// ** to confuse it with the version available from UCAR.                    
// ** 2) Redistributions of source code must retain the above copyright      
// ** notice, this list of conditions and the following disclaimer.          
// ** 3) Redistributions in binary form must reproduce the above copyright   
// ** notice, this list of conditions and the following disclaimer in the    
// ** documentation and/or other materials provided with the distribution.   
// ** 4) Neither the name of UCAR nor the names of its contributors,         
// ** if any, may be used to endorse or promote products derived from        
// ** this software without specific prior written permission.               
// ** DISCLAIMER: THIS SOFTWARE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS  
// ** OR IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED      
// ** WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.    
// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=* 
#include "StatusGaugePlugin.h"
#include "StatusGauge.h"

StatusGaugePlugin::StatusGaugePlugin(QObject *parent):
QObject(parent)
{
	initialized = false;
}

void
StatusGaugePlugin::initialize(QDesignerFormEditorInterface *core)
{
	if (initialized)
		return;

	initialized = true;
}

bool 
StatusGaugePlugin::isInitialized() const
{
	return initialized;
}

QWidget*
StatusGaugePlugin::createWidget(QWidget *parent)
{
	StatusGauge* p = new StatusGauge(parent);
	return p;
}

QString 
StatusGaugePlugin::name() const
{
	return "StatusGauge";
}

QString 
StatusGaugePlugin::codeTemplate() const
{
	return "";
}

QString 
StatusGaugePlugin::group() const
{
	return "QtToolbox";
}

QIcon 
StatusGaugePlugin::icon() const
{
	return QIcon();
}

QString 
StatusGaugePlugin::toolTip() const
{
	return "";
}

QString StatusGaugePlugin::whatsThis() const
{
	return "";
}

bool StatusGaugePlugin::isContainer() const
{
	return false;
}


QString 
StatusGaugePlugin::domXml() const
{
	return "<widget class=\"StatusGauge\" name=\"statusGauge\">\n"
		" <property name=\"geometry\">\n"
		"  <rect>\n"
		"   <x>0</x>\n"
		"   <y>0</y>\n"
		"   <width>20</width>\n"
		"   <height>60</height>\n"
		"  </rect>\n"
		" </property>\n"
		"</widget>\n";
}

QString 
StatusGaugePlugin::includeFile() const
{
	return "StatusGauge.h";
}

