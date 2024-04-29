#include "filemenu.hpp"

#include <cstdio>

FileMenu::FileMenu() : QMenu("File") {
    this->addAction("Open file");
    this->addAction("Quit");
}
