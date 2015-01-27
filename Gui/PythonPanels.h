//  Natron
//
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
/*
 * Created by Alexandre GAUTHIER-FOICHAT on 6/1/2012.
 * contact: immarespond at gmail dot com
 *
 */


#ifndef PYTHONPANELS_H
#define PYTHONPANELS_H

#include <Python.h>

#include <QDialog>

#include "Global/Macros.h"

#include "Engine/NodeWrapper.h"
#include "Engine/Knob.h"

class GuiApp;
class Gui;
class TabWidget;
class Param;

struct DialogParamHolderPrivate;
class DialogParamHolder : public NamedKnobHolder
{
    
public:
    
    DialogParamHolder(const std::string& uniqueID,AppInstance* app);
    
    virtual ~DialogParamHolder();
    
    virtual std::string getScriptName_mt_safe() const OVERRIDE FINAL;
    
    void setParamChangedCallback(const std::string& callback);
    
    
private:
    
    virtual void initializeKnobs() OVERRIDE FINAL {}
    
    virtual void evaluate(KnobI* /*knob*/,bool /*isSignificant*/,Natron::ValueChangedReasonEnum /*reason*/) OVERRIDE FINAL {}
    
    virtual void onKnobValueChanged(KnobI* /*k*/,
                                    Natron::ValueChangedReasonEnum /*reason*/,
                                    SequenceTime /*time*/,
                                    bool /*originatedFromMainThread*/) OVERRIDE FINAL;

    boost::scoped_ptr<DialogParamHolderPrivate> _imp;
};




struct PyModalDialogPrivate;
class PyModalDialog : public QDialog, public UserParamHolder
{
    Q_OBJECT
    
public:
    
    PyModalDialog(Gui* gui);
    
    virtual ~PyModalDialog();
    
    Param* getParam(const std::string& scriptName) const;
        
    void setParamChangedCallback(const std::string& callback);
    
    void insertWidget(int index, QWidget* widget);
    
    void addWidget(QWidget* widget);
    
private:
    
    boost::scoped_ptr<PyModalDialogPrivate> _imp;

    
};


struct PyPanelPrivate;
class PyPanel : public QWidget, public UserParamHolder
{
    Q_OBJECT
    
public:
    
    PyPanel(const std::string& label,bool useUserParameters,GuiApp* app);
    
    virtual ~PyPanel();
        
    std::string save_serialization_thread() const;
    
    virtual void restore(const std::string& /*data*/) {}
    
    void setLabel(const std::string& label);
    
    std::string getLabel() const;
    
    Param* getParam(const std::string& scriptName) const;
    
    std::list<Param*> getParams() const;
    
    void setParamChangedCallback(const std::string& callback);
    
    void insertWidget(int index, QWidget* widget);
    
    void addWidget(QWidget* widget);
    
protected:
    
    virtual std::string save() { return std::string(); }
    
    void onUserDataChanged();
    
private:
    
    boost::scoped_ptr<PyPanelPrivate> _imp;
    
};


class PyTabWidget {

    TabWidget* _tab;
    
public :
    
    PyTabWidget(TabWidget* pane);
    
    ~PyTabWidget();
    
    TabWidget* getInternalTabWidget() const {
        return _tab;
    }
    
    bool appendTab(QWidget* tab);
    
    void insertTab(int index,QWidget* tab);
    
    void removeTab(QWidget* tab);
    
    void removeTab(int index);
    
    void closeTab(int index);
    
    std::string getTabName(int index) const;
    
    int count();
    
    QWidget* currentWidget();
    
    void setCurrentIndex(int index);
    
    int getCurrentIndex() const;
    
    PyTabWidget* splitHorizontally();
    
    PyTabWidget* splitVertically();
    
    void closePane();
    
    void floatPane();
    
    void setNextTabCurrent();
    
    void floatCurrentTab();
    
    void closeCurrentTab();
    
    std::string getScriptName() const;
};

#endif // PYTHONPANELS_H
