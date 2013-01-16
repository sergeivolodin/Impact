#ifndef DEG_H
#define DEG_H

#include <QMainWindow>
#include "qtimer.h"
#include "mytime.h"

#define DESKTOP

namespace Ui {
class DEG;
}

class DEG : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit DEG(QWidget *parent = 0);
    ~DEG();
    
private:
    Ui::DEG *ui;

    //plot
    static const int plot_size = 200 + 1;
    double plot_p[plot_size], plot_q[plot_size], plot_r[plot_size], plot_time[plot_size];

    //values
    double value, prev_value, value_speed;

    QTimer timer_auto;

    double timer_auto_interval;
    mytime plot_mytime;

    void plot_init();
    void plot_reset_data();
    void plot_update();

    void step();

    double A, B, C, p, q, r, dp, dq, dr, dt, time;

    double X, Y, Z, Tx2, periodTheoretical, rotationTimeTheoretical;

    static const double epsCheck = 0.0015, epsTime = 1;

    void updateInfo();

private slots:
    void timer_auto_update();

    void on_pushButton_reset_clicked();
    void on_pushButton_pause_clicked();
    void on_timer_valueChanged(int arg1);
    void on_A_valueChanged(double arg1);
    void on_B_valueChanged(double arg1);
    void on_C_valueChanged(double arg1);
    void on_p_valueChanged(double arg1);
    void on_q_valueChanged(double arg1);
    void on_r_valueChanged(double arg1);
};

#endif // DEG_H
