#include "searchinput.hpp"

#include <qlineedit.h>
#include <qpainter.h>

SearchInput::SearchInput(QString t_bg_text)
    : QLineEdit(), m_bg_text(" " + t_bg_text) {}

void SearchInput::paintEvent(QPaintEvent *event) {
    QLineEdit::paintEvent(event);

    if (this->text().isEmpty()) {
        QPainter painter(this);
        painter.setPen(Qt::gray);
        painter.drawText(rect(), Qt::AlignLeft | Qt::AlignVCenter,
                         this->m_bg_text);
    }
}
