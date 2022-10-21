#include "CxNativeWindowHelper.h"
#include "CxNativeWindowHelper_p.h"

#include <windows.h>
#include <windowsx.h>
#include <winuser.h>
#include <Uxtheme.h>
#include <dwmapi.h>

#include <QScreen>
#include <QEvent>
#include <QOperatingSystemVersion>

#include "CxNativeWindowFilter.h"

#if defined(__GNUC__)
#  define WM_DPICHANGED       0x02E0
#endif

// class CxNativeWindowHelper

CxNativeWindowHelper::CxNativeWindowHelper(QWindow *window, CxNativeWindowTester *tester)
    : QObject(window)
    , d_ptr(new CxNativeWindowHelperPrivate())
{
    d_ptr->q_ptr = this;

    Q_D(CxNativeWindowHelper);

    Q_CHECK_PTR(window);
    Q_CHECK_PTR(tester);

    d->window = window;
    d->tester = tester;

    if (d->window) {
        d->scaleFactor = d->window->screen()->devicePixelRatio();
        if (d->window->flags() & Qt::FramelessWindowHint) {
            d->window->installEventFilter(this);
            d->updateWindowStyle();
        }
    }
}

CxNativeWindowHelper::CxNativeWindowHelper(QWindow *window)
    : QObject(window)
    , d_ptr(new CxNativeWindowHelperPrivate())
{
    d_ptr->q_ptr = this;

    Q_D(CxNativeWindowHelper);

    Q_CHECK_PTR(window);

    d->window = window;

    if (d->window) {
        d->scaleFactor = d->window->screen()->devicePixelRatio();
        if (d->window->flags() & Qt::FramelessWindowHint) {
            d->window->installEventFilter(this);
            d->updateWindowStyle();
        }
    }
}

CxNativeWindowHelper::~CxNativeWindowHelper()
{
}

