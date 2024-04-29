#pragma once

#include <qstandarditemmodel.h>
#include <qtableview.h>
#include <qtmetamacros.h>
#include <qwidget.h>

#include "app/trails/itemmodel.hpp"

class TrailView : public QTableView {
    Q_OBJECT
   private:
    TrailItemModel* m_item_model;

   private slots:
    void onRowClick(const QModelIndex& index);

   signals:
    void dispatchClickedRow(Trail);

   public:
    TrailView(QWidget* t_parent = nullptr);
    ~TrailView() = default;

    void onRowClickDispatch(int t_row);
};
