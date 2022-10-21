#ifndef CXNATIVEWINDOWFILTER_P_H
#define CXNATIVEWINDOWFILTER_P_H

#include <QHash>
#include <QWindow>

#include "CxNativeWindowFilter.h"

class CxNativeWindowFilterPrivate
{
public:
    static QScopedPointer<CxNativeWindowFilter> instance;

    static QHash<CxNativeWindowHelper *, WId> windows;
    static QHash<QWindow *, WId> winIds;
    static QHash<WId, CxNativeWindowHelper *> helpers;
};

#endif // CXNATIVEWINDOWFILTER_P_H
