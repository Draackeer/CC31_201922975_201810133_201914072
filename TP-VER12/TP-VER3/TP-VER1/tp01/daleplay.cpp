#include "daleplay.h"
#include "ui_daleplay.h"
#include "string"
#include "ListaReproduccion.h"
#include "Tree.h"
#include "Publicacion.h"
#include "QFile"
#include <functional>
using namespace std;

Publicacion* actualPublicacion = nullptr;
QStringList comentarios_ini;
QString usuario_actual; // = actualPublicacion->GetUsuario();
DalePlay::DalePlay(QWidget *parent) : QMainWindow(parent), ui(new Ui::DalePlay)

{
    srand(1);

    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(2);
    setFixedSize(ui->SingUpFond->width(), ui->SingUpFond->height()+25);
    QPushButton* btnCanciones[10];
    for(int i=0;i<10;i++){
        QString btnName="Cancion"+QString::number(i+1);
        btnCanciones[i]=DalePlay::findChild<QPushButton*>(btnName);
        connect(btnCanciones[i],SIGNAL(released()),this,SLOT(on_btnCanciones_clicked()));
    }
    //ARBOLES
    this->arbolNombre = new BST<Publicacion*,QString>([](Publicacion* p){return p->GetNombre();});
    this->arbolFecha = new BST<Publicacion*,QString>([](Publicacion* p){return p->GetFecha();});
    this->arbolContenido = new BST<Publicacion*,QString>([](Publicacion* p){return p->GetContenido();});
    this->arbolInteraccion = new BST<Publicacion*,int>([](Publicacion* p){return p->Getinteraccion();});
    this->arbolPosicion = new BST<Publicacion*,int>([](Publicacion* p){return p->GetPosicion();});
    //cargar_comentarios();
    //cargar_publicaciones();
    if(cfile.IsNull()){
        cargar_todo();
    }
    else{
        cargar_todoTxt();
    }
    arbolFecha->postorder_50(ui->ListaPubIn);
    ui->ListaPubIn->setCurrentRow(0);
    ui->pushButton->setVisible(false);
    //Esto lo utilizamos en el botón de inicio o cualquier otro para guardar la info
    //guardar_todo();
}

DalePlay::~DalePlay()
{
    delete ui;
}
/*void DalePlay::guardar_todo(){
    QFile file("publications2.tsv");
    QFile file2("users2.tsv");
    QFile file3("comments2.tsv");
        if(file.open(QIODevice::WriteOnly)&&
           file2.open(QIODevice::WriteOnly)&&
           file3.open(QIODevice::WriteOnly)){ //WriteOnly
            QTextStream publications(&file);
            QTextStream users(&file2);// in << palabras[1] << "\n";
            QTextStream comments(&file3);
            queue<Node<Publicacion*>*> q;
            q.push(arbolNombre->root);
            int i = 0;
            while(q.empty()==false){
                Node<Publicacion*>* actualNodo = q.front();
                i++;
                Publicacion* actual = actualNodo->data;

                for(int j = 0; j <actual->GetComentarios().size(); j++ ){
                publications<<(j+1)+i<<"\t"<<
                     QString::number(actual->Getinteraccion())<<"\t"<<
                     actual->GetComentarios()[j]<<"\t"<<
                     actual->GetNombre()<<"\t"<<
                     10<<"\t"<<
                     actual->Getinteraccion()<<"\n";
                }

                users<<i<<"\t"<<
                       "@"<<"\t"<<
                       actual->GetNombre()<<"\t"<<
                       actual->GetFecha()<<"\n";

                comments<<i<<"\t"<<
                        i<<"\t"<<
                        actual->GetFecha()<<"\t"<<
                        actual->GetContenido()<<"\n";

                q.pop();
                if(actualNodo->left != NULL) q.push(actualNodo->left);
                if(actualNodo->right != NULL) q.push(actualNodo->right);

            }
            file.close();
        }
}
void DalePlay::cargar_comentarios(){
    //QFile archivo("publications2.tsv");
    QFile archivo("publications.tsv");
    if(archivo.open(QIODevice::ReadOnly)){
        QTextStream in(&archivo);
        while(!in.atEnd()){
            QString linea = in.readLine();
            QStringList data = linea.split("\t");
            QString comentario = data[3] +"   "+data[2];
            comentarios_ini.push_back(comentario);
        }
        archivo.close();
    }
}

void DalePlay::cargar_publicaciones(){
   // QFile archivo3("publications2.tsv");
   // QFile archivo2("users2.tsv");
   // QFile archivo("comments2.tsv");

    QFile archivo("comment.tsv");
    QFile archivo2("users.tsv");
    QFile archivo3("publications.tsv");
    if(archivo.open(QIODevice::ReadOnly)){
        QTextStream in(&archivo);
        while(!in.atEnd()){
            QString linea = in.readLine();
            QStringList data = linea.split("\t");
            QString comentario = data[3] +"   "+data[2];
            comentarios_ini.push_back(comentario);
        }
        archivo.close();
    }
    if(archivo.open(QIODevice::ReadOnly)&&archivo2.open(QIODevice::ReadOnly)&&archivo3.open(QIODevice::ReadOnly)){
        QTextStream in(&archivo);
        QTextStream in2(&archivo2);
        QTextStream in3(&archivo3);
        int cont=0;
        while(!in.atEnd() && !in2.atEnd() && !in3.atEnd()){
            cont++;
            QString linea = in.readLine();
            QStringList data = linea.split("\t");

            QString linea2 = in2.readLine();
            QStringList data2 = linea2.split("\t");

            QString linea3 = in3.readLine();
            QStringList data3 = linea3.split("\t");

            QString fecha = data[2]; //COMMENT
            QString interaccion = data3[5]; //PUBLICATIONS
            int n_comentarios = rand()%100+5;
            QStringList coments;
            for (int i = 0; i < n_comentarios; i++){

                coments.push_back(comentarios_ini[rand()%comentarios_ini.size()]);
            }                               //USERS        //COMMENT

            Publicacion* p = new Publicacion(data2[1],fecha,data[3],coments,0,cont,cantPublicaciones,interaccion.toInt());
            cantPublicaciones++;
            agregar_publicacion(p);
        }
        archivo.close();
        archivo2.close();
        archivo3.close();
    }
}*/

