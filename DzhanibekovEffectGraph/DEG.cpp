#include <QTimer>
#include <iostream>
#include "DEG.h"
#include "ui_DEG.h"

#include <qwt_plot_canvas.h>
#include <qwt_legend.h>
#include <qwt_plot_curve.h>

using std::cerr;
using std::endl;

DEG::DEG(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DEG)
{
    ui->setupUi(this);

    connect(&timer_auto, SIGNAL(timeout()), this, SLOT(timer_auto_update()));

    plot_init();

    //timer_auto.start(timer_auto_interval);

    value = 0;
    p = ui->p->value();
    q = ui->q->value();
    r = ui->r->value();

    A = ui->A->value();
    B = ui->B->value();
    C = ui->C->value();

    timer_auto_interval = ui->timer->value();
    time = 0;
}

DEG::~DEG()
{
    delete ui;
}

void DEG::plot_init()
{
    plot_reset_data();

    ui->plot->canvas()->setPaintAttribute(QwtPlotCanvas::PaintCached, false);
    ui->plot->canvas()->setPaintAttribute(QwtPlotCanvas::PaintPacked, false);
    ui->plot->insertLegend(new QwtLegend(), QwtPlot::BottomLegend);

    // Insert new curves
    QwtPlotCurve *plot_p_ = new QwtPlotCurve("p");
    plot_p_->attach(ui->plot);
    QwtPlotCurve *plot_q_ = new QwtPlotCurve("q");
    plot_q_->attach(ui->plot);
    QwtPlotCurve *plot_r_ = new QwtPlotCurve("r");
    plot_r_->attach(ui->plot);

    ui->plot->setAxisScale(QwtPlot::yLeft, -10, 10);

    // Set curve styles
    plot_p_->setPen(QPen(Qt::red));
    plot_q_->setPen(QPen(Qt::green));
    plot_r_->setPen(QPen(Qt::blue));

    // Attach (don't copy) data.
    plot_p_->setRawData(plot_time, plot_p, plot_size);
    plot_q_->setRawData(plot_time, plot_q, plot_size);
    plot_r_->setRawData(plot_time, plot_r, plot_size);

    ui->plot->setAxisTitle(QwtPlot::xBottom, "Time [s]");
    ui->plot->setAxisTitle(QwtPlot::yLeft, "Angular Velocity [rad/s]");
}

void DEG::plot_reset_data()
{
    for(int i = 0; i < plot_size; i++)
    {
        plot_time[i] = 0;

        plot_p[i] = 0;
        plot_q[i] = 0;
        plot_r[i] = 0;
    }
}

void DEG::plot_update()
{
    int plot_current = plot_size - 1;

    long double dt_seconds = plot_mytime.get_time_difference() / 1E3;

    //shifting values
    for(int i = 0; i < plot_size - 1; i++)
    {
        plot_time[i] = plot_time[i + 1];

        plot_p[i] = plot_p[i + 1];
        plot_q[i] = plot_q[i + 1];
        plot_r[i] = plot_r[i + 1];
    }

    plot_time[plot_current] = plot_time[plot_current - 1] + dt_seconds;

    //for first run seconds
    for(int i = plot_size - 2; i >= 0; i--)
        if(plot_time[i] == 0) plot_time[i] = plot_time[i + 1] - dt_seconds;

    plot_p[plot_current] = p;
    plot_q[plot_current] = q;
    plot_r[plot_current] = r;

    ui->plot->setAxisScale(QwtPlot::xBottom, plot_time[0], plot_time[plot_current]);
    ui->plot->replot();

    //for dt_seconds
    plot_mytime.set_time();
}

void DEG::step()
{
    dp = (B - C) / A * q * r * dt;
    dq = (C - A) / B * r * p * dt;
    dr = (A - B) / C * p * q * dt;


    p += dp;
    q += dq;
    r += dr;
}

void DEG::updateInfo()
{
    double alpha, beta, epsilon;

    X = A * p;
    Y = B * q;
    Z = C * r;

    Tx2 = X * p + Y * q + Z * r;
    alpha = sqrt(((A - B) * (B - C) * Tx2) / (A * B * C));
    epsilon = pow(X, 2) + pow(Y, 2) + pow(Z, 2) - Tx2 * B;
    beta = (A - C) * fabs(epsilon) / Tx2 / (A - B) / (B - C);
    //periodTheoretical = 2 / alpha * log(16 * A * B * C * pow(alpha, 2) / (A - C) / epsilon) / log(M_E);

    periodTheoretical = 2 / alpha;
    periodTheoretical *= log(32 * Tx2 / 2 * (A - B) * (B - C) / fabs(epsilon) / (A - C)) / log(M_E);

    rotationTimeTheoretical = 2 * (1.47222 - 1.55227 * beta) / alpha;

    ui->T_2->setValue(Tx2);
    ui->result_t->setValue(periodTheoretical);
    ui->eps->setValue(epsilon);
    cerr << epsilon << endl;
    ui->result1_t->setValue(rotationTimeTheoretical);
}

void DEG::timer_auto_update()
{
    static double prev_dq;
    dt = plot_mytime.get_time_difference() / 1.E3;

    if(!plot_mytime.is_set())
    {
        plot_mytime.set_time();
        time = 0;
    }
    else if(dt)
    {
        step();

        if(prev_dq > 0 && dq < 0 && time > epsTime)
        {
            ui->result->setValue(time);
            if(ui->PeriodStop->isChecked())
                on_pushButton_pause_clicked();
        }

        time += dt;
        prev_dq = dq;
        plot_update();
    }
}

void DEG::on_pushButton_reset_clicked()
{
    plot_mytime.reset();
    plot_reset_data();
    timer_auto_interval = ui->timer->value();

    p = ui->p->value();
    q = ui->q->value();
    r = ui->r->value();

    A = ui->A->value();
    B = ui->B->value();
    C = ui->C->value();

    time = 0;

    updateInfo();
}

void DEG::on_pushButton_pause_clicked()
{
    if(timer_auto.isActive())
    {
        timer_auto.stop();
        ui->pushButton_pause->setText("Start");
        time = 0;
    }
    else
    {
        time = 0;
        plot_reset_data();
        plot_mytime.reset();
        ui->pushButton_pause->setText("Pause");
        updateInfo();
        timer_auto.start(timer_auto_interval);
    }
}

void DEG::on_timer_valueChanged(int arg1)
{
    timer_auto_interval = arg1;
}

void DEG::on_A_valueChanged(double arg1)
{
    A = arg1;
}

void DEG::on_B_valueChanged(double arg1)
{
    B = arg1;
}

void DEG::on_C_valueChanged(double arg1)
{
    C = arg1;
}

void DEG::on_p_valueChanged(double arg1)
{
    p = arg1;
}

void DEG::on_q_valueChanged(double arg1)
{
    q = arg1;
}

void DEG::on_r_valueChanged(double arg1)
{
    r = arg1;
}
