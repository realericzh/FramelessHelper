#include "CxMaximizeButton.h"
#include "CxMaximizeButton_p.h"

#include <QStyleOptionButton>
#include <QPainter>
#include <QEvent>
#include <QTimer>

// class CxMaximizeButton

CxMaximizeButton::CxMaximizeButton(QWidget *parent)
    : QPushButton(parent)
    , d_ptr(new CxMaximizeButtonPrivate())
{
    d_ptr->q_ptr = this;

    Q_D(CxMaximizeButton);

    setFixedSize(45, 26);

    d->blackIcon1.load(":/CxFramelessWindow/Extras/res/maximize-button1-black.png");
    d->whiteIcon1.load(":/CxFramelessWindow/Extras/res/maximize-button1-white.png");
    d->blackIcon2.load(":/CxFramelessWindow/Extras/res/maximize-button2-black.png");
    d->whiteIcon2.load(":/CxFramelessWindow/Extras/res/maximize-button2-white.png");

    while (parent) {
        d->window = parent;
        if (!d->window->parentWidget()) {
            d->window->installEventFilter(this);
            break;
        }

        parent = parent->parentWidget();
    }
}

CxMaximizeButton::~CxMaximizeButton()
{
}

void CxMaximizeButton::setDark(bool dark)
{
    Q_D(CxMaximizeButton);

    if (dark != d->dark) {
        d->dark = dark;
        emit darkChanged(dark);

        update();
    }
}

bool CxMaximizeButton::isDark() const
{
    return d_func()->dark;
}

bool CxMaximizeButton::eventFilter(QObject *obj, QEvent *ev)
{
    if (ev->type() == QEvent::WindowStateChange) {
        update();
    }

    return QWidget::eventFilter(obj, ev);
}

void CxMaximizeButton::paintEvent(QPaintEvent *)
{
    Q_D(CxMaximizeButton);

    QStyleOptionButton option;
    initStyleOption(&option);
    const QRect rc = rect();
    QPainter painter(this);

    const QPoint center = rc.center();
    const QRect iconRect(center.x() - 5, center.y() - 5, 10, 10);

    bool actived = false;
    bool maximized = false;
    if (d->window) {
        actived = d->window->isActiveWindow();
        if (d->window->windowState() & Qt::WindowMaximized) {
            maximized = true;
        }
    }

    if (d->dark) {
        if (isDown()) {
            painter.setOpacity(0.2);
            painter.fillRect(rc, Qt::white);
            painter.setOpacity(actived ? 1.0 : 0.5);
            painter.drawPixmap(iconRect, maximized ? d->whiteIcon2 : d->whiteIcon1);
        } else if (option.state & QStyle::State_MouseOver) {
            painter.setOpacity(0.1);
            painter.fillRect(rc, Qt::white);
            painter.setOpacity(actived ? 1.0 : 0.5);
            painter.drawPixmap(iconRect, maximized ? d->whiteIcon2 : d->whiteIcon1);
        } else {
            painter.setOpacity(actived ? 1.0 : 0.5);
            painter.drawPixmap(iconRect, maximized ? d->whiteIcon2 : d->whiteIcon1);
        }
    } else {
        if (isDown()) {
            painter.setOpacity(0.2);
            painter.fillRect(rc, Qt::black);
            painter.setOpacity(actived ? 1.0 : 0.5);
            painter.drawPixmap(iconRect, maximized ? d->blackIcon2 : d->blackIcon1);
        } else if (option.state & QStyle::State_MouseOver) {
            painter.setOpacity(0.1);
            painter.fillRect(rc, Qt::black);
            painter.setOpacity(actived ? 1.0 : 0.5);
            painter.drawPixmap(iconRect, maximized ? d->blackIcon2 : d->blackIcon1);
        } else {
            painter.setOpacity(actived ? 1.0 : 0.5);
            painter.drawPixmap(iconRect, maximized ? d->blackIcon2 : d->blackIcon1);
        }
    }
}


// class CxMaximizeButtonPrivate

CxMaximizeButtonPrivate::CxMaximizeButtonPrivate()
    : q_ptr(nullptr)
{
}

CxMaximizeButtonPrivate::~CxMaximizeButtonPrivate()
{
}