string DalePlay::QStoS(QString sdato){
    string sadd;
    sadd.resize(sdato.size());
    for(int i=0;i<sdato.size();i++) sadd[i]=sdato[i].toLatin1();
    return sadd;
}
QString DalePlay::StoQS(string s){
    QString qs;
    int sn=(int)s.size();
    qs.resize(sn);
    for(int j=0;j<sn;j++){
        qs[j]=s[j];
    }
    return qs;
}
void DalePlay::cargar_todoTxt(){
    ifstream fdatosr;
    fdatosr.open("datos.txt",ios::in);
    string garbage;
    int lenaux;
    int cuentasx;
    fdatosr>>cuentasx;
    fdatosr.ignore();
    for(int i=0;i<cuentasx;i++){
        QString nickname;
        fdatosr>>garbage;
        nickname=StoQS(garbage);
        fdatosr>>garbage;
        int size3,size4,size5,size6,size7;
        for(int j=0;j<3;j++){
            fdatosr>>lenaux;
            fdatosr.ignore();
            for(int k=0;k<lenaux;k++) {
                getline(fdatosr,garbage);
            }
        }
        fdatosr>>size3;
        QString aux3[size3];
        fdatosr.ignore();
        for(int k=0;k<size3;k++) {
            getline(fdatosr,garbage);
            aux3[k]=StoQS(garbage);
        }

        fdatosr>>size4;
        QString aux4[size4];
        fdatosr.ignore();
        for(int k=0;k<size4;k++) {
            getline(fdatosr,garbage);
            aux4[k]=StoQS(garbage);
        }

        fdatosr>>size5;
        QString aux5[size5];
        fdatosr.ignore();
        for(int k=0;k<size5;k++) {
            getline(fdatosr,garbage);
            aux5[k]=StoQS(garbage);
        }

        fdatosr>>size6;
        QString aux6[size6];
        fdatosr.ignore();
        for(int k=0;k<size6;k++) {
            getline(fdatosr,garbage);
            aux6[k]=StoQS(garbage);
        }

        fdatosr>>size7;
        QString aux7[size7];
        fdatosr.ignore();
        for(int k=0;k<size7;k++) {
            getline(fdatosr,garbage);
            aux7[k]=StoQS(garbage);
        }




        for(int j=0;j<size3;j++){
            QString comentario=nickname+"   "+aux3[j];
            comentarios_ini.push_back(comentario);
        }


        for (int j = 0; j < size3; j++){
            QStringList coments;
            QStringList dataaux=aux7[j].split("\t");
            for(int k=0;k<dataaux.size();k++){
                coments.push_back(dataaux[k]);
            }
            Publicacion* p = new Publicacion(nickname,aux4[j],aux3[j],coments,j,i,cantPublicaciones,aux6[j].toInt());
            agregar_publicacion(p);
            cantPublicaciones++;
        }


    }
    fdatosr.close();
}

