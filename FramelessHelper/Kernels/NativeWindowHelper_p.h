#ifndef NATIVEWINDOWHELPER_P_H
#define NATIVEWINDOWHELPER_P_H

#include "NativeWindowHelper.h"

class NativeWindowHelperPrivate
{
    Q_DECLARE_PUBLIC(NativeWindowHelper)

public:
    NativeWindowHelperPrivate();
    virtual ~NativeWindowHelperPrivate();
protected:
    NativeWindowHelper *q_ptr;

public:
    void updateWindowStyle();
    int hitTest(int x, int y) const;
    QMargins draggableMargins() const;
    QMargins maximizedMargins() const;
    QRect availableGeometry() const;

public:
    QWindow            *window;
    NativeWindowTester *tester;

    HWND oldWindow;

    qreal scaleFactor;
};

#endif // NATIVEWINDOWHELPER_P_H
