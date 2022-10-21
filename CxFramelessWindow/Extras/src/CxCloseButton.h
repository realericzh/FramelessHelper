#ifndef CXCLOSEBUTTON_H
#define CXCLOSEBUTTON_H

#include <QPushButton>

class CxCloseButtonPrivate;
class CxCloseButton : public QPushButton
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(CxCloseButton)

    Q_PROPERTY(bool dark READ isDark WRITE setDark NOTIFY darkChanged)

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

protected:
    bool eventFilter(QObject *obj, QEvent *ev) override;
    void paintEvent(QPaintEvent *) override;
};

#endif // CXCLOSEBUTTON_H