void DalePlay::cargar_todo(){
    QFile archivo3("publications.tsv");
    QFile archivo2("users.tsv");
    QFile archivo("comment.tsv");
    ofstream fdatosw;
    fdatosw.open("datos.txt",ios::out);
    int i=0;
    if(archivo3.open(QIODevice::ReadOnly)&&archivo2.open(QIODevice::ReadOnly)){
        QTextStream in3(&archivo3);
        QTextStream in2(&archivo2);
        while(!in3.atEnd()&&!in2.atEnd()){
            QString linea3 = in3.readLine();
            QStringList data3 = linea3.split("\t");

            QString linea2= in2.readLine();
            QStringList data2=linea2.split("\t");
            i++;
        }
        archivo3.close();
        archivo2.close();
    }
    fdatosw<<i<<endl;
    if(archivo3.open(QIODevice::ReadOnly)&&archivo2.open(QIODevice::ReadOnly)&&archivo.open(QIODevice::ReadOnly)){
        QTextStream in3(&archivo3);
        QTextStream in2(&archivo2);
        QTextStream in(&archivo);
        while(!in3.atEnd()&&!in2.atEnd()&&!in.atEnd()){
            QString linea3 = in3.readLine();
            QStringList data3 = linea3.split("\t");

            QString linea2= in2.readLine();
            QStringList data2=linea2.split("\t");

            QString linea = in.readLine();
            QStringList data = linea.split("\t");

            QString comentario = data2[1] +"   "+data[3];
            comentarios_ini.push_back(comentario);
        }
        archivo3.close();
        archivo2.close();
        archivo.close();
    }
    if(archivo.open(QIODevice::ReadOnly)&&archivo2.open(QIODevice::ReadOnly)&&archivo3.open(QIODevice::ReadOnly)){
        QTextStream in(&archivo);
        QTextStream in2(&archivo2);
        QTextStream in3(&archivo3);
        int cont=0;
        while(!in.atEnd() && !in2.atEnd() && !in3.atEnd()){
            cuentaActual=cont;
            QString linea = in.readLine();
            QStringList data = linea.split("\t");

            QString linea2 = in2.readLine();
            QStringList data2 = linea2.split("\t");

            QString linea3 = in3.readLine();
            QStringList data3 = linea3.split("\t");

            QString fecha = data[2]; //COMMENT
            QString interaccion = data3[5]; //PUBLICATIONS
            string saux;



            saux=QStoS(data2[1]);
            fdatosw<<saux<<endl;

            saux=QStoS(data2[2]);
            fdatosw<<saux<<endl;

            fdatosw<<0<<endl<<0<<endl<<0<<endl;

            fdatosw<<1<<endl;
            saux=QStoS(data3[2]);
            fdatosw<<saux<<endl;

            fdatosw<<1<<endl;
            saux=QStoS(data3[4]);
            fdatosw<<saux<<endl;

            fdatosw<<1<<endl;
            saux=QStoS(data[2]);
            fdatosw<<saux<<endl;


            fdatosw<<1<<endl;
            saux=QStoS(data3[5]);
            fdatosw<<saux<<endl;

            int n_comentarios = rand()%5;
            fdatosw<<1<<endl;

            QStringList coments;
            for (int i = 0; i < n_comentarios; i++){
                QString aux=comentarios_ini[rand()%comentarios_ini.size()];
                coments.push_back(aux);
                saux=QStoS(aux);
                fdatosw<<saux;
                if(i!=n_comentarios-1) fdatosw<<"\t";
            }                               //USERS        //COMMENT
            fdatosw<<endl;
            Publicacion* p = new Publicacion(data2[1],fecha,data3[2],coments,0,cont,cantPublicaciones,interaccion.toInt());
            agregar_publicacion(p);
            cantPublicaciones++;
            cont++;
        }
        archivo.close();
        archivo2.close();
        archivo3.close();
    }
    fdatosw.close();
}

void DalePlay::on_BtnSiguientePL_clicked()
{
    ui->MuestraCancionPL->setText(" Reproduciendo: " + (listaR.ImprimeSig()));
    ui->MuestraCancionPL_2->setText(" Reproduciendo:\n " + (listaR.ImprimeAct()));
    if(listaR.NullSig()){
        ui->BtnSiguientePL->setEnabled(false);
        ui->BtnSiguientePL->setStyleSheet("background-image: url(:/Imagenes/btnNext.png); border: 3px solid; border-color: rgb(24, 24, 23);");
    }
    ui->BtnAtrasPL->setEnabled(true);
    ui->BtnAtrasPL->setStyleSheet("background-image: url(:/Imagenes/btnAtrasClicked.png); border: 3px solid; border-color: rgb(24, 24, 23);");
}

