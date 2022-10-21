#include "CxQuickFramelessHelper.h"
#include "CxQuickFramelessHelper_p.h"

#include <QQmlEngine>
#include <QQuickItem>

// class CxQuickFramelessHelper

CxQuickFramelessHelper::CxQuickFramelessHelper(QObject *parent)
    : QObject(parent)
    , d_ptr(new CxQuickFramelessHelperPrivate())
{
}

CxQuickFramelessHelper::~CxQuickFramelessHelper()
{
}

void CxQuickFramelessHelper::classBegin()
{
}

void CxQuickFramelessHelper::componentComplete()
{
    Q_D(CxQuickFramelessHelper);

    auto obj = parent();
    while (nullptr != obj) {
        if (obj->inherits("QQuickRootItem")) {
            if (auto rootItem = qobject_cast<QQuickItem *>(obj)) {
                if (auto window = rootItem->window()) {
                    d->window = window;

                    d->helper = new CxNativeWindowHelper(window, d);
                    connect(d->helper, &CxNativeWindowHelper::scaleFactorChanged,
                            this, &CxQuickFramelessHelper::scaleFactorChanged);
                    if (!qFuzzyCompare(d->helper->scaleFactor(), 1.0)) {
                        emit scaleFactorChanged();
                    }
                }

                break;
            }
        }

        obj = obj->parent();
    }
}

void CxQuickFramelessHelper::setTopDraggableMargin(int dm)
{
    Q_D(CxQuickFramelessHelper);

    if (dm != d->priDraggableMargins.top()) {
        d->priDraggableMargins.setTop(dm);
        emit topDraggableMarginChanged();
    }
}

void CxQuickFramelessHelper::setLeftDraggableMargin(int dm)
{
    Q_D(CxQuickFramelessHelper);

    if (dm != d->priDraggableMargins.left()) {
        d->priDraggableMargins.setLeft(dm);
        emit leftDraggableMarginChanged();
    }
}

void CxQuickFramelessHelper::setRightDraggableMargin(int dm)
{
    Q_D(CxQuickFramelessHelper);

    if (dm != d->priDraggableMargins.right()) {
        d->priDraggableMargins.setRight(dm);
        emit rightDraggableMarginChanged();
    }
}

void CxQuickFramelessHelper::setBottomDraggableMargin(int dm)
{
    Q_D(CxQuickFramelessHelper);

    if (dm != d->priDraggableMargins.bottom()) {
        d->priDraggableMargins.setBottom(dm);
        emit bottomDraggableMarginChanged();
    }
}

int CxQuickFramelessHelper::topDraggableMargin() const
{
    Q_D(const CxQuickFramelessHelper);

    return d->priDraggableMargins.top();
}

int CxQuickFramelessHelper::leftDraggableMargin() const
{
    Q_D(const CxQuickFramelessHelper);

    return d->priDraggableMargins.left();
}

int CxQuickFramelessHelper::rightDraggableMargin() const
{
    Q_D(const CxQuickFramelessHelper);

    return d->priDraggableMargins.right();
}

int CxQuickFramelessHelper::bottomDraggableMargin() const
{
    Q_D(const CxQuickFramelessHelper);

    return d->priDraggableMargins.bottom();
}

void CxQuickFramelessHelper::setTopMaximizedMargin(int dm)
{
    Q_D(CxQuickFramelessHelper);

    if (dm != d->priMaximizedMargins.top()) {
        d->priMaximizedMargins.setTop(dm);
        emit topMaximizedMarginChanged();
    }
}

void CxQuickFramelessHelper::setLeftMaximizedMargin(int dm)
{
    Q_D(CxQuickFramelessHelper);

    if (dm != d->priMaximizedMargins.left()) {
        d->priMaximizedMargins.setLeft(dm);
        emit leftMaximizedMarginChanged();
    }
}

void CxQuickFramelessHelper::setRightMaximizedMargin(int dm)
{
    Q_D(CxQuickFramelessHelper);

    if (dm != d->priMaximizedMargins.right()) {
        d->priMaximizedMargins.setRight(dm);
        emit rightMaximizedMarginChanged();
    }
}

void CxQuickFramelessHelper::setBottomMaximizedMargin(int dm)
{
    Q_D(CxQuickFramelessHelper);

    if (dm != d->priMaximizedMargins.bottom()) {
        d->priMaximizedMargins.setBottom(dm);
        emit bottomMaximizedMarginChanged();
    }
}

int CxQuickFramelessHelper::topMaximizedMargin() const
{
    Q_D(const CxQuickFramelessHelper);

    return d->priMaximizedMargins.top();
}

