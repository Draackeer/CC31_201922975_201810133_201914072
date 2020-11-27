#ifndef FILES_H
#define FILES_H
#include <QMainWindow>
#include <fstream>
using namespace std;
class CFiles{
public:
    CFiles(){}
    bool IsNull(){
        ifstream fdatosr;
        fdatosr.open("datos.txt",ios::in);
        fdatosr.seekg(0,fdatosr.end);
        int size=fdatosr.tellg();
        fdatosr.close();
        if(size==0) return true;
        else return false;
    }

    bool Ingresar(int opcionesTotal,QString snickname, QString spassword,int &cuenta, int &bnickname, int &bpassword){
        bnickname=bpassword=0;
        if(snickname.size()==0) bnickname=1;
        if(spassword.size()==0) bnickname=1;
        if(bnickname!=0||bpassword!=0) return false;
        ifstream fdatosr;
        fdatosr.open("datos.txt",ios::in);
        fdatosr.seekg(0,fdatosr.end);
        int size=fdatosr.tellg();
        fdatosr.seekg(0,fdatosr.beg);
        if(size==0) return false;
        else{
            int n;
            fdatosr>>n;
            fdatosr.ignore();
            string garbage;
            string nicknameaux;
            string passwordaux;
            int auxlenstring;
            for(int i=0;i<n;i++){
                fdatosr>>nicknameaux>>passwordaux;
                if((int)snickname.size()!=(int)nicknameaux.size());
                else{
                    bool cont=true;
                    for(int j=0;j<(int)snickname.size();j++){
                        if(snickname[j]!=nicknameaux[j]){
                            cont=false;
                            break;
                        }
                    }
                    if(cont==true){
                        fdatosr.close();
                        if((int)spassword.size()!=(int)passwordaux.size()) return false;
                        else{
                            for(int j=0;j<(int)spassword.size();j++){
                                if(spassword[j]!=passwordaux[j]){
                                    return false;
                                }
                            }
                            cuenta=i;
                            return true;
                        }
                    }
                }
                for(int j=0;j<opcionesTotal;j++){
                    fdatosr>>auxlenstring;
                    fdatosr.ignore();
                    for(int k=0;k<auxlenstring;k++) getline(fdatosr,garbage);
                }
            }
        }
        fdatosr.close();
        return false;
    }

    bool CrearCuenta(int opcionesTotal,QString snickname,QString spassword,int &bnickname,int &bpassword,int &cuenta){
        ifstream fdatosr;
        fdatosr.open("datos.txt",ios::in);
        fdatosr.seekg(0,fdatosr.end);
        int size=fdatosr.tellg();
        fdatosr.seekg(0,fdatosr.beg);
        int cuentasTotal;
        if(size==0){
            cuentasTotal=0;
        }
        else{
            fdatosr>>cuentasTotal;
            fdatosr.ignore();
        }
        int lenstringant=0;
        int auxlenstring;
        string garbage;
        bool encontrado=false;
        string cuentaaux;
        if(cuentasTotal!=0){
            lenstringant++;
            for(int i=0;i<cuentasTotal;i++){
                fdatosr>>cuentaaux>>garbage;
                if((int)snickname.size()!=(int)cuentaaux.size());
                else{
                    bool cont=true;
                    for(int j=0;j<(int)snickname.size();j++){
                        if(snickname[j]!=cuentaaux[j]){
                            cont=false;
                            break;
                        }
                    }
                    if(cont==true){
                        encontrado=true;
                        break;
                    }
                }
                lenstringant+=2;
                for(int j=0;j<opcionesTotal;j++){
                    fdatosr>>auxlenstring;
                    lenstringant++;
                    fdatosr.ignore();
                    lenstringant+=auxlenstring;
                    for(int k=0;k<auxlenstring;k++) getline(fdatosr,garbage);
                }
            }
        }
        bpassword=bnickname=0;
        bool nospacepassword=false;
        bool nospacenickname=false;
        for(int i=0;i<spassword.size();i++){
            if(spassword[i]==' '){
                nospacepassword=true;
                break;
            }
        }
        for(int i=0;i<snickname.size();i++) {
            if(snickname[i]==' '){
                nospacenickname=true;
                break;
            }
        }
        if(spassword.size()==0) bpassword=1;
        else if(spassword.size()<2) bpassword=2;
        else if(nospacepassword) bpassword=3;
        if(snickname.size()==0) bnickname=1;
        else if(snickname.size()<2) bnickname=2;
        else if(nospacenickname) bnickname=3;
        else if(encontrado) bnickname=4;
        if(bnickname!=0||bpassword!=0) return false;
        if(!encontrado){
            fdatosr.seekg(0,fdatosr.beg);
            string sant[lenstringant];
            for(int i=0;i<lenstringant;i++) getline(fdatosr,sant[i]);
            fdatosr.close();
            ofstream fdatosw;
            fdatosw.open("datos.txt",ios::out);
            fdatosw<<cuentasTotal+1<<endl;
            cuenta=cuentasTotal;
            for(int i=1;i<lenstringant;i++) fdatosw<<sant[i]<<endl;
            for(int i=0;i<snickname.size();i++) fdatosw<<snickname[i].toLatin1();
            fdatosw<<endl;
            for(int i=0;i<spassword.size();i++) fdatosw<<spassword[i].toLatin1();
            fdatosw<<endl;
            for(int i=0;i<opcionesTotal;i++) fdatosw<<"0"<<endl;
            fdatosw.close();
        }
        return true;
    }

