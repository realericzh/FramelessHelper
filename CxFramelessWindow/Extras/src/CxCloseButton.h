#ifndef CXCLOSEBUTTON_H
#define CXCLOSEBUTTON_H

#include <QPushButton>

class CxCloseButtonPrivate;
class CxCloseButton : public QPushButton
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(CxCloseButton)

    Q_PROPERTY(bool dark READ isDark WRITE setDark NOTIFY darkChanged)
    Q_PROPERTY(qreal radius READ radius WRITE setRadius NOTIFY radiusChanged)

public:
    explicit CxCloseButton(QWidget *parent = nullptr);
    virtual ~CxCloseButton();
protected:
    QScopedPointer<CxCloseButtonPrivate> d_ptr;

signals:
    void darkChanged(bool dark);
public:
    void setDark(bool dark);
public:
    bool isDark() const;

signals:
    void radiusChanged(qreal radius);
public:
    void setRadius(qreal radius);
public:
    qreal radius() const;

protected:
    bool eventFilter(QObject *obj, QEvent *ev) override;
    void paintEvent(QPaintEvent *) override;
};

#endif // CXCLOSEBUTTON_H
