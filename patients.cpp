#include "patients.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlQueryModel>
#include<QObject>
patients::patients()
{

id=0;
    nom=" ";prenom=" ";ville=" ";age=0;
}
patients::patients(int id,QString nom ,QString prenom,QString ville,int age)

{ this->id=id;    this->nom=nom; this ->prenom=prenom;this->ville=ville;this->age=age;}
int patients::getid(){return id;}
    QString patients::getnom(){return nom ;}
   QString patients:: getprenom(){return prenom;}
   QString patients::getville(){return ville ;}
   int patients::getage(){return age;}
   void patients::setid(int id){this->id=id;};
   void patients::setnom(QString nom){this->nom=nom;}
   void patients::setprenom(QString prenom){this->prenom=prenom;}
   void patients::setville(QString ville){this->ville=ville;};

   void patients::setage(int age){this->age=age;};
bool patients::ajouter()
{bool test=false;
    QSqlQuery query;

          query.prepare("INSERT INTO PATIENTS (id,nom, prenom, ville,age) "
                        "VALUES (:id,:nom, :prenom, :ville,:age)");
           query.bindValue(":id",id);
          query.bindValue(":nom", nom);
          query.bindValue(":prenom", prenom);
          query.bindValue(":ville", ville);
          query.bindValue(":age", age);

          query.exec();
          return test;

}
bool patients::supprimer(int id)
{ QSqlQuery query;
    query.prepare("Delete from patients where id=:id");
     query.bindValue(0,id);

    query.exec();
}

          QSqlQueryModel* patients::afficher(){

              QSqlQueryModel* model=new QSqlQueryModel();
                   model->setQuery("SELECT * FROM patients");
                   model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
                   model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
                   model->setHeaderData(3, Qt::Horizontal, QObject::tr("ville"));
                   model->setHeaderData(4, Qt::Horizontal, QObject::tr("age"));
                   model->setHeaderData(5, Qt::Horizontal, QObject::tr("id"));

              return model;


}
          bool patients::modifier(int id ,QString nom,QString prenom,QString ville,int age)
          {
              QSqlQuery query;
              query.prepare("UPDATE PATIENTS SET id= :id,nom= :nom,prenom = :prenom,ville=:ville,age=:age  WHERE id= :id ");
              query.bindValue(":id",id);
              query.bindValue(":nom",nom);
              query.bindValue(":prenom",prenom);
             query.bindValue(":ville",ville);
             query.bindValue(":age",age);

              return    query.exec();
          }
          QSqlQueryModel *patients::trinom()
          {
              QSqlQueryModel * model= new QSqlQueryModel();

              model->setQuery("select * from patients ORDER BY nom ");
              model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
              model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
              model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
              model->setHeaderData(3, Qt::Horizontal, QObject::tr("ville"));
              model->setHeaderData(4, Qt::Horizontal, QObject::tr("age"));
              return model;
}
          QSqlQueryModel *patients::triage()
          {
              QSqlQueryModel * model= new QSqlQueryModel();

              model->setQuery("select * from patients ORDER BY age ");
              model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
              model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
              model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
              model->setHeaderData(3, Qt::Horizontal, QObject::tr("ville"));
              model->setHeaderData(4, Qt::Horizontal, QObject::tr("age"));


                  return model;
          }
          QSqlQueryModel *patients::triid()
          {
              QSqlQueryModel * model= new QSqlQueryModel();

              model->setQuery("select * from patients ORDER BY id ");
              model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
              model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
              model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
              model->setHeaderData(3, Qt::Horizontal, QObject::tr("ville"));
              model->setHeaderData(4, Qt::Horizontal, QObject::tr("age"));


                  return model;
          }
          QSqlQueryModel* patients::recherche(QString recherche){
              QSqlQueryModel* model = new QSqlQueryModel();

             model->setQuery("SELECT * FROM patients WHERE nom LIKE '%"+recherche+"%' OR prenom LIKE '%"+recherche+"%' OR ville LIKE '%"+recherche+"%'");
              model->setHeaderData(0,Qt::Horizontal,QObject::tr("id"));
              model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
              model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
              model->setHeaderData(4,Qt::Horizontal,QObject::tr("ville "));
              model->setHeaderData(5,Qt::Horizontal,QObject::tr("age"));


              return model;
          }

          //stat

          int patients::statistique1(){
              QSqlQuery query;
                      int count=0 ;
                      QSqlQuery requete("select * from patients where age >13 ") ;
                      while(requete.next())
                      {
                              count++ ;
                      }

                  return count ;
          }

          int patients::statistique2(){
              QSqlQuery query;
                      int count=0 ;
                      QSqlQuery requete("select * from patients where age <=13 ") ;
                      while(requete.next())
                      {
                              count++ ;
                      }

                  return count ;
          }

          //pdf
          QSqlQueryModel * patients:: getAllId(){
              QSqlQueryModel * model =new QSqlQueryModel();
                      model->setQuery("select id from patients ");
                      return model ;
          }

          patients* patients::readpatients (QString val)
          {
           QSqlQuery query;
              query.prepare("Select * FROM patients where id='"+val+"'");
                  if(query.exec())
                  {     while(query.next())
                      {
                       setid(query.value(0).toInt());
                       setnom(query.value(1).toString());
                       setprenom(query.value(2).toString());
                       setville(query.value(3).toString());
                       setage (query.value(4).toInt());
                      }
                  }
               return this;
          }

