#ifndef CXMAXIMIZEBUTTON_H
#define CXMAXIMIZEBUTTON_H

#include <QPushButton>

class CxMaximizeButtonPrivate;
class CxMaximizeButton : public QPushButton
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(CxMaximizeButton)

    Q_PROPERTY(bool dark READ isDark WRITE setDark NOTIFY darkChanged)

public:
    explicit CxMaximizeButton(QWidget *parent = nullptr);
    virtual ~CxMaximizeButton();
protected:
    QScopedPointer<CxMaximizeButtonPrivate> d_ptr;

signals:
    void darkChanged(bool dark);
public:
    void setDark(bool dark);
public:
    bool isDark() const;

protected:
    bool eventFilter(QObject *obj, QEvent *ev) override;
    void paintEvent(QPaintEvent *) override;
};

#endif // CXMAXIMIZEBUTTON_H
