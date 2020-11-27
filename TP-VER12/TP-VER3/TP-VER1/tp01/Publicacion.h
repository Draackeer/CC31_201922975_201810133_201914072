#ifndef PUBLICACION_H
#define PUBLICACION_H

#include <QTextStream>
class Publicacion{
    QString nombre;
    QString fecha;
    QString contenido;
    QStringList comentarios = {"Titulo asdasqwd \nDescripcion: dasñkldaskla", "qweqwqw","efefasda"};
    //"YYYY/MM/DD"
    int interaccion;
    int posopcion;
    int poscuenta;
    int posicion;
public:
    Publicacion(QString nombre,QString fecha,QString contenido,QStringList comentarios, int posopcion,int poscuenta,int posicion,int interaccion):
        nombre(nombre),
        fecha(fecha),
        contenido(contenido),
        comentarios(comentarios),
        posopcion(posopcion),
        poscuenta(poscuenta),
        posicion(posicion){
        this->interaccion = interaccion;
        this->interaccion+=comentarios.size();
    }
    QString GetNombre(){
        return this->nombre;
    }
    int GetPosicion(){return posicion;}
    QString GetFecha(){
        return this->fecha;
    }
    QString GetContenido(){
        return this->contenido;
    }
    QStringList GetComentarios(){
        return this->comentarios;
    }
    void add_comentario(QString coment){
        this->comentarios.append(coment);
    }
    int Getinteraccion(){
        return this->interaccion;
    }
    int GetPosopcion(){return this->posopcion;}
    int GetPosCuenta(){return this->poscuenta;}
    void aumentarInteraccion(){
        this->interaccion++;
    }
    QString fill_space(QString fill, int n = 15){
       /* int sep = n-fill.size();
        if(sep % 2 != 0)
            return QString((sep/2),' ') + fill + QString((sep/2)+1,' ');
        return QString((sep/2),' ') + fill + QString((sep/2),' ');*/
        return fill+QString(n-fill.size(),' ');
    }

    QString toString(){
       return fill_space(QString::number(this->interaccion),3)+" | "+ fill_space(this->nombre,18)+" | "+fill_space(this->fecha,10)+" | "+this->contenido
               +" | "+fill_space(QString::number(this->posicion),6);
    }
};


#endif // PUBLICACIÓN_H