    void CantAntPos(int opcionesTotal,int cuentaActual,int &lenstringant,int &lenstringpos){
        ifstream fdatosr;
        fdatosr.open("datos.txt",ios::in);
        int cuentasTotal;
        fdatosr>>cuentasTotal;
        lenstringant=lenstringpos=0;
        string garbage;
        int auxlenstring;
        lenstringant++;
        for(int i=0;i<cuentaActual;i++){
            fdatosr>>garbage;
            fdatosr>>garbage;
            lenstringant+=2;
            for(int j=0;j<opcionesTotal;j++){
                fdatosr>>auxlenstring;
                lenstringant++;
                fdatosr.ignore();
                lenstringant+=auxlenstring;
                for(int k=0;k<auxlenstring;k++) getline(fdatosr,garbage);

            }
        }
        fdatosr>>garbage;
        fdatosr>>garbage;
        for(int i=0;i<opcionesTotal;i++){
            fdatosr>>auxlenstring;
            fdatosr.ignore();
            for(int j=0;j<auxlenstring;j++) getline(fdatosr,garbage);
        }
        for(int i=cuentaActual+1;i<cuentasTotal;i++){
            fdatosr>>garbage;
            fdatosr>>garbage;
            lenstringpos+=2;
            for(int j=0;j<opcionesTotal;j++){
                fdatosr>>auxlenstring;
                lenstringpos++;
                fdatosr.ignore();
                lenstringpos+=auxlenstring;
                for(int k=0;k<auxlenstring;k++) getline(fdatosr,garbage);
            }
        }
    }

    int CantOpcion(int opcionesTotal,int cuentaActual,int opcion){
        ifstream fdatosr;
        fdatosr.open("datos.txt",ios::in);
        int cuentasTotal;
        fdatosr>>cuentasTotal;
        string garbage;
        int auxlenstring;
        for(int i=0;i<cuentaActual;i++){
            fdatosr>>garbage;
            fdatosr>>garbage;
            for(int j=0;j<opcionesTotal;j++){
                fdatosr>>auxlenstring;
                fdatosr.ignore();
                for(int k=0;k<auxlenstring;k++) getline(fdatosr,garbage);

            }
        }
        fdatosr>>garbage;
        fdatosr>>garbage;
        for(int i=0;i<opcion;i++){
            fdatosr>>auxlenstring;
            fdatosr.ignore();
            for(int j=0;j<auxlenstring;j++) getline(fdatosr,garbage);
        }

        fdatosr>>auxlenstring;
        fdatosr.close();
        return auxlenstring;

    }

