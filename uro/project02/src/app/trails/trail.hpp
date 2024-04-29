#pragma once

#include <qlist.h>
#include <qstandarditemmodel.h>

#include <cstdint>

class Trail : public QList<QStandardItem*> {
   private:
    QString m_start;
    QString m_end;
    double m_distance;
    uint8_t m_difficulty;
    size_t m_ascent;
    size_t m_descent;
    float m_rating;
    QString m_link;

   public:
    Trail(const QString& t_start, const QString& t_end, double t_distance,
          uint8_t t_difficulty, size_t t_ascent, size_t t_descent,
          float t_rating, const QString& t_link);
    ~Trail() = default;

    QString getStart() const { return this->m_start; }
    QString getEnd() const { return this->m_end; }
    double getDistance() const { return this->m_distance; }
    QString getDifficulty() const;
    size_t getAscent() const { return this->m_ascent; }
    size_t getDescent() const { return this->m_descent; }
    float getRating() const { return this->m_rating; }
    QString getLink() const { return this->m_link; }
};
