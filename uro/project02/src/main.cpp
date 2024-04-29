#include <QApplication>

#include "app/window.hpp"

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    app.setStyle("macOS");

    AppWindow app_window;

    return app.exec();
};