    void CantAntPosOpcion(int opcionesTotal,int cuentaActual,int &lenstringant,int &lenstringpos,int opcion){
        ifstream fdatosr;
        fdatosr.open("datos.txt",ios::in);
        int cuentasTotal;
        fdatosr>>cuentasTotal;
        lenstringant=lenstringpos=0;
        string garbage;
        int auxlenstring;
        lenstringant++;
        for(int i=0;i<cuentaActual;i++){
            fdatosr>>garbage;
            fdatosr>>garbage;
            lenstringant+=2;
            for(int j=0;j<opcionesTotal;j++){
                fdatosr>>auxlenstring;
                lenstringant++;
                fdatosr.ignore();
                lenstringant+=auxlenstring;
                for(int k=0;k<auxlenstring;k++) getline(fdatosr,garbage);

            }
        }
        fdatosr>>garbage;
        fdatosr>>garbage;
        lenstringant+=2;
        for(int i=0;i<opcion;i++){
            fdatosr>>auxlenstring;
            lenstringant++;
            fdatosr.ignore();
            lenstringant+=auxlenstring;
            for(int j=0;j<auxlenstring;j++) getline(fdatosr,garbage);
        }

        fdatosr>>auxlenstring;
        fdatosr.ignore();
        for(int i=0;i<auxlenstring;i++) getline(fdatosr,garbage);

        for(int i=opcion+1;i<opcionesTotal;i++){
            fdatosr>>auxlenstring;
            lenstringpos++;
            fdatosr.ignore();
            lenstringpos+=auxlenstring;
            for(int j=0;j<auxlenstring;j++) getline(fdatosr,garbage);
        }
        for(int i=cuentaActual+1;i<cuentasTotal;i++){
            fdatosr>>garbage;
            fdatosr>>garbage;
            lenstringpos+=2;
            for(int j=0;j<opcionesTotal;j++){
                fdatosr>>auxlenstring;
                lenstringpos++;
                fdatosr.ignore();
                lenstringpos+=auxlenstring;
                for(int k=0;k<auxlenstring;k++) getline(fdatosr,garbage);
            }
        }
    }

    void CantAntPosEliminar(int opcionesTotal,int cuentaActual,int &lenstringant,int &lenstringpos,int opcion){
        ifstream fdatosr;
        fdatosr.open("datos.txt",ios::in);
        int cuentasTotal;
        fdatosr>>cuentasTotal;
        lenstringant=lenstringpos=0;
        string garbage;
        int auxlenstring;
        lenstringant++;
        for(int i=0;i<cuentaActual;i++){
            fdatosr>>garbage;
            fdatosr>>garbage;
            lenstringant+=2;
            for(int j=0;j<opcionesTotal;j++){
                fdatosr>>auxlenstring;
                lenstringant++;
                fdatosr.ignore();
                lenstringant+=auxlenstring;
                for(int k=0;k<auxlenstring;k++) getline(fdatosr,garbage);

            }
        }
        fdatosr>>garbage;
        fdatosr>>garbage;
        lenstringant+=2;
        for(int i=0;i<opcion;i++){
            fdatosr>>auxlenstring;
            lenstringant++;
            fdatosr.ignore();
            lenstringant+=auxlenstring;
            for(int j=0;j<auxlenstring;j++) getline(fdatosr,garbage);
        }
        fdatosr>>auxlenstring;
        fdatosr.ignore();
        for(int j=0;j<auxlenstring;j++) getline(fdatosr,garbage);
        for(int i=opcion+1;i<opcionesTotal;i++){
            fdatosr>>auxlenstring;
            lenstringpos++;
            fdatosr.ignore();
            lenstringpos+=auxlenstring;
            for(int j=0;j<auxlenstring;j++) getline(fdatosr,garbage);
        }
        for(int i=cuentaActual+1;i<cuentasTotal;i++){
            fdatosr>>garbage;
            fdatosr>>garbage;
            lenstringpos+=2;
            for(int j=0;j<opcionesTotal;j++){
                fdatosr>>auxlenstring;
                lenstringpos++;
                fdatosr.ignore();
                lenstringpos+=auxlenstring;
                for(int k=0;k<auxlenstring;k++) getline(fdatosr,garbage);
            }
        }
    }