void DalePlay::on_BtnAtrasPL_clicked()
{
    ui->MuestraCancionPL->setText(" Reproduciendo: " + (listaR.ImprimeAnt()));
    ui->MuestraCancionPL_2->setText(" Reproduciendo:\n " + (listaR.ImprimeAct()));
    if(listaR.NullAnt()){
        ui->BtnAtrasPL->setEnabled(false);
        ui->BtnAtrasPL->setStyleSheet("background-image: url(:/Imagenes/btnAtras.png); border: 3px solid; border-color: rgb(24, 24, 23);");
    }
    ui->BtnSiguientePL->setEnabled(true);
    ui->BtnSiguientePL->setStyleSheet("background-image: url(:/Imagenes/btnNextClicked.png); border: 3px solid; border-color: rgb(24, 24, 23);");
}



void DalePlay::on_BtnLoginLg_clicked    (){
    int bnickname,bpassword;
    if(cfile.Ingresar(opcionesTotal,ui->NicknameLg->text(),ui->PasswordLg->text(),cuentaActual,bnickname,bpassword)){
        int sizeCan,sizeAm,sizeFav;
        qsCan=cfile.CargarDatos(opcionesTotal,cuentaActual,0,sizeCan);
        for(int i=0;i<sizeCan;i++){
            listaR.AppendNodo(qsCan[i]);
        }
        qsFav=cfile.CargarDatos(opcionesTotal,cuentaActual,2,sizeFav);
        for(int i=0;i<sizeFav;i++){
            ui->MostraListaAr->addItem(qsFav[i]);
        }
        if(sizeCan!=0){
            ui->MuestraPlaylist->setText(listaR.ImprimirLista());
            ui->MuestraCancionPL->setText(" Reproduciendo: " + (listaR.ImprimeAct()));
            ui->MuestraCancionPL_2->setText(" Reproduciendo:\n " + (listaR.ImprimeAct()));
        }
        qsAm=cfile.CargarDatos(opcionesTotal,cuentaActual,1,sizeAm);
        for(int i=0;i<sizeAm;i++) {
            listaAm.add_first(qsAm[i]);
            ui->MuestraAmigos->addItem(qsAm[i]);
        }
        if(sizeCan==0||sizeCan==1){
            ui->BtnAtrasPL->setEnabled(false);
            ui->BtnAtrasPL->setStyleSheet("background-image: url(:/Imagenes/btnAtras.png); border: 3px solid; border-color: rgb(24, 24, 23);");
            ui->BtnSiguientePL->setEnabled(false);
            ui->BtnSiguientePL->setStyleSheet("background-image: url(:/Imagenes/btnNext.png); border: 3px solid; border-color: rgb(24, 24, 23);");
        }
        else{
            ui->BtnAtrasPL->setEnabled(false);
            ui->BtnAtrasPL->setStyleSheet("background-image: url(:/Imagenes/btnAtras.png); border: 3px solid; border-color: rgb(24, 24, 23);");
            ui->BtnSiguientePL->setEnabled(true);
            ui->BtnSiguientePL->setStyleSheet("background-image: url(:/Imagenes/btnNextClicked.png); border: 3px solid; border-color: rgb(24, 24, 23);");
        }
        QString *amigosPosibles;
        int size;
        amigosPosibles=cfile.LeerAmigosPosibles(opcionesTotal,cuentaActual,size);
        for(int i=0;i<size;i++){
            ui->UsuariosAm->addItem(amigosPosibles[i]);
            listaPosiblesAm.add_last(amigosPosibles[i]);
        }
        setFixedSize(ui->FondoInicio -> width(), ui->FondoInicio -> height() + 25);
        ui->stackedWidget->setCurrentIndex(3);
    }
    else{
        // Error
    }
}
void DalePlay::on_btnLogearRg_clicked   (){ setFixedSize(ui->SingUpFond  -> width(), ui->SingUpFond  -> height() + 25); ui->stackedWidget->setCurrentIndex(2); }
void DalePlay::on_BtnRegisterRg_clicked (){
    int bnickname,bpassword;
    if(cfile.CrearCuenta(opcionesTotal,ui->NicknameRg->text(),ui->PasswordRg->text(),bnickname,bpassword,cuentaActual)){
        QString *amigosPosibles;
        int size;
        amigosPosibles=cfile.LeerAmigosPosibles(opcionesTotal,cuentaActual,size);
        for(int i=0;i<size;i++){
            ui->UsuariosAm->addItem(amigosPosibles[i]);
            listaPosiblesAm.add_last(amigosPosibles[i]);
        }
        setFixedSize(ui->FondoInicio -> width(), ui->FondoInicio -> height() + 25);
        ui->stackedWidget->setCurrentIndex(3);
    }
    else{
        // Señalar el tipo de Error
    }
}
void DalePlay::on_btnRegistrarLg_clicked(){ setFixedSize(ui->SingUpFond  -> width(), ui->SingUpFond  -> height() + 25); ui->stackedWidget->setCurrentIndex(7); }

