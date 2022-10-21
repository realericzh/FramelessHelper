#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTimer>
#include <QWindow>
#include <QScreen>
#include <QPainter>

#include "CxFramelessHelper.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent, Qt::FramelessWindowHint)
    , ui(new Ui::MainWindow())
{
    ui->setupUi(this);

    setWindowTitle("Qt Widgets Inside");

    CxFramelessHelper *helper = new CxFramelessHelper(this);
    helper->setMaximizedMargins(5, 5, 5, 5);
    helper->setDraggableMargins(8, 8, 8, 8);
    helper->setTitleBarHeight(28);

    helper->addExcludeItem(ui->minimizeButton);
    helper->addExcludeItem(ui->maximizeButton);
    helper->addExcludeItem(ui->closeButton);

    connect(ui->minimizeButton, &QPushButton::clicked,
            helper, &CxFramelessHelper::triggerMinimizeButtonAction);
    connect(ui->maximizeButton, &QPushButton::clicked,
            helper, &CxFramelessHelper::triggerMaximizeButtonAction);
    connect(ui->closeButton, &QPushButton::clicked,
            helper, &CxFramelessHelper::triggerCloseButtonAction);

    QTimer::singleShot(100, this, &MainWindow::syncPosition);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    painter.fillRect(rect(), QColor("#ff0000"));
    painter.fillRect(rect().adjusted(5, 5, -5, -5), QColor("#00ff00"));
    painter.fillRect(rect().adjusted(6, 6, -6, -6), QColor("#0000ff"));
    painter.fillRect(rect().adjusted(7, 7, -7, -7), QColor("#ff0000"));
    painter.fillRect(rect().adjusted(8, 8, -8, -8), QColor("#ffffff"));

    QFont font("Arial", 28);
    painter.setFont(font);
    painter.drawText(rect(), Qt::AlignCenter, "Qt Widget Inside");
}

void MainWindow::syncPosition()
{
    QWindow *window = windowHandle();
    QScreen *screen = window->screen();

    window->setX(screen->availableGeometry().width() / 2 - window->width() / 2);
}
