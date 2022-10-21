#ifndef CXNATIVEWINDOWHELPER_H
#define CXNATIVEWINDOWHELPER_H

#include <QPoint>
#include <QWindow>
#include <QMargins>

#define QWINDOWSIZE_MAX ((1<<24)-1)

class CxNativeWindowTester
{
public:
    virtual QMargins draggableMargins() const = 0;
    virtual QMargins maximizedMargins() const = 0;

    virtual bool hitTest(const QPoint &pos) const = 0;
};

class CxNativeWindowHelperPrivate;
class CxNativeWindowHelper : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(CxNativeWindowHelper)

public:
    CxNativeWindowHelper(QWindow *window, CxNativeWindowTester *tester);
    explicit CxNativeWindowHelper(QWindow *window);
    ~CxNativeWindowHelper();

public:
    bool nativeEventFilter(void *msg, long *result);
protected:
    bool eventFilter(QObject *obj, QEvent *ev) final;
protected:
    QScopedPointer<CxNativeWindowHelperPrivate> d_ptr;

signals:
    void scaleFactorChanged(qreal factor);
public:
    qreal scaleFactor() const;
};

#endif // CXNATIVEWINDOWHELPER_H