void DalePlay::on_BtnPlaylistIn_clicked (){ ui->stackedWidget->setCurrentIndex(0); }
void DalePlay::on_BtnArtistaIn_clicked  (){ ui->stackedWidget->setCurrentIndex(1); }
void DalePlay::on_BtnInicioIn_clicked   (){ ui->stackedWidget->setCurrentIndex(3); }
void DalePlay::on_BtnCancionIn_clicked  (){ ui->stackedWidget->setCurrentIndex(5); }
void DalePlay::on_BtnAmigoIn_clicked    (){ ui->stackedWidget->setCurrentIndex(6); }

void DalePlay::on_BtnPlaylistCa_clicked (){ ui->stackedWidget->setCurrentIndex(0); }
void DalePlay::on_BtnArtistCa_clicked   (){ ui->stackedWidget->setCurrentIndex(1); }
void DalePlay::on_BtnInicioCa_clicked   (){ ui->stackedWidget->setCurrentIndex(3); }
void DalePlay::on_BtnCancionCa_clicked  (){ ui->stackedWidget->setCurrentIndex(5); }
void DalePlay::on_btnAmigoCa_clicked    (){ ui->stackedWidget->setCurrentIndex(6); }

void DalePlay::on_BtnPlaylistAm_clicked (){ ui->stackedWidget->setCurrentIndex(0); }
void DalePlay::on_BtnArtistaAm_clicked  (){ ui->stackedWidget->setCurrentIndex(1); }
void DalePlay::on_BtnInicioAm_clicked   (){ ui->stackedWidget->setCurrentIndex(3); }
void DalePlay::on_BtnCancionAm_clicked  (){ ui->stackedWidget->setCurrentIndex(5); }
void DalePlay::on_BtnAmigoAm_clicked    (){ ui->stackedWidget->setCurrentIndex(6); }

void DalePlay::on_BtnPlaylistPL_clicked (){ ui->stackedWidget->setCurrentIndex(0); }
void DalePlay::on_BtnArtistaPL_clicked  (){ ui->stackedWidget->setCurrentIndex(1); }
void DalePlay::on_BtnInicioPL_clicked   (){ ui->stackedWidget->setCurrentIndex(3); }
void DalePlay::on_BtnCancionPL_clicked  (){ ui->stackedWidget->setCurrentIndex(5); }
void DalePlay::on_BtnAmigoPL_clicked    (){ ui->stackedWidget->setCurrentIndex(6); }

void DalePlay::on_BtnPlaylistAr_clicked (){ ui->stackedWidget->setCurrentIndex(0); }
void DalePlay::on_BtnArtistaAr_clicked  (){ ui->stackedWidget->setCurrentIndex(1); }
void DalePlay::on_BtnInicioAr_clicked   (){ ui->stackedWidget->setCurrentIndex(3); }
void DalePlay::on_BtnCancionAr_clicked  (){ ui->stackedWidget->setCurrentIndex(5); }
void DalePlay::on_BtnAmigoAr_clicked    (){ ui->stackedWidget->setCurrentIndex(6); }


void DalePlay::on_btnEliminarAm_clicked()
{
    if(ui->MuestraAmigos->count()>0&&ui->MuestraAmigos->currentRow()>=0){
        cfile.EliminarDato(opcionesTotal,ui->MuestraAmigos->currentRow(),cuentaActual,1);
        listaPosiblesAm.add_last(ui->MuestraAmigos->currentItem()->text());
        listaAm.remove_pos(ui->MuestraAmigos->currentRow());
        ui->EscribeAmigoAm->textChanged(ui->EscribeAmigoAm->text());
        ui->MuestraAmigos->takeItem(ui->MuestraAmigos->currentRow());
    }
}

void DalePlay::on_btnAgregarAm_clicked()
{
    if(ui->UsuariosAm->count()>0&&ui->UsuariosAm->currentRow()>=0){
        ui->MuestraAmigos->addItem(ui->UsuariosAm->currentItem()->text());
        for(int i=0;i<listaPosiblesAm.get_leng();i++){
            if(ui->UsuariosAm->currentItem()->text()==listaPosiblesAm.get_pos(i)){
                listaPosiblesAm.remove_pos(i);
                break;
            }
        }
        cfile.GuardarDato(opcionesTotal,ui->UsuariosAm->currentItem()->text(),cuentaActual,1);
        listaAm.add_last(ui->UsuariosAm->currentItem()->text());
        ui->UsuariosAm->takeItem(ui->UsuariosAm->currentRow());
    }
}



void DalePlay::on_btnEliminarAr_clicked()
{
}

void DalePlay::on_btnAgregarAr_clicked()
{
}

