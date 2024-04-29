#include "menubar.hpp"

#include <qmainwindow.h>

#include "app/menubar/filemenu.hpp"
#include "app/menubar/info.hpp"

MenuBar::MenuBar()
    : QMenuBar(), m_menu_info(new MenuInfo()), m_file_menu(new FileMenu()) {
    this->addMenu(this->m_file_menu);
    this->addAction(this->m_menu_info);
}
