#include "details.hpp"

#include <qgridlayout.h>
#include <qlabel.h>
#include <qnamespace.h>
#include <qsizepolicy.h>

#include <iomanip>
#include <sstream>
#include <string>

#include "app/tabview/browserbtn.hpp"

DetailsLayout::DetailsLayout() : QGridLayout() {}

void DetailsLayout::onRowClicked(Trail t_trail) {
    QLayoutItem* l_layout_item;

    while ((l_layout_item = this->takeAt(0)) != nullptr) {
        delete l_layout_item->widget();
        delete l_layout_item;
    }

    std::stringstream l_tmp;

    this->addWidget(new QLabel("Start: " + t_trail.getStart()), 0, 0,
                    Qt::AlignLeft);

    this->addWidget(new QLabel("End: " + t_trail.getEnd()), 0, 1,
                    Qt::AlignLeft);

    l_tmp << t_trail.getDistance() << std::setprecision(1);
    this->addWidget(new QLabel(("Distance: " + l_tmp.str() + "km").c_str()), 1,
                    0, Qt::AlignLeft);
    l_tmp = std::stringstream();

    this->addWidget(new QLabel("Difficulty: " + t_trail.getDifficulty()), 1, 1,
                    Qt::AlignLeft);

    l_tmp << t_trail.getAscent() << std::setprecision(1);
    this->addWidget(new QLabel(("Ascent: " + l_tmp.str() + "m").c_str()), 2, 0,
                    Qt::AlignLeft);
    l_tmp = std::stringstream();

    l_tmp << t_trail.getDescent() << std::setprecision(1);
    this->addWidget(new QLabel(("Descent: " + l_tmp.str() + "m").c_str()), 2, 1,
                    Qt::AlignLeft);
    l_tmp = std::stringstream();

    l_tmp << t_trail.getRating() << std::setprecision(1);
    this->addWidget(new QLabel(("Rating: " + l_tmp.str() + "\u2605").c_str()),
                    3, 0, Qt::AlignLeft);
    l_tmp = std::stringstream();

    this->addWidget(new BrowserBtn("Route link", t_trail.getLink()), 3, 1,
                    Qt::AlignLeft);

    for (int i = 0; i < this->count(); i++) {
        this->itemAt(i)->widget()->setSizePolicy(QSizePolicy(
            QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding));
    }
}
