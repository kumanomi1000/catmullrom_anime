#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent)
, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	px = QPixmap(ui->label->size());
	timer1.setSingleShot(true);
	connect(&timer1, SIGNAL(timeout()), this, SLOT(timeout()));
	pt.begin(&px);
	p<<QPointF(213,53);
	p<<QPointF(133,80);
	p<<QPointF(53,240);
	p<<QPointF(267,267);
	p<<p[0];
	p<<p[1];
	p<<p[2];
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_pushButton_clicked()
{
	b=true;
	idx=0;
	draw();
	idx = 1;
	timer1.start(100);
}

void MainWindow::timeout()
{
	draw();
	++idx;
	if(idx>=100){
		idx=0;
		b=false;
	}
	timer1.start(100);
}

void MainWindow::draw()
{
	px.fill();
	for(int i=0;i<4;i++){
		pt.setPen(Qt::black);
		pt.setBrush(Qt::NoBrush);
		pt.drawEllipse(p[i],5,5);
	}
	int i=idx/25;
	double t=(idx%25)*0.04;
	{
		tn=0.5;
		double a0=-tn*t+2*tn*t*t-tn*t*t*t;
		double a1=1+(tn-3)*t*t+(2-tn)*t*t*t;
		double a2=tn*t+(3-2*tn)*t*t+(tn-2)*t*t*t;
		double a3=-tn*t*t+tn*t*t*t;
		QPointF cp=a0*p[i]+a1*p[i+1]+a2*p[i+2]+a3*p[i+3];
		pt.setPen(Qt::NoPen);
		pt.setBrush(Qt::green);
		pt.drawEllipse(cp,5,5);
	}
	{
		tn=1.0;
		double a0=-tn*t+2*tn*t*t-tn*t*t*t;
		double a1=1+(tn-3)*t*t+(2-tn)*t*t*t;
		double a2=tn*t+(3-2*tn)*t*t+(tn-2)*t*t*t;
		double a3=-tn*t*t+tn*t*t*t;
		QPointF cp=a0*p[i]+a1*p[i+1]+a2*p[i+2]+a3*p[i+3];
		pt.setPen(Qt::NoPen);
		pt.setBrush(Qt::red);
		pt.drawEllipse(cp,5,5);
	}
	{
		tn=0.2;
		double a0=-tn*t+2*tn*t*t-tn*t*t*t;
		double a1=1+(tn-3)*t*t+(2-tn)*t*t*t;
		double a2=tn*t+(3-2*tn)*t*t+(tn-2)*t*t*t;
		double a3=-tn*t*t+tn*t*t*t;
		QPointF cp=a0*p[i]+a1*p[i+1]+a2*p[i+2]+a3*p[i+3];
		pt.setPen(Qt::NoPen);
		pt.setBrush(Qt::blue);
		pt.drawEllipse(cp,5,5);
	}
	ui->label->setPixmap(px);
	if(b)
		px.save(QString("%1.png").arg(idx,2,10,QChar('0')));
}
