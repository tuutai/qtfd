#ifndef POPUP_H
#define POPUP_H

#include <QDialog>

namespace Ui {
    class popup;
}

class popup : public QDialog
{
    Q_OBJECT

public:
    explicit popup(QWidget *parent = 0);
    void setTopic(const QString *s);
    void setImage(const QString *s);
    void setDescription(const QString *s);
    ~popup();

private:
    Ui::popup *ui;
};

#endif // POPUP_H
