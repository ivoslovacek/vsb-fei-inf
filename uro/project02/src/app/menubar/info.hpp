#pragma once

#include <qaction.h>
#include <qmessagebox.h>

class InfoBox;

class MenuInfo : public QAction {
    Q_OBJECT
   private:
    QMessageBox *m_info_window;

   public:
    MenuInfo();
    ~MenuInfo() = default;

    void showInfo();
};
