#include "info.hpp"

#include <qaction.h>
#include <qmessagebox.h>

MenuInfo::MenuInfo() : QAction("Info") {
    connect(this, &MenuInfo::triggered, this, &MenuInfo::showInfo);
}

void MenuInfo::showInfo() {
    QMessageBox::about(nullptr, "About Trail Manager",
                       "Trail manger lets you store basic\n information about "
                       "hiking trails\n© Ivo Slováček 2024");
}