    void EliminarDato(int opcionesTotal,int posicion,int cuentaActual,int opcion){
        int lenstringant,lenstringpos;
        CantAntPosEliminar(opcionesTotal,cuentaActual,lenstringant,lenstringpos,opcion);
        string sant[lenstringant];
        string spos[lenstringpos];
        ifstream fdatosr;
        fdatosr.open("datos.txt",ios::in);
        string garbage;
        for(int i=0;i<lenstringant;i++) getline(fdatosr,sant[i]);

        int lendatos;
        fdatosr>>lendatos;
        fdatosr.ignore();
        lendatos--;
        string datos[lendatos];
        for(int i=0;i<posicion;i++) getline(fdatosr,datos[i]);
        getline(fdatosr,garbage);
        for(int i=posicion;i<lendatos;i++) getline(fdatosr,datos[i]);

        for(int i=0;i<lenstringpos;i++) getline(fdatosr,spos[i]);
        fdatosr.close();
        ofstream fdatosw;
        fdatosw.open("datos.txt",ios::out);
        for(int i=0;i<lenstringant;i++) fdatosw<<sant[i]<<endl;
        fdatosw<<lendatos<<endl;
        for(int i=0;i<lendatos;i++) fdatosw<<datos[i]<<endl;
        for(int i=0;i<lenstringpos;i++) fdatosw<<spos[i]<<endl;
        fdatosw.close();
    }

    void EliminarCuenta(int opcionesTotal,int cuentaActual){
        int lenstringant,lenstringpos;
        CantAntPos(opcionesTotal,cuentaActual,lenstringant,lenstringpos);
        string sant[lenstringant];
        string spos[lenstringpos];
        ifstream fdatosr;
        fdatosr.open("datos.txt",ios::in);
        int cuentasTotal;
        fdatosr>>cuentasTotal;
        fdatosr.ignore();
        if(cuentasTotal==1){
            ofstream fdatosw;
            fdatosw.open("datos.txt",ios::out);
            fdatosw.close();
        }
        for(int i=0;i<lenstringant-1;i++) getline(fdatosr,sant[i]);
        string garbage;
        fdatosr>>garbage;
        fdatosr>>garbage;
        int lenstringaux;
        for(int i=0;i<opcionesTotal;i++){
            fdatosr>>lenstringaux;
            fdatosr.ignore();
            for(int j=0;j<lenstringaux;j++) getline(fdatosr,garbage);
        }
        for(int i=0;i<lenstringpos;i++) getline(fdatosr,spos[i]);
        fdatosr.close();
        ofstream fdatosw;
        fdatosw.open("datos.txt",ios::out);
        cuentasTotal--;
        fdatosw<<cuentasTotal<<endl;
        for(int i=0;i<lenstringant-1;i++) fdatosw<<sant[i]<<endl;
        for(int i=0;i<lenstringpos;i++) fdatosw<<spos[i]<<endl;
        fdatosw.close();
    }

    QString* CargarDatos(int opcionesTotal,int cuentaActual,int opcion,int &size){
        int lenstringant,lenstringpos;
        CantAntPos(opcionesTotal,cuentaActual,lenstringant,lenstringpos);
        string sant[lenstringant];
        string spos[lenstringpos];
        ifstream fdatosr;
        fdatosr.open("datos.txt",ios::in);
        string garbage;
        for(int i=0;i<lenstringant;i++) getline(fdatosr,garbage);
        fdatosr>>garbage>>garbage;
        int n;
        for(int i=0;i<opcion;i++){
            fdatosr>>n;
            fdatosr.ignore();
            for(int i=0;i<n;i++) getline(fdatosr,garbage);
        }
        fdatosr>>size;
        fdatosr.ignore();
        QString *qs=new QString[size];
        string s[size];
        for(int i=0;i<size;i++){
            getline(fdatosr,s[i]);
            int sn=(int)s[i].size();
            qs[i].resize(sn);
            for(int j=0;j<sn;j++){
                qs[i][j]=s[i][j];
            }
        }
        fdatosr.close();
        return qs;
    }

