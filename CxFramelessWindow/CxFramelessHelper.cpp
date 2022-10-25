#include "CxFramelessHelper.h"
#include "CxFramelessHelper_p.h"

#include <windows.h>

// class CxFramelessHelper

CxFramelessHelper::CxFramelessHelper(QWidget *parent)
    : QObject(parent)
    , d_ptr(new CxFramelessHelperPrivate())
{
    Q_D(CxFramelessHelper);
    Q_CHECK_PTR(parent);
    d->window = parent;

    if (d->window)
        d->window->installEventFilter(this);
}

CxFramelessHelper::~CxFramelessHelper()
{
}

void CxFramelessHelper::setDraggableMargins(int left, int top, int right, int bottom)
{
    Q_D(CxFramelessHelper);

    d->priDraggableMargins = QMargins(left, top, right, bottom);
}

void CxFramelessHelper::setMaximizedMargins(int left, int top, int right, int bottom)
{
    Q_D(CxFramelessHelper);

    d->priMaximizedMargins = QMargins(left, top, right, bottom);
}

void CxFramelessHelper::setDraggableMargins(const QMargins &margins)
{
    Q_D(CxFramelessHelper);

    d->priDraggableMargins = margins;
}

void CxFramelessHelper::setMaximizedMargins(const QMargins &margins)
{
    Q_D(CxFramelessHelper);

    d->priMaximizedMargins = margins;
}

QMargins CxFramelessHelper::draggableMargins() const
{
    Q_D(const CxFramelessHelper);

    return d->priDraggableMargins;
}

QMargins CxFramelessHelper::maximizedMargins() const
{
    Q_D(const CxFramelessHelper);

    return d->priMaximizedMargins;
}

void CxFramelessHelper::addIncludeItem(QWidget *item)
{
    Q_D(CxFramelessHelper);

    d->includeItems.insert(item);
}

void CxFramelessHelper::removeIncludeItem(QWidget *item)
{
    Q_D(CxFramelessHelper);

    d->includeItems.remove(item);
}

void CxFramelessHelper::addExcludeItem(QWidget *item)
{
    Q_D(CxFramelessHelper);

    d->excludeItems.insert(item);
}

void CxFramelessHelper::removeExcludeItem(QWidget *item)
{
    Q_D(CxFramelessHelper);

    d->excludeItems.remove(item);
}

void CxFramelessHelper::setTitleBarHeight(int value)
{
    Q_D(CxFramelessHelper);

    if (value != d->titleBarHeight) {
        d->titleBarHeight = value;
        emit titleBarHeightChanged(value);
    }
}

int CxFramelessHelper::titleBarHeight() const
{
    Q_D(const CxFramelessHelper);

    return d->titleBarHeight;
}

qreal CxFramelessHelper::scaleFactor() const
{
    Q_D(const CxFramelessHelper);

    return d->helper ? d->helper->scaleFactor() : 1.0;
}

bool CxFramelessHelper::isMaximized() const
{
    Q_D(const CxFramelessHelper);

    return d->maximized;
}

void CxFramelessHelper::triggerMinimizeButtonAction()
{
    Q_D(CxFramelessHelper);

    if (d->window) {
        d->window->showMinimized();
    }
}

void CxFramelessHelper::triggerMaximizeButtonAction()
{
    Q_D(CxFramelessHelper);

    if (d->window) {
        const QSize maximumSize = d->window->maximumSize();
        if ((maximumSize.width() != QWINDOWSIZE_MAX)
                || (maximumSize.height() != QWINDOWSIZE_MAX)) {
            return;
        }

        if (d->window->windowState() & Qt::WindowMaximized) {
            d->window->showNormal();
        } else {
            d->window->showMaximized();
        }
    }
}

void CxFramelessHelper::triggerCloseButtonAction()
{
    Q_D(CxFramelessHelper);

    if (d->window) {
        d->window->close();
    }
}

bool CxFramelessHelper::eventFilter(QObject *obj, QEvent *ev)
{
    Q_D(CxFramelessHelper);

    if (ev->type() == QEvent::WindowStateChange) {
        bool maximized = d->window->windowState() & Qt::WindowMaximized;
        if (maximized != d->maximized) {
            d->maximized = maximized;
            emit maximizedChanged(maximized);
        }
    } else if (ev->type() == QEvent::WinIdChange) {
        if (nullptr == d->helper) {
            auto w = d->window->windowHandle();

            d->helper = new CxNativeWindowHelper(w, d);
            connect(d->helper, &CxNativeWindowHelper::scaleFactorChanged,
                    this, &CxFramelessHelper::scaleFactorChanged);
            if (!qFuzzyCompare(d->helper->scaleFactor(), 1.0)) {
                emit scaleFactorChanged(d->helper->scaleFactor());
            }
        }
    }

#if QT_VERSION < QT_VERSION_CHECK(5, 9, 0)
    if ((ev->type() == QEvent::Resize) || (ev->type() == QEvent::WindowStateChange)) {
        if (d->window->windowState() & Qt::WindowMaximized) {
            const QMargins &m = d->priMaximizedMargins;
            int r = GetSystemMetrics(SM_CXFRAME) * 2 - m.left() - m.right();
            int b = GetSystemMetrics(SM_CYFRAME) * 2 - m.top() - m.bottom();

            d->window->setContentsMargins(0, 0, r, b);
        } else {
            d->window->setContentsMargins(0 ,0, 0, 0);
        }
    }
#endif

    return QObject::eventFilter(obj, ev);
}

// class CxFramelessHelperPrivate

CxFramelessHelperPrivate::CxFramelessHelperPrivate()
    : window(nullptr)
    , helper(nullptr)
    , titleBarHeight(0)
    , maximized(false)
{
}

CxFramelessHelperPrivate::~CxFramelessHelperPrivate()
{
}

QMargins CxFramelessHelperPrivate::draggableMargins() const
{
    return priDraggableMargins;
}

QMargins CxFramelessHelperPrivate::maximizedMargins() const
{
    return priMaximizedMargins;
}

bool CxFramelessHelperPrivate::hitTest(const QPoint &pos) const
{
    if (!window)
        return false;
    else if (titleBarHeight == 0)
        return false;
    else if ((titleBarHeight > 0)
             && (pos.y() >= titleBarHeight))
        return false;

    int currentIndex = -1;
    QWidget *items[32] = {0};
    auto child = window;
    QPoint p = pos;

    while (child && (currentIndex < 31)) {
        items[++currentIndex] = child;
        auto grandchild = child->childAt(p);
        if (nullptr == grandchild) {
            break;
        }

        p = grandchild->mapFrom(child, p);
        child = grandchild;
    }

    while (currentIndex > 0) {
        child = items[currentIndex];
        --currentIndex;

        if (includeItems.contains(child)) {
            break;
        } else if (excludeItems.contains(child)) {
            return false;
        } else if (window == child) {
            break;
        }
    }

    return true;
}
