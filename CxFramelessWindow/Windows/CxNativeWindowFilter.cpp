#include "CxNativeWindowFilter.h"
#include "CxNativeWindowFilter_p.h"

#include <windows.h>

#include <QCoreApplication>

#include "CxNativeWindowHelper_p.h"

// class CxNativeWindowFilter

bool CxNativeWindowFilter::nativeEventFilter(const QByteArray &eventType, void *message, Result *result)
{
    Q_UNUSED(eventType);

    LPMSG msg = reinterpret_cast<LPMSG>(message);
    if (auto h = CxNativeWindowFilterPrivate::helpers.value(reinterpret_cast<WId>(msg->hwnd)))
        return h->nativeEventFilter(msg, result);

    return false;
}

void CxNativeWindowFilter::deliver(QWindow *window, CxNativeWindowHelper *helper)
{
    Q_CHECK_PTR(window);

    if (!CxNativeWindowFilterPrivate::instance) {
        CxNativeWindowFilter *filter = new CxNativeWindowFilter();
        CxNativeWindowFilterPrivate::instance.reset(filter);
        qApp->installNativeEventFilter(filter);
    }

    if (helper) {
        WId newId = window->winId();
        WId oldId = CxNativeWindowFilterPrivate::windows.value(helper);
        if (newId != oldId) {
            CxNativeWindowFilterPrivate::helpers.insert(newId, helper);
            CxNativeWindowFilterPrivate::helpers.remove(oldId);
            CxNativeWindowFilterPrivate::windows.insert(helper, newId);

            CxNativeWindowFilterPrivate::winIds.insert(window, newId);
        }
    } else {
        WId oldId = CxNativeWindowFilterPrivate::winIds.take(window);
        CxNativeWindowHelper *helper = CxNativeWindowFilterPrivate::helpers.take(oldId);
        CxNativeWindowFilterPrivate::windows.remove(helper);
    }
}

// class CxNativeWindowFilterPrivate

QScopedPointer<CxNativeWindowFilter> CxNativeWindowFilterPrivate::instance;

QHash<CxNativeWindowHelper *, WId> CxNativeWindowFilterPrivate::windows;
QHash<QWindow *, WId> CxNativeWindowFilterPrivate::winIds;
QHash<WId, CxNativeWindowHelper *> CxNativeWindowFilterPrivate::helpers;