    QString LeerNickname(int opcionesTotal,int cuentaActual){
        int lenstringant,lenstringpos;
        CantAntPos(opcionesTotal,cuentaActual,lenstringant,lenstringpos);
        string sant[lenstringant];
        string spos[lenstringpos];
        ifstream fdatosr;
        fdatosr.open("datos.txt",ios::in);
        string garbage;
        for(int i=0;i<lenstringant;i++) getline(fdatosr,garbage);
        QString qs;
        string s;
        getline(fdatosr,s);
        int sn=(int)s.size();
        qs.resize(sn);
        for(int j=0;j<sn;j++){
            qs[j]=s[j];
        }
        fdatosr.close();
        return qs;
    }

    int totalCuentas(){
        ifstream fdatosr;
        fdatosr.open("datos.txt",ios::in);
        fdatosr.seekg(0,fdatosr.end);
        int size=fdatosr.tellg();
        fdatosr.seekg(0,fdatosr.beg);
        int cuentasTotal;
        if(size==0){
            cuentasTotal=0;
        }
        else{
            fdatosr>>cuentasTotal;
            fdatosr.ignore();
        }
        return cuentasTotal;
    }

    QString* LeerAmigosPosibles(int opcionesTotal,int cuentaActual,int &size){
        int lenamigosActuales;
        QString *amigosActuales;
        amigosActuales=CargarDatos(opcionesTotal,cuentaActual,1,lenamigosActuales);
        ifstream fdatosr;
        fdatosr.open("datos.txt",ios::in);
        int cuentasTotal;
        fdatosr>>cuentasTotal;
        fdatosr.ignore();
        int lencuentasDif=cuentasTotal-1;
        QString *cuentasDif=new QString[lencuentasDif];
        string garbage;
        int lenstringaux;
        int cont=0;
        for(int i=0;i<cuentasTotal;i++){
            if(i==cuentaActual){
                fdatosr>>garbage;
            }
            else{
                string aux;
                fdatosr>>aux;
                int sn=(int)aux.size();
                cuentasDif[cont].resize(sn);
                for(int j=0;j<sn;j++){
                    cuentasDif[cont][j]=aux[j];
                }
                cont++;
            }
            fdatosr>>garbage;
            for(int j=0;j<opcionesTotal;j++){
                fdatosr>>lenstringaux;
                fdatosr.ignore();
                for(int k=0;k<lenstringaux;k++) getline(fdatosr,garbage);
            }
        }
        fdatosr.close();

        QString *qsaux=new QString[lencuentasDif];
        size=0;
        for(int i=0;i<lencuentasDif;i++){
            bool encontrado=false;
            for(int j=0;j<lenamigosActuales;j++){
                if(cuentasDif[i]==amigosActuales[j]) {
                    encontrado=true;
                    break;
                }
            }
            if(!encontrado){
                qsaux[size].resize(cuentasDif[i].size());
                qsaux[size]=cuentasDif[i];
                size++;
            }
        }
        QString *amigosPosibles=new QString[size];
        for(int i=0;i<size;i++){
            amigosPosibles[i].resize(qsaux[i].size());
            amigosPosibles[i]=qsaux[i];
        }
        return amigosPosibles;
    }

    void GuardarDatoSiempre(int opcionesTotal,QString sdato,int cuentaActual,int opcion){
        int lenstringant,lenstringpos;
        CantAntPosOpcion(opcionesTotal,cuentaActual,lenstringant,lenstringpos,opcion);
        string sant[lenstringant];
        string spos[lenstringpos];
        ifstream fdatosr;
        fdatosr.open("datos.txt",ios::in);
        for(int i=0;i<lenstringant;i++) getline(fdatosr,sant[i]);
        int lenOpcion;
        fdatosr>>lenOpcion;
        fdatosr.ignore();
        string datosOpcion[lenOpcion];
        for(int i=0;i<lenOpcion;i++) getline(fdatosr,datosOpcion[i]);
        for(int i=0;i<lenstringpos;i++) getline(fdatosr,spos[i]);
        fdatosr.close();
        ofstream fdatosw;
        fdatosw.open("datos.txt",ios::out);
        string sadd;
        sadd.resize(sdato.size());
        for(int i=0;i<sdato.size();i++) sadd[i]=sdato[i].toLatin1();
        for(int i=0;i<lenstringant;i++) fdatosw<<sant[i]<<endl;
        fdatosw<<lenOpcion+1<<endl;
        for(int i=0;i<lenOpcion;i++) fdatosw<<datosOpcion[i]<<endl;
        fdatosw<<sadd<<endl;
        for(int i=0;i<lenstringpos;i++) fdatosw<<spos[i]<<endl;
        fdatosw.close();
    }