void DalePlay::on_btnCanciones_clicked()
{
    QPushButton* button=(QPushButton*) sender();
    QString cancionTXT=button->text();
    ui->MostrarCancionCa->setText("   Reproduciendo: "+ (cancionTXT));
    if(pilaCa.size()==0) pilaCa.push(cancionTXT);
    else{
        if(pilaCa.top()!=cancionTXT) pilaCa.push(cancionTXT);
    }
    if(pilaCa.size()>=2) {
        ui->BtnRegresarCa->setEnabled(true);
        ui->BtnRegresarCa->setStyleSheet("background-image: url(:/Imagenes/btnAtrasClicked.png); border: 3px solid; border-color: rgb(24, 24, 23);");
    }
    ui->BtnSiguienteCa->setEnabled(false);
    ui->BtnSiguienteCa->setStyleSheet("background-image: url(:/Imagenes/btnNext.png); border: 3px solid; border-color: rgb(24, 24, 23);");
    while(pilaAvanzarCa.size()!=0) pilaAvanzarCa.pop();
}




void DalePlay::on_BtnRegresarCa_clicked()
{
        pilaAvanzarCa.push(pilaCa.top());
        ui->BtnSiguienteCa->setEnabled(true);
        ui->BtnSiguienteCa->setStyleSheet("background-image: url(:/Imagenes/btnNextClicked.png); border: 3px solid; border-color: rgb(24, 24, 23);");
        pilaCa.pop();
        QString cancionTXT=pilaCa.top();
        ui->MostrarCancionCa->setText("   Reproduciendo: "+ (cancionTXT));
        if(pilaCa.size()<=1) {
            ui->BtnRegresarCa->setEnabled(false);
            ui->BtnRegresarCa->setStyleSheet("background-image: url(:/Imagenes/btnAtras.png); border: 3px solid; border-color: rgb(24, 24, 23);");
        }

}

void DalePlay::on_btnGuardarCa_clicked()
{
    if(pilaCa.size()!=0){
        if(cfile.GuardarDato(opcionesTotal,pilaCa.top(),cuentaActual,0)){
            listaR.AppendNodo(pilaCa.top());
            ui->MuestraCancionPL->setText("Reproduciendo:\n" + (listaR.ImprimeAct()));
            ui->MuestraCancionPL_2->setText(" Reproduciendo:\n " + (listaR.ImprimeAct()));
            if(listaR.GetLeng()>=2){
                ui->BtnSiguientePL->setEnabled(true);
                ui->BtnSiguientePL->setStyleSheet("background-image: url(:/Imagenes/btnNextClicked.png);");
            }
            ui->MuestraPlaylist->setText(listaR.ImprimirLista());
        }
    }
}

void DalePlay::on_BtnEliminarPL_clicked()
{
}

void DalePlay::on_BtnSiguienteCa_clicked()
{
    QString cancionTXT=pilaAvanzarCa.top();
    pilaCa.push(pilaAvanzarCa.top());
    if(pilaCa.size()>=2) {
        ui->BtnRegresarCa->setEnabled(true);
        ui->BtnRegresarCa->setStyleSheet("background-image: url(:/Imagenes/btnAtrasClicked.png); border: 3px solid; border-color: rgb(24, 24, 23);");
    }
    pilaAvanzarCa.pop();
    ui->MostrarCancionCa->setText("   Reproduciendo: "+ (cancionTXT));
    if(pilaAvanzarCa.size()==0) {
        ui->BtnSiguienteCa->setEnabled(false);
        ui->BtnSiguienteCa->setStyleSheet("background-image: url(:/Imagenes/btnNext.png); border: 3px solid; border-color: rgb(24, 24, 23);");
    }
}





void DalePlay::on_EscribeAmigoAm_textChanged(const QString &arg1)
{
    ui->UsuariosAm->clear();
    for(int i=0;i<listaPosiblesAm.get_leng();i++){
        for(int j=0;j<listaPosiblesAm.get_pos(i).size()-arg1.size();j++){
            bool encontrado = true;
            for(int k = 0;k< arg1.size();k++){
                if(listaPosiblesAm.get_pos(i)[k+j] != arg1[k]){
                   encontrado = false;
                   break;
                }
            }
            if(encontrado == true ) {
                ui->UsuariosAm->addItem(listaPosiblesAm.get_pos(i));
                break;
            }
        }
    }
}

void DalePlay::on_AgregaCancionAr_clicked(){ ui->stackedWidget->setCurrentIndex(6); }

void DalePlay::on_btnFavoritosCa_clicked()
{
    if(pilaCa.size()!=0){
        if(cfile.GuardarDato(opcionesTotal,pilaCa.top(),cuentaActual,2)){
            ui->MostraListaAr->addItem(pilaCa.top());
        }
    }
}

