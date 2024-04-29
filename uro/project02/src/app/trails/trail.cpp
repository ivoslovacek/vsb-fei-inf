#include "trail.hpp"

#include <qlist.h>
#include <qstandarditemmodel.h>

#include <array>
#include <cstdint>

Trail::Trail(const QString& t_start, const QString& t_end, double t_distance,
             uint8_t t_difficulty, size_t t_ascent, size_t t_descent,
             float t_rating, const QString& t_link)
    : QList<QStandardItem*>(),
      m_start(t_start),
      m_end(t_end),
      m_distance(t_distance),
      m_difficulty(t_difficulty),
      m_ascent(t_ascent),
      m_descent(t_descent),
      m_rating(t_rating),
      m_link(t_link) {
    this->append(new QStandardItem(m_start));
    this->append(new QStandardItem(m_end));
    this->append(new QStandardItem(QString::number(t_distance) + "km"));
    this->append(new QStandardItem(this->getDifficulty()));
}

QString Trail::getDifficulty() const {
    constexpr std::array l_difficulty_table = {
        "Easy", "Moderate", "Moderately Strenous", "Strenous", "Very Strenuos"};

    return QString(l_difficulty_table.at(this->m_difficulty - 1));
}
