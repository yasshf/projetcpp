#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "patients.h"
#include "statistiques.h"
#include <QPrinter>
#include <QPainter>
#include <QIntValidator>
#include <QMessageBox>
#include <audiorecorder.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_4->setValidator(new QIntValidator (0,100,this));
    ui->lineEdit_5->setValidator(new QIntValidator (0,9999,this));
    ui->lineEdit_idm->setValidator(new QIntValidator (0,9999));
    ui->lineEdit_agem->setValidator(new QIntValidator (0,9999));
    ui->tab_patients->setModel(p.afficher());
    minute =0;
    seconde=0;
    lent=false;
    connect(&horloge,SIGNAL(timeout()),this,SLOT(processus()));
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_pb_ajouter_clicked()
{   int id=ui->lineEdit_5->text().toInt();
    QString nom=ui->lineEdit->text();
      QString prenom=ui->lineEdit_2->text();
      QString ville=ui->lineEdit_3->text();
      int age=ui->lineEdit_4->text().toInt();

    patients p(id,nom,prenom,ville,age);
    bool test = p.ajouter();
    if(test)
    {
ui->tab_patients->setModel(p.afficher());
        QMessageBox::information(nullptr, QObject::tr("non ajouter"),
                          QObject::tr("patient non modifiée.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("ajouter patient"),
                    QObject::tr("ajouteé !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tab_patients->setModel(p.afficher());
}






void MainWindow::on_pb_supp_clicked()
{
    patients p1; p1.setid(ui->lineEdit_supp->text().toUInt());
    bool test=p1.supprimer(p1.getid());
    QMessageBox msgbox;
            if(test)
            { ui->tab_patients->setModel(p.afficher());
                QMessageBox::information(nullptr, QObject::tr("Supprimer"),
                            QObject::tr("Suppression Terminer.\n"), QMessageBox::Ok);

           }

}

void MainWindow::on_pb_modifier_clicked()
{
    int id = ui->lineEdit_idm->text().toInt();
        QString nom= ui->lineEdit_nomm->text();
        QString prenom= ui->lineEdit_prenomm->text();
         QString ville= ui->lineEdit_villem->text();
         int age = ui->lineEdit_agem->text().toInt();



                patients p;
                bool test=p.modifier(id,nom,prenom,ville,age);

                if(test)
                {

                    QMessageBox::information(nullptr, QObject::tr("modifie un patient"),
                                      QObject::tr("patient  modifiée.\n"
                                                  "Click Cancel to exit."), QMessageBox::Cancel);
                    ui->tab_patients->setModel(p.afficher());
                }
                else
                    QMessageBox::critical(nullptr, QObject::tr("non modifie"),
                                QObject::tr("Erreur !.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);
                    ui->tab_patients->setModel(p.afficher());
}


void MainWindow::on_cancel_clicked()
{
    close();
}

void MainWindow::on_cancel_2_clicked()
{
    close();
}

void MainWindow::on_cancel_3_clicked()
{
    close();
}

void MainWindow::on_tri_id_clicked()
{
  ui->tab_patients->setModel(p.triid());
}

void MainWindow::on_tri_age_clicked()
{
    ui->tab_patients->setModel(p.triage());
}

void MainWindow::on_tri_nom_clicked()
{
    ui->tab_patients->setModel(p.trinom());
}

void MainWindow::on_rech_clicked()
{
    QString rech=ui->le_rec_id->text();
     ui->tab_patients->setModel(p.recherche(rech));
}

void MainWindow::on_pb_stat_clicked()
{
    statistiques S;
     S.setModal(true);
     S.exec();
}

void MainWindow::on_pdf_push_clicked()
{
    QString id_cb=ui->pdf_c->text();
    patients * En ;
    En=p.readpatients(id_cb);
    QString id_string=QString::number(En->getid());
    QString nom_string = En->getnom();
    QString prenom_string = En->getprenom();
    QString ville_string = En->getville();
    QString age_string=QString::number(En->getage());



     QPrinter printer;
                printer.setOutputFormat(QPrinter::PdfFormat);
                printer.setOutputFileName("C:/Users/HP/Desktop/PDF/"+id_string+".pdf");
                           QPainter painter;
                           if(! painter.begin(&printer))
                           { qWarning("failed to open file");  }
                            painter.setFont(QFont("Sitka Heading", 25));
                            painter.setPen(Qt::blue);
                            painter.drawText(340,100," ADPH ");
                            painter.setPen(Qt::black);
                            painter.drawText(175,50,"Information relative au patients");
                            painter.setPen(Qt::black);
                            painter.drawText(250,300,"Identifiant : " + id_string);
                            painter.drawText(250,400,"Nom : "+nom_string);
                            painter.drawText(250,500,"Prenom : "+prenom_string);
                            painter.drawText(250,600,"ville : "+ville_string);
                            painter.drawText(250,700,"Age : " +age_string);
                            painter.end();
}

void MainWindow::on_pb_start_clicked()
{
   horloge.start(1000);
}

void MainWindow::on_pb_pause_clicked()
{
if(lent==false)
{
    horloge.stop();
    lent=true;

}
else {
    lent=false;
    horloge.start(1000);
}
}

void MainWindow::on_pb_stop_clicked()
{
minute=0;
seconde=0;
lent=false;
ui->minute->display(minute);
ui->seconde->display(seconde);
horloge.stop();

}

void MainWindow::processus()
{
    seconde=seconde+1;
    if(seconde==60)
    {
        seconde=0;
        minute=minute+1;
    }
    else
    {
      ui->seconde->display(seconde);
      ui->minute->display(minute);
    }
}

