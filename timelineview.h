#ifndef TIMELINEVIEW_H
#define TIMELINEVIEW_H

#include <QDialog>

namespace Ui {
    class TimeLineView;
}

class TimeLineView : public QDialog
{
    Q_OBJECT

public:
    explicit TimeLineView(QWidget *parent = 0);
    void timeline_reload();
    ~TimeLineView();

private:
    Ui::TimeLineView *ui;
};

#endif // TIMELINEVIEW_H
