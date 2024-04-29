#pragma once

#include <qmenubar.h>

#include "app/menubar/filemenu.hpp"
#include "app/menubar/info.hpp"

class MenuBar : public QMenuBar {
   private:
    MenuInfo* m_menu_info;
    FileMenu* m_file_menu;

   public:
    MenuBar();
    ~MenuBar() = default;
};
