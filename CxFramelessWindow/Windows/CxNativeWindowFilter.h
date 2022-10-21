#ifndef CXNATIVEWINDOWFILTER_H
#define CXNATIVEWINDOWFILTER_H

#include <QAbstractNativeEventFilter>

class QWindow;
class CxNativeWindowHelper;
class CxNativeWindowFilter : public QAbstractNativeEventFilter
{
public:
    bool nativeEventFilter(const QByteArray &eventType, void *message, long *result) final;
public:
    static void deliver(QWindow *window, CxNativeWindowHelper *helper);
};

#endif // CXNATIVEWINDOWFILTER_H