void DalePlay::on_EliminCancionAr_clicked()
{
    if(ui->MostraListaAr->currentRow()>=-1){
        cfile.EliminarDato(opcionesTotal,ui->MostraListaAr->currentRow(),cuentaActual,2);
        ui->MostraListaAr->takeItem(ui->MostraListaAr->currentRow());
    }
}
void DalePlay::on_BtnEntrarPubliIn_clicked()
{

    if(ui->ListaPubIn->currentRow()!=-1){
        QString publi = ui->ListaPubIn->currentItem()->text();
        QStringList data = publi.split(" | ");
        int dataaux=data[4].toInt();
        actualPublicacion = this->arbolPosicion->getNode(dataaux)->data;
        Publicacion* p = actualPublicacion;

        ui->UsuarioIn->setText(p->GetNombre());
        ui->CorreoIn->setText(p->GetFecha());
        ui->PubliIn->clear();
        ui->PubliIn->addItem(p->GetContenido());
        ui->LikeIn->setText(QString::number(p->Getinteraccion()));

        ui->ListaComIn->clear();
        for(int i = 0; i < p->GetComentarios().size() ; i++){
          ui->ListaComIn->addItem(p->GetComentarios()[i]);
        }
    }


}
void DalePlay::aumentar_interaccion(Publicacion p){
    //
}
void DalePlay::on_BtnLikeIn_clicked()
{
    if(actualPublicacion != nullptr){
        actualPublicacion->aumentarInteraccion();
        cfile.AumentarInteraciones(opcionesTotal,actualPublicacion->GetPosopcion(),actualPublicacion->GetPosCuenta(),6);
        ui->LikeIn->setText(QString::number(actualPublicacion->Getinteraccion()));

        ui->ListaPubIn->clear();

        this->arbolFecha->postorder_50(ui->ListaPubIn);
    }
}

void DalePlay::on_BtnhareIn_clicked()
{
    on_BtnLikeIn_clicked();
    QString nombre = cfile.LeerNickname(opcionesTotal,cuentaActual);
    QString fecha = actualPublicacion->GetFecha();
    QString publicacion = actualPublicacion->GetContenido();
    int interaccion =0;
    int opcionactual=cfile.CantOpcion(opcionesTotal,cuentaActual,3);
    agregar_publicacion(new Publicacion (nombre, fecha, publicacion, {},opcionactual,cuentaActual,cantPublicaciones, interaccion));
    cantPublicaciones++;
    cfile.GuardarDatoSiempre(opcionesTotal,fecha,cuentaActual,4);
    cfile.GuardarDatoSiempre(opcionesTotal,publicacion,cuentaActual,3);
    cfile.AgregarInteraccionPublicacionComentario(opcionesTotal,cuentaActual,6);
    cfile.AgregarIteracionPublicacionComentario(opcionesTotal,cuentaActual,7);
    ui->ListaPubIn->clear();
    arbolInteraccion->postorder_50(ui->ListaPubIn);
}

void DalePlay::on_BtnRecienteIn_clicked()
{
     ui->ListaPubIn->clear();
     arbolFecha->postorder_50(ui->ListaPubIn);
}

void DalePlay::on_BtnNomAZIn_clicked()
{
    ui->ListaPubIn->clear();
    arbolNombre->inorder_50(ui->ListaPubIn);
}

void DalePlay::on_BtnNomZAIn_clicked()
{
    ui->ListaPubIn->clear();
    arbolNombre->postorder_50(ui->ListaPubIn);
}

void DalePlay::on_BtnInteracIn_clicked()
{
    ui->ListaPubIn->clear();
    arbolInteraccion->postorder_50(ui->ListaPubIn);
}

void DalePlay::on_BtnAgregarPubIn_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);
    setFixedSize(ui->FondoComentario->width(), ui->FondoComentario->height());
}

void DalePlay::on_BtnCancelarCO_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    setFixedSize(ui->FondoInicio->width(), ui->FondoInicio->height());
}

void DalePlay::on_BtnCommIn_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
    setFixedSize(ui->FondoComentario->width(), ui->FondoComentario->height());
}

void DalePlay::on_CancelarPU_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    setFixedSize(ui->FondoInicio->width(), ui->FondoInicio->height());
}

void DalePlay::on_BtnPlaylistUs_clicked () { ui->stackedWidget->setCurrentIndex(0); }

void DalePlay::on_BtnArtistaUs_clicked  () { ui->stackedWidget->setCurrentIndex(1); }

void DalePlay::on_pushButton_2_clicked  () { ui->stackedWidget->setCurrentIndex(3); }

void DalePlay::on_btnVolverUs_clicked   () { ui->stackedWidget->setCurrentIndex(3); }

void DalePlay::on_BtnInicioUs_clicked   () { ui->stackedWidget->setCurrentIndex(3); }

