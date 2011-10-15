#ifndef BUTTONAREA_H
#define BUTTONAREA_H

#include <QWidget>

class Buttonarea : public QWidget
{
    Q_OBJECT
public:
    explicit Buttonarea(QWidget *parent = 0);
    void updateYears(int a, int b);

private:
    void paintEvent(QPaintEvent *);
    int oldest;
    int newest;

};

#endif // BUTTONAREA_H