bool CxNativeWindowHelper::nativeEventFilter(void *msg, Result *result)
{
    Q_D(CxNativeWindowHelper);

    Q_CHECK_PTR(d->window);

    const LPMSG lpMsg = reinterpret_cast<LPMSG>(msg);
    const WPARAM wParam = lpMsg->wParam;
    const LPARAM lParam = lpMsg->lParam;

    if (WM_NCHITTEST == lpMsg->message) {
        *result = d->hitTest(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        return true;
    } else if (WM_NCACTIVATE == lpMsg->message) {
        if (result) *result = 1;
        return true;
    } else if (WM_NCPAINT == lpMsg->message) {
        if (result) *result = 0;
        return true;
    } else if (WM_NCCALCSIZE == lpMsg->message) {
        if (TRUE == wParam) {
            if (HWND hWnd = reinterpret_cast<HWND>(d->window->winId())) {
                WINDOWPLACEMENT placement = {0};
                if (GetWindowPlacement(hWnd, &placement) && (SW_MAXIMIZE == placement.showCmd)) {
                    LPNCCALCSIZE_PARAMS params = reinterpret_cast<LPNCCALCSIZE_PARAMS>(lParam);

                    const QRect g = d->availableGeometry();
                    const QMargins mm = d->maximizedMargins();

                    params->rgrc[0].top =    g.top()    - mm.top();
                    params->rgrc[0].left =   g.left()   - mm.left();
                    params->rgrc[0].right =  g.right()  + mm.right() + 1;
                    params->rgrc[0].bottom = g.bottom() + mm.bottom() + 1;
                }
            }

            if (result) *result = 0;
            return true;
        }
    } else if (WM_GETMINMAXINFO == lpMsg->message) {
        LPMINMAXINFO lpMinMaxInfo = reinterpret_cast<LPMINMAXINFO>(lParam);

        const QRect g = d->availableGeometry();
        const QMargins mm = d->maximizedMargins();

        lpMinMaxInfo->ptMaxPosition.x = -mm.left();
        lpMinMaxInfo->ptMaxPosition.y =  -mm.top();
        lpMinMaxInfo->ptMaxSize.x = g.right() - g.left() + 1 + mm.left() + mm.right();
        lpMinMaxInfo->ptMaxSize.y = g.bottom() - g.top() + 1 + mm.top() + mm.bottom();

        lpMinMaxInfo->ptMinTrackSize.x = max(d->window->minimumWidth() * d->scaleFactor, GetSystemMetrics(SM_CXMINTRACK));
        lpMinMaxInfo->ptMinTrackSize.y = max(d->window->minimumHeight() * d->scaleFactor, GetSystemMetrics(SM_CYMINTRACK));
        lpMinMaxInfo->ptMaxTrackSize.x = min(d->window->maximumWidth() * d->scaleFactor, GetSystemMetrics(SM_CXMAXTRACK));
        lpMinMaxInfo->ptMaxTrackSize.y = min(d->window->maximumHeight() * d->scaleFactor, GetSystemMetrics(SM_CYMAXTRACK));

        if (result) *result = 0;
        return true;
    } else if (WM_DPICHANGED == lpMsg->message) {
        qreal scaleFactor = HIWORD(wParam) < 144 ? 1.0 : 2.0;
        if (scaleFactor != d->scaleFactor) {
            d->scaleFactor = scaleFactor;
            emit scaleFactorChanged(scaleFactor);
        }

        const LPRECT suggested = reinterpret_cast<LPRECT>(lParam);
        if ((suggested->right - suggested->left) < 10) {
            SetWindowPos(reinterpret_cast<HWND>(d->window->winId()),
                         NULL,
                         suggested->left,
                         suggested->top,
                         suggested->right - suggested->left + 1,
                         suggested->bottom - suggested->top,
                         SWP_NOZORDER | SWP_NOACTIVATE);
        } else {
            SetWindowPos(reinterpret_cast<HWND>(d->window->winId()),
                         NULL,
                         suggested->left,
                         suggested->top,
                         suggested->right - suggested->left - 1,
                         suggested->bottom - suggested->top,
                         SWP_NOZORDER | SWP_NOACTIVATE);
        }

        SetWindowPos(reinterpret_cast<HWND>(d->window->winId()),
                     NULL,
                     suggested->left,
                     suggested->top,
                     suggested->right - suggested->left,
                     suggested->bottom - suggested->top,
                     SWP_NOZORDER | SWP_NOACTIVATE);
    }

    return false;
}

bool CxNativeWindowHelper::eventFilter(QObject *obj, QEvent *ev)
{
    Q_D(CxNativeWindowHelper);

    if (ev->type() == QEvent::WinIdChange) {
        d->updateWindowStyle();
    } else if (ev->type() == QEvent::Show) {
        d->updateWindowStyle();
    }

    return QObject::eventFilter(obj, ev);
}

qreal CxNativeWindowHelper::scaleFactor() const
{
    return d_func()->scaleFactor;
}

// class CxNativeWindowHelperPrivate

CxNativeWindowHelperPrivate::CxNativeWindowHelperPrivate()
    : q_ptr(nullptr)
{
}

CxNativeWindowHelperPrivate::~CxNativeWindowHelperPrivate()
{
    if (window)
        CxNativeWindowFilter::deliver(window, nullptr);
}

void CxNativeWindowHelperPrivate::updateWindowStyle()
{
    Q_Q(CxNativeWindowHelper);

    Q_CHECK_PTR(window);

    HWND hWnd = reinterpret_cast<HWND>(window->winId());
    if (oldWindow == hWnd)
        return;
    oldWindow = hWnd;

    SetWindowTheme(hWnd, L"", L"");

    CxNativeWindowFilter::deliver(window, q);

#if QT_VERSION < QT_VERSION_CHECK(5, 14, 0)
    if (window->inherits("QQuickWindow")) {
        const QOperatingSystemVersion currentVersion = QOperatingSystemVersion::current();
        if (currentVersion < QOperatingSystemVersion::Windows8) {
            return;
        }
    }
#endif

    LONG oldStyle = WS_OVERLAPPEDWINDOW | WS_THICKFRAME
            | WS_CAPTION | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX;
    LONG newStyle = WS_POPUP            | WS_THICKFRAME;

    BOOL compositionEnabled = FALSE;
    DwmIsCompositionEnabled(&compositionEnabled);
    if (compositionEnabled) {
        newStyle |= WS_CAPTION;
    }

    if (window->flags() & Qt::CustomizeWindowHint) {
        if (window->flags() & Qt::WindowSystemMenuHint)
            newStyle |= WS_SYSMENU;
        if (window->flags() & Qt::WindowMinimizeButtonHint)
            newStyle |= WS_MINIMIZEBOX;
        if (window->flags() & Qt::WindowMaximizeButtonHint)
            newStyle |= WS_MAXIMIZEBOX;
    } else {
        newStyle |= WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
    }

    const QSize maximumSize = window->maximumSize();
    if ((maximumSize.width() != QWINDOWSIZE_MAX)
            || (maximumSize.height() != QWINDOWSIZE_MAX)) {
        newStyle = newStyle & ~WS_MAXIMIZEBOX;
    }

    const LONG currentStyle = GetWindowLong(hWnd, GWL_STYLE);
    SetWindowLong(hWnd, GWL_STYLE, (currentStyle & ~oldStyle) | newStyle);

    SetWindowPos(hWnd, NULL, 0, 0, 0, 0,
                 SWP_NOOWNERZORDER | SWP_NOZORDER |
                 SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE);

    if (compositionEnabled) {
        const MARGINS margins{1, 1, 1, 1};
        DwmExtendFrameIntoClientArea(hWnd, &margins);
    }
}

int CxNativeWindowHelperPrivate::hitTest(int x, int y) const
{
    Q_CHECK_PTR(window);

    enum RegionMask {
        Client = 0x0,
        Top    = 0x1,
        Left   = 0x2,
        Right  = 0x4,
        Bottom = 0x8,
    };

    const QMargins dm = tester ? tester->draggableMargins() * scaleFactor : QMargins();

    const int top = dm.top() > 0       ? dm.top()    : GetSystemMetrics(SM_CYFRAME);
    const int left = dm.left() > 0     ? dm.left()   : GetSystemMetrics(SM_CXFRAME);
    const int right = dm.right() > 0   ? dm.right()  : GetSystemMetrics(SM_CXFRAME);
    const int bottom = dm.bottom() > 0 ? dm.bottom() : GetSystemMetrics(SM_CYFRAME);

    RECT windowRect = {0};
    HWND hWnd = reinterpret_cast<HWND>(window->winId());
    GetWindowRect(hWnd, &windowRect);
    const int result =
            (Top    * (y < (windowRect.top    + top))) |
            (Left   * (x < (windowRect.left   + left))) |
            (Right  * (x > (windowRect.right  - right))) |
            (Bottom * (y > (windowRect.bottom - bottom)));

    const bool wResizable = window->minimumWidth()  < window->maximumWidth();
    const bool hResizable = window->minimumHeight() < window->maximumHeight();

    switch (result) {
    case Top | Left    : return wResizable && hResizable ? HTTOPLEFT     : HTCLIENT;
    case Top           : return hResizable               ? HTTOP         : HTCLIENT;
    case Top | Right   : return wResizable && hResizable ? HTTOPRIGHT    : HTCLIENT;
    case Right         : return wResizable               ? HTRIGHT       : HTCLIENT;
    case Bottom | Right: return wResizable && hResizable ? HTBOTTOMRIGHT : HTCLIENT;
    case Bottom        : return hResizable               ? HTBOTTOM      : HTCLIENT;
    case Bottom | Left : return wResizable && hResizable ? HTBOTTOMLEFT  : HTCLIENT;
    case Left          : return wResizable               ? HTLEFT        : HTCLIENT;
    }

    if (tester) {
        const int x2 = (x - windowRect.left) / scaleFactor;
        const int y2 = (y - windowRect.top)  / scaleFactor;
        if (tester->hitTest(QPoint(x2, y2))) {
            return HTCAPTION;
        }
    }

    return HTCLIENT;
}

QMargins CxNativeWindowHelperPrivate::maximizedMargins() const
{
    return tester ? tester->maximizedMargins() * scaleFactor : QMargins();
}

QRect CxNativeWindowHelperPrivate::availableGeometry() const
{
    Q_CHECK_PTR(window);

    MONITORINFO monitorInfo = {0};
    monitorInfo.cbSize = sizeof(MONITORINFO);
    HWND hWnd = reinterpret_cast<HWND>(window->winId());
    HMONITOR hMonitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
    if (!hMonitor || !GetMonitorInfoW(hMonitor, &monitorInfo)) {
        Q_ASSERT(NULL != hMonitor);
        return window->screen()->availableGeometry();
    }

    return QRect(monitorInfo.rcWork.left, monitorInfo.rcWork.top, monitorInfo.rcWork.right - monitorInfo.rcWork.left, monitorInfo.rcWork.bottom - monitorInfo.rcWork.top);
}
