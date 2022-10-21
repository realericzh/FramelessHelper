#include "CxMinimizeButton.h"
#include "CxMinimizeButton_p.h"

#include <QStyleOptionButton>
#include <QPainter>
#include <QEvent>
#include <QTimer>

// class CxMinimizeButton

CxMinimizeButton::CxMinimizeButton(QWidget *parent)
    : QPushButton(parent)
    , d_ptr(new CxMinimizeButtonPrivate())
{
    d_ptr->q_ptr = this;

    Q_D(CxMinimizeButton);

    setFixedSize(45, 26);

    d->blackIcon.load(":/CxFramelessWindow/Extras/res/minimize-button-black.png");
    d->whiteIcon.load(":/CxFramelessWindow/Extras/res/minimize-button-white.png");

    while (parent) {
        d->window = parent;
        if (!d->window->parentWidget()) {
            d->window->installEventFilter(this);
            break;
        }

        parent = parent->parentWidget();
    }
}

CxMinimizeButton::~CxMinimizeButton()
{
}

void CxMinimizeButton::setDark(bool dark)
{
    Q_D(CxMinimizeButton);

    if (dark != d->dark) {
        d->dark = dark;
        emit darkChanged(dark);

        update();
    }
}

bool CxMinimizeButton::isDark() const
{
    return d_func()->dark;
}

bool CxMinimizeButton::eventFilter(QObject *obj, QEvent *ev)
{
    if (ev->type() == QEvent::WindowStateChange) {
        update();
    }

    return QWidget::eventFilter(obj, ev);
}

void CxMinimizeButton::paintEvent(QPaintEvent *)
{
    Q_D(CxMinimizeButton);

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

    if (d->dark) {
        if (isDown()) {
            painter.setOpacity(0.2);
            painter.fillRect(rc, Qt::white);
            painter.setOpacity(actived ? 1.0 : 0.5);
            painter.drawPixmap(iconRect, d->whiteIcon);
        } else if (option.state & QStyle::State_MouseOver) {
            painter.setOpacity(0.1);
            painter.fillRect(rc, Qt::white);
            painter.setOpacity(actived ? 1.0 : 0.5);
            painter.drawPixmap(iconRect, d->whiteIcon);
        } else {
            painter.setOpacity(actived ? 1.0 : 0.5);
            painter.drawPixmap(iconRect, d->whiteIcon);
        }
    } else {
        if (isDown()) {
            painter.setOpacity(0.2);
            painter.fillRect(rc, Qt::black);
            painter.setOpacity(actived ? 1.0 : 0.5);
            painter.drawPixmap(iconRect, d->blackIcon);
        } else if (option.state & QStyle::State_MouseOver) {
            painter.setOpacity(0.1);
            painter.fillRect(rc, Qt::black);
            painter.setOpacity(actived ? 1.0 : 0.5);
            painter.drawPixmap(iconRect, d->blackIcon);
        } else {
            painter.setOpacity(actived ? 1.0 : 0.5);
            painter.drawPixmap(iconRect, d->blackIcon);
        }
    }
}

// class CxMinimizeButtonPrivate

CxMinimizeButtonPrivate::CxMinimizeButtonPrivate()
    : q_ptr(nullptr)
{
}

CxMinimizeButtonPrivate::~CxMinimizeButtonPrivate()
{
}
