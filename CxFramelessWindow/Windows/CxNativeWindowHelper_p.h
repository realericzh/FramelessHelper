#ifndef CXNATIVEWINDOWHELPER_P_H
#define CXNATIVEWINDOWHELPER_P_H

#include "CxNativeWindowHelper.h"

class CxNativeWindowHelperPrivate
{
    Q_DECLARE_PUBLIC(CxNativeWindowHelper)

public:
    CxNativeWindowHelperPrivate();
    virtual ~CxNativeWindowHelperPrivate();
protected:
    CxNativeWindowHelper *q_ptr;

protected:
    void updateWindowStyle();
    int hitTest(int x, int y) const;
    QMargins maximizedMargins() const;
    QRect availableGeometry() const;

protected:
    QWindow              *window = nullptr;
    CxNativeWindowTester *tester = nullptr;

    qreal scaleFactor = 1.0;

    HWND oldWindow = NULL;
};

#endif // CXNATIVEWINDOWHELPER_P_H
