#ifndef DALEPLAY_H
#define DALEPLAY_H
#include "ListaReproduccion.h"
#include "Amigos_Artista.h"
#include "Files.h"
#include <stack>
#include <QMainWindow>
#include <Tree.h>
#include <Publicacion.h>

QT_BEGIN_NAMESPACE
namespace Ui { class DalePlay; }
QT_END_NAMESPACE

class DalePlay : public QMainWindow
{
    Q_OBJECT
     int opcionesTotal=8; // Al agregar una nueva opcion ACTUALIZAR
     // 0 = lista de reproduccion
     // 1 = amigos
     // 2 = favoritos
     // 3 = publicacion
     // 4 = fecha de publicacion
     // 5 = fecha de comentario (vacío)
     // 6 = interacciones de publicacion
     // 7 = comentarios de publicaciones
     ListaReproduccion<QString> listaR;
     Amigos_Favoritos<QString> listaPosiblesAm;
     Amigos_Favoritos<QString> listaAm;
     Amigos_Favoritos<QString> listaFa;

     BST<Publicacion*, QString>* arbolNombre;
     BST<Publicacion*, QString>* arbolFecha;
     BST<Publicacion*, QString>* arbolContenido;
     BST<Publicacion*, int>* arbolInteraccion;
     BST<Publicacion*, int>* arbolPosicion;
     int cantPublicaciones=0;

     stack<QString> pilaCa;
     stack<QString> pilaAvanzarCa;
     int cuentaActual;
     QString *qsCan,*qsAm,*qsFav;
     bool YaPulso = false;
     CFiles cfile=CFiles();

public:
    DalePlay(QWidget *parent = nullptr);
    ~DalePlay();

private slots:
    //void cargar_comentarios();
    void aumentar_interaccion(Publicacion p);
    //void cargar_publicaciones();
    void agregar_publicacion(Publicacion* p);

    //void guardar_todo();
    void cargar_todo();

    void BuscarPubli(QString titulo);

    void on_BtnSiguientePL_clicked();

    void on_BtnAtrasPL_clicked();

    void on_BtnInicioIn_clicked();

    void on_BtnCancionIn_clicked();

    void on_BtnAmigoIn_clicked();

    void on_BtnPlaylistIn_clicked();

    void on_BtnArtistaIn_clicked();

    void on_BtnInicioCa_clicked();

    void on_BtnCancionCa_clicked();

    void on_btnAmigoCa_clicked();

    void on_BtnPlaylistCa_clicked();

    void on_BtnArtistCa_clicked();

    void on_BtnInicioAm_clicked();

    void on_BtnCancionAm_clicked();

    void on_BtnAmigoAm_clicked();

    void on_BtnPlaylistAm_clicked();

    void on_BtnArtistaAm_clicked();

    void on_BtnInicioPL_clicked();

    void on_BtnCancionPL_clicked();

    void on_BtnAmigoPL_clicked();

    void on_BtnPlaylistPL_clicked();

    void on_BtnArtistaPL_clicked();

    void on_BtnInicioAr_clicked();

    void on_BtnCancionAr_clicked();

    void on_BtnAmigoAr_clicked();

    void on_BtnPlaylistAr_clicked();

    void on_BtnArtistaAr_clicked();

    void on_btnEliminarAm_clicked();

    void on_btnAgregarAm_clicked();

    void on_btnEliminarAr_clicked();

    void on_btnAgregarAr_clicked();

    void on_btnCanciones_clicked();

    void on_BtnRegresarCa_clicked();

    void on_btnGuardarCa_clicked();

    void on_BtnEliminarPL_clicked();

    void on_BtnSiguienteCa_clicked();

    void on_BtnLoginLg_clicked();

    void on_btnLogearRg_clicked();

    void on_BtnRegisterRg_clicked();

    void on_btnRegistrarLg_clicked();

    void on_EscribeAmigoAm_textChanged(const QString &arg1);

    void on_AgregaCancionAr_clicked();

    void on_btnFavoritosCa_clicked();

    void on_EliminCancionAr_clicked();

    void on_BtnEntrarPubliIn_clicked();

    void on_BtnLikeIn_clicked();

    void on_BtnhareIn_clicked();

    void on_BtnRecienteIn_clicked();

    void on_BtnNomAZIn_clicked();

    void on_BtnNomZAIn_clicked();

    void on_BtnInteracIn_clicked();

    void on_BtnAgregarPubIn_clicked();

    void on_pushButton_2_clicked();

    void on_BtnCancelarCO_clicked();

    void on_BtnCommIn_clicked();

    void on_CancelarPU_clicked();

    void on_pushButton_clicked();

    void on_BtnUsuarioIn_clicked();

    void on_btnVolverUs_clicked();

    void on_BtnInicioUs_clicked();

    void on_BtnCancionUs_clicked();

    void on_BtnAmigoUs_clicked();

    void on_BtnPlaylistUs_clicked();

    void on_BtnArtistaUs_clicked();

    void on_AceptarPU_clicked();

    string QStoS(QString);

    QString StoQS(string);

    void cargar_todoTxt();

    void on_BtnAceptarCO_clicked();

    void on_EmpiezaIn_returnPressed();

    void on_EmpiezaIn_textEdited(const QString &arg1);

    //void on_BtnCommUs_clicked();

    void on_BuscarPuIn_textEdited(const QString &arg1);

    void on_BuscarNoIn_textEdited(const QString &arg1);

private:
    Ui::DalePlay *ui;
};
#endif // DALEPLAY_H