int CxQuickFramelessHelper::leftMaximizedMargin() const
{
    Q_D(const CxQuickFramelessHelper);

    return d->priMaximizedMargins.left();
}

int CxQuickFramelessHelper::rightMaximizedMargin() const
{
    Q_D(const CxQuickFramelessHelper);

    return d->priMaximizedMargins.right();
}

int CxQuickFramelessHelper::bottomMaximizedMargin() const
{
    Q_D(const CxQuickFramelessHelper);

    return d->priMaximizedMargins.bottom();
}

void CxQuickFramelessHelper::addIncludeItem(QQuickItem *item)
{
    Q_D(CxQuickFramelessHelper);

    d->includeItems.insert(item);
}

void CxQuickFramelessHelper::removeIncludeItem(QQuickItem *item)
{
    Q_D(CxQuickFramelessHelper);

    d->includeItems.remove(item);
}

void CxQuickFramelessHelper::addExcludeItem(QQuickItem *item)
{
    Q_D(CxQuickFramelessHelper);

    d->excludeItems.insert(item);
}

void CxQuickFramelessHelper::removeExcludeItem(QQuickItem *item)
{
    Q_D(CxQuickFramelessHelper);

    d->excludeItems.remove(item);
}

void CxQuickFramelessHelper::setTitleBarHeight(int value)
{
    Q_D(CxQuickFramelessHelper);

    if (value != d->titleBarHeight) {
        d->titleBarHeight = value;
        emit titleBarHeightChanged();
    }
}

int CxQuickFramelessHelper::titleBarHeight() const
{
    Q_D(const CxQuickFramelessHelper);

    return d->titleBarHeight;
}

qreal CxQuickFramelessHelper::scaleFactor() const
{
    Q_D(const CxQuickFramelessHelper);

    return d->helper ? d->helper->scaleFactor() : 1.0;
}

void CxQuickFramelessHelper::triggerMinimizeButtonAction()
{
    Q_D(CxQuickFramelessHelper);

    if (d->window) {
        auto oldStates = d->window->windowStates();
        d->window->setWindowStates((oldStates & ~Qt::WindowActive) | Qt::WindowMinimized);
    }
}

void CxQuickFramelessHelper::triggerMaximizeButtonAction()
{
    Q_D(CxQuickFramelessHelper);

    if (d->window) {
        const QSize maximumSize = d->window->maximumSize();
        if ((maximumSize.width() != QWINDOWSIZE_MAX)
                || (maximumSize.height() != QWINDOWSIZE_MAX)) {
            return;
        }

        if (QWindow::Maximized == d->window->visibility()) {
            d->window->showNormal();
        } else {
            d->window->showMaximized();
        }
    }
}

void CxQuickFramelessHelper::triggerCloseButtonAction()
{
    Q_D(CxQuickFramelessHelper);

    if (d->window) {
        d->window->close();
    }
}

// class CxQuickFramelessHelperPrivate

CxQuickFramelessHelperPrivate::CxQuickFramelessHelperPrivate()
    : window(nullptr)
    , helper(nullptr)
    , titleBarHeight(0)
{
}

CxQuickFramelessHelperPrivate::~CxQuickFramelessHelperPrivate()
{
}

QMargins CxQuickFramelessHelperPrivate::draggableMargins() const
{
    return priDraggableMargins;
}

QMargins CxQuickFramelessHelperPrivate::maximizedMargins() const
{
    return priMaximizedMargins;
}

bool CxQuickFramelessHelperPrivate::hitTest(const QPoint &pos) const
{
    int scaledTitleBarHeight = titleBarHeight * helper->scaleFactor();

    if (!window)
        return false;
    else if (scaledTitleBarHeight == 0)
        return false;
    else if ((scaledTitleBarHeight > 0)
             && (pos.y() >= scaledTitleBarHeight))
        return false;

    auto rootItem = window->contentItem();
    if (nullptr == rootItem) {
        return false;
    }

    int currentIndex = -1;
    QQuickItem *items[32] = {0};
    auto child = rootItem;
    QPointF p = pos;

    while (child && (currentIndex < 31)) {
        items[++currentIndex] = child;
        auto grandchild = child->childAt(p.x(), p.y());
        if (nullptr == grandchild) {
            break;
        }

        p = child->mapToItem(grandchild, p);
        child = grandchild;
    }

    while (currentIndex > 0) {
        child = items[currentIndex];
        --currentIndex;

        if (excludeItems.contains(child)) {
            return false;
        } else if (includeItems.contains(child)) {
            break;
        } else if (rootItem == child) {
            break;
        }
    }

    return true;
}
