#pragma once

#include <qdialog.h>
#include <qgridlayout.h>

class NewTrailLayout : public QGridLayout {
   private:
   public:
    NewTrailLayout();
    ~NewTrailLayout() = default;
};

template <class T>
class InputBox : public QGridLayout {
   private:
   public:
    InputBox(QString t_label);
    ~InputBox() = default;
};
