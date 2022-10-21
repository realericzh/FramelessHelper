#ifndef CXMINIMIZEBUTTON_H
#define CXMINIMIZEBUTTON_H

#include <QPushButton>

class CxMinimizeButtonPrivate;
class CxMinimizeButton : public QPushButton
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(CxMinimizeButton)

    Q_PROPERTY(bool dark READ isDark WRITE setDark NOTIFY darkChanged)

public:
    explicit CxMinimizeButton(QWidget *parent = nullptr);
    virtual ~CxMinimizeButton();
protected:
    QScopedPointer<CxMinimizeButtonPrivate> d_ptr;

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

#endif // CXMINIMIZEBUTTON_H
