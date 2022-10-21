#ifndef QSHARKFRAMELESSHELPER_P_H
#define QSHARKFRAMELESSHELPER_P_H

#include <QSet>
#include <QQuickWindow>

#include "CxQuickFramelessHelper.h"

#include "Windows/CxNativeWindowHelper.h"

class CxQuickFramelessHelperPrivate : public CxNativeWindowTester
{
public:
    CxQuickFramelessHelperPrivate();
    virtual ~CxQuickFramelessHelperPrivate();

public:
    QMargins draggableMargins() const final;
    QMargins maximizedMargins() const final;

    bool hitTest(const QPoint &pos) const final;

public:
    QQuickWindow       *window;
    CxNativeWindowHelper *helper;
public:
    QMargins priDraggableMargins;
    QMargins priMaximizedMargins;
public:
    QSet<QQuickItem *> extraTitleBars;
    int                titleBarHeight;
public:
    QSet<QQuickItem *> includeItems;
    QSet<QQuickItem *> excludeItems;
};

#endif // QSHARKFRAMELESSHELPER_P_H
