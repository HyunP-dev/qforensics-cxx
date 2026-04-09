#include "MainWindow.h"
#include "widgets/DynamicContainer.h"
#include "models/EvidenceTreeModel.h"

#include <QtCore>
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this);

    this->setWindowTitle("Qforensics : : Digital Forensics OSS");

    this->setCorner(Qt::Corner::TopLeftCorner, Qt::DockWidgetArea::LeftDockWidgetArea);
    this->setCorner(Qt::Corner::BottomLeftCorner, Qt::DockWidgetArea::LeftDockWidgetArea);
    this->setCorner(Qt::Corner::TopRightCorner, Qt::DockWidgetArea::RightDockWidgetArea);
    this->setCorner(Qt::Corner::BottomRightCorner, Qt::DockWidgetArea::RightDockWidgetArea);

    evidenceTreeDock = new QDockWidget("탐색 트리", this);
    auto evidenceTreeView = new QTreeView(this);

    auto model = new EvidenceTreeModel();
    model->attachImage("/Users/rpark/Downloads/Hunter XP.E01");

    evidenceTreeView->setModel(reinterpret_cast<QAbstractItemModel *>(model));
    evidenceTreeDock->setWidget(evidenceTreeView);

    propsDock = new QDockWidget("속성", this);
    propsDock->setWidget(new QTreeView(this));

    explorerDock = new QDockWidget("파일 목록", this);
    explorerDock->setWidget(new QTreeView(this));

    this->addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, evidenceTreeDock);
    this->addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, propsDock);
    this->addDockWidget(Qt::DockWidgetArea::TopDockWidgetArea, explorerDock);

    this->resizeDocks({evidenceTreeDock, propsDock}, {70, 40}, Qt::Orientation::Vertical);
    this->resizeDocks({explorerDock}, {360}, Qt::Orientation::Vertical);
    this->resizeDocks({evidenceTreeDock, explorerDock}, {250, 750}, Qt::Orientation::Horizontal);

    auto viewerContainer = new DynamicContainer(this);
    this->setCentralWidget(viewerContainer);

    viewerContainer->setWidget(new QPlainTextEdit(this));
}

MainWindow::~MainWindow()
{
}
