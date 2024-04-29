#include "window.hpp"

#include <qmainwindow.h>
#include <qtreeview.h>
#include <qwidget.h>

#include "app/layout.hpp"
#include "app/menubar/menubar.hpp"

AppWindow::AppWindow(QWidget* t_parent)
    : QMainWindow(t_parent),
      m_main_widget(new QWidget()),
      m_main_layout(new MainLayout()),
      m_menu(new MenuBar()) {
    this->setWindowTitle("Trail Manager");
    this->setCentralWidget(this->m_main_widget);
    this->m_main_widget->setLayout(this->m_main_layout);

    this->setMenuBar(this->m_menu);

    this->setSizePolicy(QSizePolicy(QSizePolicy::MinimumExpanding,
                                    QSizePolicy::MinimumExpanding));
    this->adjustSize();
    this->show();
}
