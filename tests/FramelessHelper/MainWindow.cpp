#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTimer>
#include <QWindow>
#include <QScreen>
#include <QPainter>
#include <QPainterPath>

#include "CxFramelessHelper.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent, Qt::FramelessWindowHint)
    , ui(new Ui::MainWindow())
{
    ui->setupUi(this);

    setAttribute(Qt::WA_TranslucentBackground);

    setWindowTitle("Qt Widgets Inside");

    CxFramelessHelper *helper = new CxFramelessHelper(this);
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
    painter.setRenderHint(QPainter::Antialiasing);
    QPainterPath path;
    path.addRoundedRect(rect(), 4, 4);
    painter.setClipPath(path);

    QImage backgroundImage(QStringLiteral(":/tests/res/background.png"));
    painter.drawImage(contentsRect(), backgroundImage);

    QFont font("Arial", 28);
    painter.setFont(font);
    painter.drawText(rect(), Qt::AlignCenter, "Qt Widget Inside");
}

void MainWindow::syncPosition()
{
    QWindow *window = windowHandle();
    QScreen *screen = window->screen();

    window->setX(screen->availableGeometry().width() / 2 + 10);
}
