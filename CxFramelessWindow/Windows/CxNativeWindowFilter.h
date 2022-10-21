#ifndef CXNATIVEWINDOWFILTER_H
#define CXNATIVEWINDOWFILTER_H

#include <QAbstractNativeEventFilter>

class QWindow;
class CxNativeWindowHelper;
class CxNativeWindowFilter : public QAbstractNativeEventFilter
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    typedef long    Result;
#else
    typedef qintptr Result;
#endif

public:
    bool nativeEventFilter(const QByteArray &eventType, void *message, Result *result) final;
public:
    static void deliver(QWindow *window, CxNativeWindowHelper *helper);
};

#endif // CXNATIVEWINDOWFILTER_H
