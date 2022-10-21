#include "CxCloseButton.h"
#include "CxCloseButton_p.h"

#include <QStyleOptionButton>
#include <QPainter>
#include <QEvent>
#include <QTimer>

// class CxCloseButton

CxCloseButton::CxCloseButton(QWidget *parent)
    : QPushButton(parent)
    , d_ptr(new CxCloseButtonPrivate())
{
    d_ptr->q_ptr = this;

    Q_D(CxCloseButton);

    setFixedSize(45, 26);

    d->blackIcon.load(":/CxFramelessWindow/Extras/res/close-button-black.png");
    d->whiteIcon.load(":/CxFramelessWindow/Extras/res/close-button-white.png");

    while (parent) {
        d->window = parent;
        if (!d->window->parentWidget()) {
            d->window->installEventFilter(this);
            break;
        }

        parent = parent->parentWidget();
    }
}

CxCloseButton::~CxCloseButton()
{
}

void CxCloseButton::setDark(bool dark)
{
    Q_D(CxCloseButton);

    if (dark != d->dark) {
        d->dark = dark;
        emit darkChanged(dark);

        update();
    }
}

bool CxCloseButton::isDark() const
{
    return d_func()->dark;
}

bool CxCloseButton::eventFilter(QObject *obj, QEvent *ev)
{
    if (ev->type() == QEvent::WindowStateChange) {
        update();
    }

    return QWidget::eventFilter(obj, ev);
}

void CxCloseButton::paintEvent(QPaintEvent *)
{
    Q_D(CxCloseButton);

    QStyleOptionButton option;
    initStyleOption(&option);
    const QRect rc = rect();
    QPainter painter(this);

    const QPoint center = rc.center();
    const QRect iconRect(center.x() - 5, center.y() - 5, 10, 10);

    bool actived = false;
    if (d->window) {
        actived = d->window->isActiveWindow();
    }

    if (isDown()) {
        painter.fillRect(rc, QColor("#8c0a15"));
        painter.setOpacity(actived ? 1.0 : 0.5);
        painter.drawPixmap(iconRect, d->whiteIcon);
    } else if (option.state & QStyle::State_MouseOver) {
        painter.fillRect(rc, QColor("#e81123"));
        painter.setOpacity(actived ? 1.0 : 0.5);
        painter.drawPixmap(iconRect, d->whiteIcon);
    } else if (d->dark) {
        painter.setOpacity(actived ? 1.0 : 0.5);
        painter.drawPixmap(iconRect, d->whiteIcon);
    } else {
        painter.setOpacity(actived ? 1.0 : 0.5);
        painter.drawPixmap(iconRect, d->blackIcon);
    }
}

// class CxCloseButtonPrivate

CxCloseButtonPrivate::CxCloseButtonPrivate()
    : q_ptr(nullptr)
{
}

CxCloseButtonPrivate::~CxCloseButtonPrivate()
{
}
