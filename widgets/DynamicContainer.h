#pragma once

#include <QtWidgets>

class DynamicContainer : public QWidget
{
    Q_OBJECT

  public:
    DynamicContainer(QWidget *parent = nullptr);
    ~DynamicContainer();

    void setWidget(QWidget *widget);

  private:
    QVBoxLayout *__layout = new QVBoxLayout(this);
    QWidget *__currentWidget = nullptr;
};
