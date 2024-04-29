#pragma once

#include <qgridlayout.h>
#include <qlabel.h>
#include <qtmetamacros.h>

#include "app/trails/trail.hpp"

class DetailsLayout : public QGridLayout {
    Q_OBJECT
   private:
    QLabel* m_start;
    QLabel* m_end;
    QLabel* m_distance;
    QLabel* m_difficulty;
    QLabel* m_ascent;
    QLabel* m_descent;
    QLabel* m_rating;
    QLabel* m_link;
   public slots:
    void onRowClicked(Trail t_trail);

   public:
    DetailsLayout();
    ~DetailsLayout() = default;
};
