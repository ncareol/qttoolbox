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
/*
 * BscanMainWindow.h
 *
 *  Created on: Sep 23, 2009
 *      Author: burghart
 */

#ifndef BSCANMAINWINDOW_H_
#define BSCANMAINWINDOW_H_

#include <vector>
#include "BscanWidget.h"
#include "GateLimitDialog.h"
#include "TimeSpanDialog.h"
#include "ui_Bscan.h"

#include "QtConfig.h"

#include <QFileDialog>
#include <QLabel>
#include <QMainWindow>
#include <QObject>
#include <QPrinter>

class BscanGraphicsScene;
class BscanRay;

/**
 * @brief Main window class for a bscan display.
 * Data are added to the display via signals to the addRay() slot.
 */
class BscanMainWindow : public QMainWindow {
    Q_OBJECT
public:
    BscanMainWindow(QtConfig &config);
    virtual ~BscanMainWindow();
    bool isPaused() const;
public slots:
    /**
     * @brief Add a new plot to the model.  This creates a 
     * BscanGraphicsView/BscanGraphicsScene pair and adds the view to 
     * the UI's plot frame.
     */
    void addNewPlot();
    /**
     * @brief Remove the plot with the given index.
     * @param plotIndex the index of the plot to be removed
     */
    void removePlot(unsigned int plotIndex);
    /**
     * @brief Remove the last (bottom) plot from the model.
     */
    void removeLastPlot();
    /**
     * @brief Print the UI's plot frame, popping up a dialog for selecting the
     * print device. The image will be printed as large as possible on the
     * page while maintaining the correct aspect ratio 
     */
    void print();
    /**
     * @brief Save the UI's plot frame as an image, popping up a dialog for
     * choosing the file name.
     */
    void saveImage();
    /**
     * @brief Set the paused state for the model.
     * @param state the new paused state
     */
    void setPaused(bool state);
    /**
     * @brief Pause the display(s).
     */
    void pause();
    /**
     * @brief Unpause the display(s).
     */
    void unpause();
    /**
     * @brief Set zoom level, where a zoom of 1 fits the entire scene on the display.
     * @param zoom the zoom factor
     */
    void setZoom(float zoom);
    /**
     * @brief Slot which accepts an incoming ray for addition to the display.
     * @param ray the BscanRay to be added to the display
     */
    void addRay(const BscanRay & ray);
    /**
     * @brief Toggle the "pointing up" state of our scenes.
     */
    void togglePointingUp();
protected slots:
    void _showLocAndData(double time, unsigned int gate, const QString &varName, 
            float value);
    /*
     * Slots which are automatically connected to actions in the UI
     */
    void on_actionPrint_triggered() { print(); }
    void on_actionSaveImage_triggered() { saveImage(); }
    void on_actionAddPlot_triggered() { addNewPlot(); }
    void on_actionRemovePlot_triggered() { removeLastPlot(); }
    void on_actionPause_triggered() { pause(); }
    void on_actionUnpause_triggered() { unpause(); }
    void on_actionZoom_100_triggered() { setZoom(1.00); }
    void on_actionZoom_150_triggered() { setZoom(1.50); }
    void on_actionZoom_200_triggered() { setZoom(2.00); }
    void on_actionZoom_300_triggered() { setZoom(3.00); }
    void on_actionQuit_triggered() { qApp->closeAllWindows(); }
    void on_actionSetGateRange_triggered() { _glDialog->exec(); }
    void on_actionSetTimeSpan_triggered() { _tsDialog->exec(); }
    void on_actionTogglePointingUp_triggered() { togglePointingUp(); }
private:
    BscanGraphicsView* _view(int index) const { return _bscans[index]->view(); }
    BscanGraphicsScene* _scene(int index) const { return _view(index)->scene(); }
    unsigned int _nBscans() const { return _bscans.size(); }
    // Make a scene name using the give index, e.g., "bscan_0" for index 0
    static std::string _makeSceneName(unsigned int index);
private:
    Ui::Bscan _ui;
    GateLimitDialog *_glDialog;
    TimeSpanDialog *_tsDialog;
    QFileDialog *_saveImageDialog;
    std::vector<BscanWidget *> _bscans;
    // Put all of our BscanWidget instances into a BscanWidgetGroup, so they 
    // share gate limits, time limits, pause state, zoom state, and 
    // horizontal/vertical scroll settings
    BscanWidgetGroup _bwGroup;
    // If a printer is chosen via the dialog popped up during print(), keep
    // it around so that the user will get the same choice by default next
    // time.
    QPrinter _printer;
    QLabel _mousePosLabel;
  QtConfig &_config;
};

#endif /* BSCANMAINWINDOW_H_ */
