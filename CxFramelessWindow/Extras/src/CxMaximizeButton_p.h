#ifndef CXMAXIMIZEBUTTON_P_H
#define CXMAXIMIZEBUTTON_P_H

#include "CxMaximizeButton.h"

class CxMaximizeButtonPrivate
{
    Q_DECLARE_PUBLIC(CxMaximizeButton)

public:
    CxMaximizeButtonPrivate();
    virtual ~CxMaximizeButtonPrivate();
protected:
    CxMaximizeButton *q_ptr;

protected:
    QWidget *window = nullptr;

    QPixmap blackIcon1;
    QPixmap whiteIcon1;
    QPixmap blackIcon2;
    QPixmap whiteIcon2;

    bool dark = false;
};

#endif // CXMAXIMIZEBUTTON_P_H
