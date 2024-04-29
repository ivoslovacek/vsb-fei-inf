#include "view.hpp"

#include <qabstractitemmodel.h>
#include <qheaderview.h>
#include <qobjectdefs.h>
#include <qsizepolicy.h>
#include <qtableview.h>

#include <iostream>
#include <ostream>

#include "app/trails/itemmodel.hpp"

TrailView::TrailView(QWidget* t_parent)
    : QTableView(t_parent), m_item_model(new TrailItemModel()) {
    this->setModel(this->m_item_model);

    this->setSelectionBehavior(QAbstractItemView ::SelectRows);
    this->setSelectionMode(QAbstractItemView ::SingleSelection);
    this->setEditTriggers(QAbstractItemView ::NoEditTriggers);
    this->horizontalHeader()->setStretchLastSection(true);

    this->setSizePolicy(QSizePolicy(QSizePolicy::MinimumExpanding,
                                    QSizePolicy::MinimumExpanding));
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    connect(this, &TrailView::clicked, this, &TrailView::onRowClick);
}

void TrailView::onRowClick(const QModelIndex& t_index) {
    this->onRowClickDispatch(t_index.row());
}

void TrailView::onRowClickDispatch(int t_row) {
    auto l_item_model = this->m_item_model->getTrail(t_row);

    emit this->dispatchClickedRow(l_item_model);
}
