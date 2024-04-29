#include "tabview.hpp"

#include <qframe.h>
#include <qtabwidget.h>

#include "app/tabview/details.hpp"
#include "app/tabview/newtrail.hpp"

TabView::TabView()
    : QTabWidget(), m_details(new QFrame()), m_new_trail(new QFrame()) {
    this->addTab(m_details, QString("Details"));
    this->m_details->setLayout(new DetailsLayout());

    this->m_new_trail->setLayout(new NewTrailLayout());
    this->addTab(m_new_trail, QString("New trail"));
}
