#pragma once

#include <qmainwindow.h>
#include <qwidget.h>

#include "app/layout.hpp"
#include "app/menubar/menubar.hpp"

class AppWindow : public QMainWindow {
   private:
    QWidget* m_main_widget;
    MainLayout* m_main_layout;
    MenuBar* m_menu;

   public:
    AppWindow(QWidget* t_parent = nullptr);
    ~AppWindow() = default;
};
