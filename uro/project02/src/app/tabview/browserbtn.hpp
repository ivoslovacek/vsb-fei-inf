#pragma once

#include <qpushbutton.h>
#include <qtmetamacros.h>
#include <qurl.h>

class BrowserBtn : public QPushButton {
    Q_OBJECT
   private:
    QUrl m_url;

   public slots:
    void onClick();

   public:
    BrowserBtn(QString t_label, QString t_url);
    ~BrowserBtn() = default;
};