    bool GuardarDato(int opcionesTotal,QString sdato,int cuentaActual,int opcion){
        int lenstringant,lenstringpos;
        CantAntPosOpcion(opcionesTotal,cuentaActual,lenstringant,lenstringpos,opcion);
        string sant[lenstringant];
        string spos[lenstringpos];
        ifstream fdatosr;
        fdatosr.open("datos.txt",ios::in);
        for(int i=0;i<lenstringant;i++) getline(fdatosr,sant[i]);
        int lenOpcion;
        fdatosr>>lenOpcion;
        fdatosr.ignore();
        string datosOpcion[lenOpcion];
        for(int i=0;i<lenOpcion;i++) getline(fdatosr,datosOpcion[i]);
        for(int i=0;i<lenstringpos;i++) getline(fdatosr,spos[i]);
        fdatosr.close();
        bool encontrado=false;
        for(int i=0;i<lenOpcion;i++){
            if((int)sdato.size()!=(int)datosOpcion[i].size()) continue;
            else{
                bool cont=true;
                for(int j=0;j<(int)sdato.size();j++){
                    if(sdato[j]!=datosOpcion[i][j]){
                        cont=false;
                        break;
                    }
                }
                if(cont==true){
                    encontrado=true;
                    break;
                }
            }
        }
        if(!encontrado){
            ofstream fdatosw;
            fdatosw.open("datos.txt",ios::out);
            string sadd;
            sadd.resize(sdato.size());
            for(int i=0;i<sdato.size();i++) sadd[i]=sdato[i].toLatin1();
            for(int i=0;i<lenstringant;i++) fdatosw<<sant[i]<<endl;
            fdatosw<<lenOpcion+1<<endl;
            for(int i=0;i<lenOpcion;i++) fdatosw<<datosOpcion[i]<<endl;
            fdatosw<<sadd<<endl;
            for(int i=0;i<lenstringpos;i++) fdatosw<<spos[i]<<endl;
            fdatosw.close();
            return true;
        }
        else return false;
    }

    void AgregarIteracionPublicacionComentario(int opcionesTotal,int cuentaActual,int opcion){
        int lenstringant,lenstringpos;
        CantAntPosOpcion(opcionesTotal,cuentaActual,lenstringant,lenstringpos,opcion);
        string sant[lenstringant];
        string spos[lenstringpos];
        ifstream fdatosr;
        fdatosr.open("datos.txt",ios::in);
        for(int i=0;i<lenstringant;i++) getline(fdatosr,sant[i]);
        int lenOpcion;
        fdatosr>>lenOpcion;
        fdatosr.ignore();
        string datosOpcion[lenOpcion];
        for(int i=0;i<lenOpcion;i++) getline(fdatosr,datosOpcion[i]);
        for(int i=0;i<lenstringpos;i++) getline(fdatosr,spos[i]);
        fdatosr.close();
        ofstream fdatosw;
        fdatosw.open("datos.txt",ios::out);
        for(int i=0;i<lenstringant;i++) fdatosw<<sant[i]<<endl;
        fdatosw<<lenOpcion+1<<endl;
        for(int i=0;i<lenOpcion;i++) fdatosw<<datosOpcion[i]<<endl;
        fdatosw<<endl;
        for(int i=0;i<lenstringpos;i++) fdatosw<<spos[i]<<endl;
        fdatosw.close();
    }

