#ifndef CXMINIMIZEBUTTON_P_H
#define CXMINIMIZEBUTTON_P_H

#include "CxMinimizeButton.h"

class CxMinimizeButtonPrivate
{
    Q_DECLARE_PUBLIC(CxMinimizeButton)

public:
    CxMinimizeButtonPrivate();
    virtual ~CxMinimizeButtonPrivate();
protected:
    CxMinimizeButton *q_ptr;

protected:
    QWidget *window = nullptr;

    QPixmap blackIcon;
    QPixmap whiteIcon;

    bool dark = false;
};

#endif // CXMINIMIZEBUTTON_P_H
