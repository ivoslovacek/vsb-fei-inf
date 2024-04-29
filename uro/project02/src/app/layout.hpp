#pragma once

#include <qboxlayout.h>

#include "app/tabview/tabview.hpp"
#include "app/trails/view.hpp"

class MainLayout : public QBoxLayout {
   private:
    TrailView *m_trail_view;
    TabView *m_tab_view;

   public:
    MainLayout();
    ~MainLayout() = default;
};
