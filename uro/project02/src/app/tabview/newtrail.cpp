#include "newtrail.hpp"

#include <qgridlayout.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qnamespace.h>
#include <qpushbutton.h>
#include <qwidget.h>

NewTrailLayout::NewTrailLayout() : QGridLayout() {
    QWidget *l_tmp = new QWidget();

    l_tmp->setLayout(new InputBox<QLineEdit>("Start"));
    this->addWidget(l_tmp, 0, 0, Qt::AlignRight);

    l_tmp = new QWidget();
    l_tmp->setLayout(new InputBox<QLineEdit>("End"));
    this->addWidget(l_tmp, 0, 1, Qt::AlignLeft);

    l_tmp = new QWidget();
    l_tmp->setLayout(new InputBox<QLineEdit>("Distance"));
    this->addWidget(l_tmp, 1, 0, Qt::AlignRight);

    l_tmp = new QWidget();
    l_tmp->setLayout(new InputBox<QLineEdit>("Difficulty"));
    this->addWidget(l_tmp, 1, 1, Qt::AlignLeft);

    l_tmp = new QWidget();
    l_tmp->setLayout(new InputBox<QLineEdit>("Ascent"));
    this->addWidget(l_tmp, 2, 0, Qt::AlignRight);

    l_tmp = new QWidget();
    l_tmp->setLayout(new InputBox<QLineEdit>("Descent"));
    this->addWidget(l_tmp, 2, 1, Qt::AlignLeft);

    l_tmp = new QWidget();
    l_tmp->setLayout(new InputBox<QLineEdit>("Rating"));
    this->addWidget(l_tmp, 3, 0, Qt::AlignRight);

    l_tmp = new QWidget();
    l_tmp->setLayout(new InputBox<QLineEdit>("Route link"));
    this->addWidget(l_tmp, 3, 1, Qt::AlignLeft);

    l_tmp = new QPushButton("Add trail");
    l_tmp->setSizePolicy(
        QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum));
    this->addWidget(l_tmp, 4, 0, 1, 2, Qt::AlignCenter);
}

template <class T>
InputBox<T>::InputBox(QString t_label) : QGridLayout() {
    this->addWidget(new QLabel(t_label + ": "), 0, 0, Qt::AlignLeft);
    this->addWidget(new T(), 0, 1, Qt::AlignLeft);
}
