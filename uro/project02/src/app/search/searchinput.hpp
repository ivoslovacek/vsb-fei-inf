#pragma once

#include <qlineedit.h>

class SearchInput : public QLineEdit {
   private:
    QString m_bg_text;

   protected:
    void paintEvent(QPaintEvent *event) override;

   public:
    SearchInput(QString t_bg_text);
    ~SearchInput() = default;
};
