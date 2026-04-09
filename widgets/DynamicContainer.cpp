#include "DynamicContainer.h"
#include <QtCore>
#include <QtWidgets>

DynamicContainer::DynamicContainer(QWidget *parent) : QWidget(parent)
{
    this->__layout->setContentsMargins(0, 0, 0, 0);
    this->__layout->setSpacing(0);
}

DynamicContainer::~DynamicContainer()
{
}

void DynamicContainer::setWidget(QWidget *widget)
{
    if (this->__currentWidget != nullptr)
    {
        this->__layout->removeWidget(this->__currentWidget);
    }

    this->__currentWidget = widget;
    this->__layout->addWidget(widget);
}
