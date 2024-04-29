#include "itemmodel.hpp"

#include <qcontainerfwd.h>
#include <qlist.h>
#include <qobject.h>
#include <qstandarditemmodel.h>

#include <vector>

#include "trail.hpp"

TrailItemModel::TrailItemModel(QObject* t_parent)
    : QStandardItemModel(t_parent),
      m_trails({Trail("Štrbské pleso", "Ostrva", 7.9, 2, 673, 27, 4.8,
                      "https://en.mapy.cz/s/jopahanasu"),
                Trail("Skalnaté pleso", "Zelené pleso", 5.4, 3, 253, 470, 4.9,
                      "https://en.mapy.cz/s/huvajepaha"),
                Trail("Mosty u Jablunkova", "Trojmezí", 11.1, 1, 375, 335, 4.0,
                      "https://en.mapy.cz/s/lolemukofe"),
                Trail("Horní lomná", "Malenovice", 25.5, 1, 1074, 1027, 3.6,
                      "https://en.mapy.cz/s/kanutolona"),
                Trail("Řeka", "Javorový", 5.4, 2, 564, 0, 3.2,
                      "https://en.mapy.cz/s/kavuruguvu"),
                Trail("Červenohorské sedlo", "Šerák", 9.1, 1, 557, 243, 3.9,
                      "https://en.mapy.cz/s/fohohujemu"),
                Trail("Ovčárna", "Bělá pod Pradědem", 14.7, 1, 151, 900, 4.1,
                      "https://en.mapy.cz/s/gabevoloca"),
                Trail("Hrádek", "Filípka", 5.1, 1, 411, 0, 3.1,
                      "https://en.mapy.cz/s/davuruseto"),
                Trail("Nýdek", "Velká Čantoryje", 4.9, 1, 579, 0, 4.4,
                      "https://en.mapy.cz/s/nozevosoze"),
                Trail("Bílá", "Bobek", 8.5, 1, 384, 79, 2.5,
                      "https://en.mapy.cz/s/jutadaleme")}) {
    std::vector<QStandardItem*> l_header{
        new QStandardItem("Start"), new QStandardItem("Finish"),
        new QStandardItem("Total distance"), new QStandardItem("Difficulty")};

    for (size_t i = 0; i < l_header.size(); i++) {
        this->setHorizontalHeaderItem(i, l_header[i]);
    }

    for (auto& each : m_trails) {
        this->appendRow(dynamic_cast<const QList<QStandardItem*>&>(each));
    }
}