    void AgregarInteraccionPublicacionComentario(int opcionesTotal,int cuentaActual,int opcion){
        int lenstringant,lenstringpos;
        CantAntPosOpcion(opcionesTotal,cuentaActual,lenstringant,lenstringpos,opcion);
        string sant[lenstringant];
        string spos[lenstringpos];
        ifstream fdatosr;
        fdatosr.open("datos.txt",ios::in);
        for(int i=0;i<lenstringant;i++) getline(fdatosr,sant[i]);
        int lenOpcion;
        fdatosr>>lenOpcion;
        fdatosr.ignore();
        string datosOpcion[lenOpcion];
        for(int i=0;i<lenOpcion;i++) getline(fdatosr,datosOpcion[i]);
        for(int i=0;i<lenstringpos;i++) getline(fdatosr,spos[i]);
        fdatosr.close();
        ofstream fdatosw;
        fdatosw.open("datos.txt",ios::out);
        for(int i=0;i<lenstringant;i++) fdatosw<<sant[i]<<endl;
        fdatosw<<lenOpcion+1<<endl;
        for(int i=0;i<lenOpcion;i++) fdatosw<<datosOpcion[i]<<endl;
        fdatosw<<"0"<<endl;
        for(int i=0;i<lenstringpos;i++) fdatosw<<spos[i]<<endl;
        fdatosw.close();
    }

    void GuardarComentario(int opcionesTotal,QString sdato,int cuentaActual,int opcion){
        int lenstringant,lenstringpos;
        CantAntPosOpcion(opcionesTotal,cuentaActual,lenstringant,lenstringpos,opcion);
        string sant[lenstringant];
        string spos[lenstringpos];
        ifstream fdatosr;
        fdatosr.open("datos.txt",ios::in);
        for(int i=0;i<lenstringant;i++) getline(fdatosr,sant[i]);
        int lenOpcion;
        fdatosr>>lenOpcion;
        fdatosr.ignore();
        string datosOpcion[lenOpcion];
        for(int i=0;i<lenOpcion;i++) getline(fdatosr,datosOpcion[i]);
        for(int i=0;i<lenstringpos;i++) getline(fdatosr,spos[i]);
        fdatosr.close();
        ofstream fdatosw;
        fdatosw.open("datos.txt",ios::out);
        string sadd;
        sadd.resize(sdato.size());
        for(int i=0;i<sdato.size();i++) sadd[i]=sdato[i].toLatin1();
        for(int i=0;i<lenstringant;i++) fdatosw<<sant[i]<<endl;
        fdatosw<<lenOpcion<<endl;
        for(int i=0;i<lenOpcion;i++) {
            fdatosw<<datosOpcion[i];
            if(i!=lenOpcion-1) fdatosw<<endl;
        }
        if(datosOpcion[lenOpcion-1].size()!=0)fdatosw<<"\t";
        fdatosw<<sadd<<endl;
        for(int i=0;i<lenstringpos;i++) fdatosw<<spos[i]<<endl;
        fdatosw.close();
    }

    void AumentarInteraciones(int opcionesTotal,int posicion,int cuentaActual,int opcion){
        int lenstringant,lenstringpos;
        CantAntPosEliminar(opcionesTotal,cuentaActual,lenstringant,lenstringpos,opcion);
        string sant[lenstringant];
        string spos[lenstringpos];
        ifstream fdatosr;
        fdatosr.open("datos.txt",ios::in);
        string garbage;
        for(int i=0;i<lenstringant;i++) getline(fdatosr,sant[i]);

        int lendatos;
        fdatosr>>lendatos;
        fdatosr.ignore();
        lendatos--;
        string datos[lendatos];
        for(int i=0;i<posicion;i++) getline(fdatosr,datos[i]);
        string snum;
        getline(fdatosr,snum);
        for(int i=posicion;i<lendatos;i++) getline(fdatosr,datos[i]);

        for(int i=0;i<lenstringpos;i++) getline(fdatosr,spos[i]);
        fdatosr.close();
        QString qsnum;
        int sn=(int)snum.size();
        qsnum.resize(sn);
        for(int j=0;j<sn;j++){
            qsnum[j]=snum[j];
        }
        int inum=qsnum.toInt();
        inum++;
        ofstream fdatosw;
        fdatosw.open("datos.txt",ios::out);
        for(int i=0;i<lenstringant;i++) fdatosw<<sant[i]<<endl;
        fdatosw<<lendatos+1<<endl;
        for(int i=0;i<lendatos;i++) fdatosw<<datos[i]<<endl;
        fdatosw<<inum<<endl;
        for(int i=0;i<lenstringpos;i++) fdatosw<<spos[i]<<endl;
        fdatosw.close();
    }

};

#endif // FILES_H
