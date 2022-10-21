#ifndef CXCLOSEBUTTON_P_H
#define CXCLOSEBUTTON_P_H

#include "CxCloseButton.h"

class CxCloseButtonPrivate
{
    Q_DECLARE_PUBLIC(CxCloseButton)

public:
    CxCloseButtonPrivate();
    virtual ~CxCloseButtonPrivate();
protected:
    CxCloseButton *q_ptr;

protected:
    QWidget *window = nullptr;

    QPixmap blackIcon;
    QPixmap whiteIcon;

    bool dark = false;
};

#endif // CXCLOSEBUTTON_P_H
