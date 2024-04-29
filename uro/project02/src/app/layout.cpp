#include "layout.hpp"

#include <qlineedit.h>

#include "app/search/searchinput.hpp"
#include "app/tabview/details.hpp"
#include "app/tabview/tabview.hpp"
#include "app/trails/view.hpp"

MainLayout::MainLayout()
    : QBoxLayout(QBoxLayout::Direction::Down),
      m_trail_view(new TrailView()),
      m_tab_view(new TabView()) {
    this->addWidget(new SearchInput("Search for a place"));
    this->addWidget(this->m_trail_view);
    this->addWidget(this->m_tab_view);

    connect(
        this->m_trail_view, &TrailView::dispatchClickedRow,
        dynamic_cast<DetailsLayout*>(this->m_tab_view->getDetails()->layout()),
        &DetailsLayout::onRowClicked);

    this->m_trail_view->onRowClickDispatch(0);
}
