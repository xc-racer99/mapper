/*
 *    Copyright 2012, 2013, 2014 Thomas Schöps, Kai Pastor
 *
 *    This file is part of OpenOrienteering.
 *
 *    OpenOrienteering is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    OpenOrienteering is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with OpenOrienteering.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef OPENORIENTEERING_HOME_SCREEN_WIDGET_H
#define OPENORIENTEERING_HOME_SCREEN_WIDGET_H

#include <vector>

#include <QObject>
#include <QPixmap>
#include <QString>
#include <QStringList>
#include <QWidget>

class QAbstractButton;
class QCheckBox;
class QIcon;
class QLabel;
class QListWidget;
class QListWidgetItem;
class QPaintEvent;
class QPushButton;
class QResizeEvent;
class QStackedLayout;

class HomeScreenController;


/**
 * The user interface of the OpenOrienteering Mapper home screen.
 * The OpenOrienteering Mapper home screen is shown when no document is open,
 * for example after the program is started for the first time.
 */
class AbstractHomeScreenWidget : public QWidget
{
Q_OBJECT
public:
	/** Creates a new AbstractHomeScreenWidget for the given controller. */
	AbstractHomeScreenWidget(HomeScreenController* controller, QWidget* parent = nullptr);
	
	/** Destroys the AbstractHomeScreenWidget. */
	virtual ~AbstractHomeScreenWidget();
	
public slots:
	/** Sets the list of recent files. */
	virtual void setRecentFiles(const QStringList& files) = 0;
	
	/** Sets the "checked" state of the control for opening
	 *  the most recently used file on startup. */
	virtual void setOpenMRUFileChecked(bool state) = 0;
	
	/** Sets the text of the the tip-of-the-day. */
	virtual void setTipOfTheDay(const QString& text) = 0;
	
	/** Sets the visiblity of the tip-of-the-day, and
	 *  sets the "checked" state of the control for displaying the tip. */
	virtual void setTipsVisible(bool state) = 0;
	
protected:
	/** Returns a QLabel for displaying a headline in the home screen. */
	QLabel* makeHeadline(const QString& text, QWidget* parent = nullptr) const;
	
	/** Returns a button with the given text
	 *  for triggering a top level activity in the home screen.
	 *  There will be no icon or a default icon. */
	QAbstractButton* makeButton(const QString& text, QWidget* parent = nullptr) const;
	
	/** Returns a button with the given text and icon
	 *  for triggering a top level activity in the home screen. */
	QAbstractButton* makeButton(const QString& text, const QIcon& icon, QWidget* parent = nullptr) const;
	
	
	HomeScreenController* controller;
};


/**
 * Implementation of AbstractHomeScreenWidget for desktop PCs.
 */
class HomeScreenWidgetDesktop : public AbstractHomeScreenWidget
{
Q_OBJECT
public:
	/** Creates a new HomeScreenWidgetDesktop for the given controller. */
	HomeScreenWidgetDesktop(HomeScreenController* controller, QWidget* parent = nullptr);
	
	/** Destroys the HomeScreenWidgetDesktop. */
	virtual ~HomeScreenWidgetDesktop();
	
public slots:
	/** Sets the list of recent files. */
	virtual void setRecentFiles(const QStringList& files);
	
	/** Sets the "checked" state of the control for opening
	 *  the most recently used file on startup. */
	virtual void setOpenMRUFileChecked(bool state);
	
	/** Sets the text of the the tip-of-the-day. */
	virtual void setTipOfTheDay(const QString& text);
	
	/** Sets the visiblity of the tip-of-the-day, and
	 *  sets the "checked" state of the control for displaying the tip. */
	virtual void setTipsVisible(bool state);
	
protected slots:
	/** Opens a file when its is list item is clicked. */
	void recentFileClicked(QListWidgetItem* item);
	
protected:
	/** Draws the home screen background when a paint event occurs. */
	virtual void paintEvent(QPaintEvent* event);
	
	/** Creates the activities widget. */
	QWidget* makeMenuWidget(HomeScreenController* controller, QWidget* parent = nullptr);
	
	/** Creates the recent files widget. */
	QWidget* makeRecentFilesWidget(HomeScreenController* controller, QWidget* parent = nullptr);
	
	/** Creates the tip-of-the-day widget. */
	QWidget* makeTipsWidget(HomeScreenController* controller, QWidget* parent = nullptr);
	
	
	QListWidget* recent_files_list;
	QCheckBox* open_mru_file_check;
	QLabel* tips_label;
	QCheckBox* tips_check;
	std::vector<QWidget*> tips_children;
};


/**
 * Implementation of AbstractHomeScreenWidget for mobile devices.
 */
class HomeScreenWidgetMobile : public AbstractHomeScreenWidget
{
Q_OBJECT
public:
	/** Creates a new HomeScreenWidgetMobile for the given controller. */
	HomeScreenWidgetMobile(HomeScreenController* controller, QWidget* parent = nullptr);
	
	/** Destroys the HomeScreenWidgetMobile. */
	virtual ~HomeScreenWidgetMobile();
	
public slots:
	/** Sets the list of recent files. */
	virtual void setRecentFiles(const QStringList& files);
	
	/** Sets the "checked" state of the control for opening
	 *  the most recently used file on startup. */
	virtual void setOpenMRUFileChecked(bool state);
	
	/** Sets the text of the the tip-of-the-day. */
	virtual void setTipOfTheDay(const QString& text);
	
	/** Sets the visiblity of the tip-of-the-day, and
	 *  sets the "checked" state of the control for displaying the tip. */
	virtual void setTipsVisible(bool state);
	
	/** Adds the examples to the list of files
	 *  if they are not already there. */
	void showExamples();
	
	/** Shows the settings dialog, adjusted for small screens. */
	void showSettings();
	
protected slots:
	/** Opens a file when its is list item is clicked. */
	void fileClicked(QListWidgetItem* item);
	
protected:
	/** Triggers title image adjustment on resize events. */
	virtual void resizeEvent(QResizeEvent* event);
	
	/** Resizes the title image to fit both the labels width and height */
	void adjustTitlePixmapSize();
	
	/** Creates the file list widget. */
	QWidget* makeFileListWidget(HomeScreenController* controller, QWidget* parent = nullptr);
	
	/** Iterates over all files at the given path and adds all map files to the list */
	void addFilesToFileList(QListWidget* file_list, const QString& path);
	
private:
	QPixmap title_pixmap;
	QLabel* title_label;
	QStackedLayout* file_list_stack;
	QListWidget* file_list;
	QPushButton* examples_button;
};

#endif
