#pragma once

#include <qobject.h>

#include <vector>

#include "app/trails/trail.hpp"
#include "qstandarditemmodel.h"

class TrailItemModel : public QStandardItemModel {
   private:
    std::vector<Trail> m_trails;

   public:
    TrailItemModel(QObject *t_parent = nullptr);
    ~TrailItemModel() = default;

    Trail getTrail(int t_row) const { return this->m_trails[t_row]; }
};
