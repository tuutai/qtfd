#ifndef TIMELINE_H
#define TIMELINE_H

#include <QWidget>

class Timeline : public QWidget
{
    Q_OBJECT
public:
    explicit Timeline(QWidget *parent = 0);
    void updateYears(int a, int b);

private:
    void paintEvent(QPaintEvent *);
    int oldest;
    int newest;

};

#endif // TIMELINE_H
