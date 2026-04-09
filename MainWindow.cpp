#include "MainWindow.h"
#include <QtCore>
#include <QtWidgets>

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	this->setWindowTitle("Qforensics : : Digital Forensics OSS");

	this->setCorner(Qt::Corner::TopLeftCorner, Qt::DockWidgetArea::LeftDockWidgetArea);
	this->setCorner(Qt::Corner::BottomLeftCorner, Qt::DockWidgetArea::LeftDockWidgetArea);
	this->setCorner(Qt::Corner::TopRightCorner, Qt::DockWidgetArea::RightDockWidgetArea);
	this->setCorner(Qt::Corner::BottomRightCorner, Qt::DockWidgetArea::RightDockWidgetArea);

	auto evidenceTreeDock = new QDockWidget("파일 목록", this);
	auto propsDock = new QDockWidget("속성", this);
}

MainWindow::~MainWindow()
{
}

