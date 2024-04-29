#pragma once

#include <qframe.h>
#include <qtabwidget.h>

class TabView : public QTabWidget {
   private:
    QFrame *m_details;
    QFrame *m_new_trail;

   public:
    TabView();
    ~TabView() = default;

    [[nodiscard]] inline QFrame *getDetails() const { return m_details; }
};
