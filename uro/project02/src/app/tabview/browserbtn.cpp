#include "browserbtn.hpp"

#include <qdesktopservices.h>
#include <qpushbutton.h>
#include <qurl.h>

BrowserBtn::BrowserBtn(QString t_label, QString t_url)
    : QPushButton(t_label), m_url(QUrl(t_url)) {
    connect(this, &BrowserBtn::clicked, this, &BrowserBtn::onClick);
}

void BrowserBtn::onClick() { QDesktopServices::openUrl(this->m_url); }