void DalePlay::on_BtnUsuarioIn_clicked  () {
    if(ui->UsuarioIn->text()!=""){

    usuario_actual = actualPublicacion->GetNombre();
    arbolNombre->findAll_query(usuario_actual,ui->ListaPubIn,[](Publicacion* p){return p->GetNombre();});
    ui->pushButton->setVisible(true);
}
}

void DalePlay::on_pushButton_clicked    () {

    ui->ListaPubIn->clear();
    arbolFecha->postorder_50(ui->ListaPubIn);
    ui->pushButton->setVisible(false);
}

void DalePlay::on_BtnCancionUs_clicked  () { ui->stackedWidget->setCurrentIndex(5); }

void DalePlay::on_BtnAmigoUs_clicked    () { ui->stackedWidget->setCurrentIndex(6); }

void DalePlay::agregar_publicacion(Publicacion* p){
   this->arbolNombre->add(p);
   this->arbolFecha->add(p);
   this->arbolContenido->add(p);
   this->arbolInteraccion->add(p);
   this->arbolPosicion->add(p);
}

void DalePlay::on_AceptarPU_clicked()
{
    if(ui->FechaPU->text() != "" && ui->PublicacionPU->text() != ""){
        QString nombre = cfile.LeerNickname(opcionesTotal,cuentaActual);
        QString fecha = ui->FechaPU->text();
        QString publicacion = ui->PublicacionPU->text();
        int interaccion =0;
        QString qsinteraccion="0";
        int opcionactual=cfile.CantOpcion(opcionesTotal,cuentaActual,3);
        agregar_publicacion(new Publicacion (nombre, fecha, publicacion, {},opcionactual,cuentaActual,cantPublicaciones, interaccion));
        cantPublicaciones++;
        cfile.GuardarDatoSiempre(opcionesTotal,fecha,cuentaActual,4);
        cfile.GuardarDatoSiempre(opcionesTotal,publicacion,cuentaActual,3);
        cfile.AgregarInteraccionPublicacionComentario(opcionesTotal,cuentaActual,6);
        cfile.AgregarIteracionPublicacionComentario(opcionesTotal,cuentaActual,7);
        ui->ListaPubIn->clear();
        arbolInteraccion->postorder_50(ui->ListaPubIn);
    }
    ui->stackedWidget->setCurrentIndex(3);
    setFixedSize(ui->FondoInicio->width(), ui->FondoInicio->height());
}

void DalePlay::on_BtnAceptarCO_clicked()
{
    if( ui->PublicacionCO->text() != "" && actualPublicacion != nullptr){
        QString nombre =  cfile.LeerNickname(opcionesTotal,cuentaActual);
        QString Publicacion =  ui->PublicacionCO->text();
        QString comentario = nombre + "   " + Publicacion;
        cfile.GuardarComentario(opcionesTotal,comentario,actualPublicacion->GetPosCuenta(),7);
        actualPublicacion->add_comentario(comentario);        //agregar_publicacion(new Publicacion ("nombre", "fecha", "genero", comentarios, 0));
        ui->ListaComIn->addItem(comentario);
    }
    ui->stackedWidget->setCurrentIndex(3);
    setFixedSize(ui->FondoInicio->width(), ui->FondoInicio->height());
}

void DalePlay::BuscarPubli(QString titulo){
   /* //juego_selected = BST_nombre->find_node(titulo);
    actualPublicacion = arbolContenido->find_query(titulo,ui->ListaPubIn);
    if(actualPublicacion != nullptr){
        Publicacion publicacion = actualPublicacion->data;
    }*/
}
void DalePlay::on_EmpiezaIn_returnPressed()
{
    //BuscarPubli(ui->EmpiezaIn->text());
}

void DalePlay::on_EmpiezaIn_textEdited(const QString &arg1)
{
   if(actualPublicacion != nullptr){
       ui->ListaComIn->clear();
       QStringList comments = actualPublicacion->GetComentarios();
       for(int i = 0; i < comments.size(); i++){
          if(comments[i].contains(arg1,Qt::CaseInsensitive)){
              ui->ListaComIn->addItem(comments[i]);
          }
       }
   }
}

void DalePlay::on_BuscarPuIn_textEdited(const QString &arg1)
{
    arbolContenido->findAll_query(arg1,ui->ListaPubIn,[](Publicacion* p){return p->GetContenido();});
}
//arbolContenido->findAll_query(actualusuario,ui->ListaPubIn,[](Publicacion* p){return p->GetNombre();});
void DalePlay::on_BuscarNoIn_textEdited(const QString &arg1)
{

    arbolNombre->findAll_query(arg1,ui->ListaPubIn,[](Publicacion* p){return p->GetNombre();});
}
