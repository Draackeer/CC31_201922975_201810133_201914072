#ifndef AMIGOS_H
#define AMIGOS_H
#include <QMainWindow>
#include "QWindow"

template<class T>
class Amigos_Favoritos {
private:
    struct Node{
        Node* Next;
        T element;
        Node(Node* Nex,T elemen):Next(Nex),element(elemen){};
    };
    Node* Header;
    int len;
public:
    Amigos_Favoritos():Header(nullptr),len(0){};
    ~Amigos_Favoritos(){

     while(Header!=nullptr){
          Node* aux = Header;
          Header = Header->Next;
          delete aux;
        }
    }
    T Get_Lista(){
        QString all_element = "";
        for(int i=0;i<len;i++){
            all_element = all_element + get_pos(i) + "\n";
        }
        return all_element;
    }
   int get_leng(){
       return len;
   }

   bool empty(){
       return len == 0;
   }
   void add_first(T element){
       Header = new Node(Header,element);
       ++len;
   }
   void add_pos(T element, int pos){
       if(pos<0 || pos>len) return;
       if(pos ==0) add_first(element);
       else{
           Node* aux = Header;
           for(int i=1;i<pos;i++){
                aux = aux->Next;
           }
           aux->Next = new Node(aux->Next,element);
           ++len;
       }
   }
   void add_last(T element){
       add_pos(element,len);
   }
   T get_first(){
       if(len>0)
       return Header->element;
   }
   T get_pos(int pos){
       if(pos<0||pos>=len) return nullptr;
       Node* aux = Header;
       for(int i=0;i<pos;i++){
           aux = aux->Next;
       }
       return aux->element;
   }
   T get_last(){
        get_pos(len-1);
   }
   void remove_first(){
       if(len>0){
           Node* aux = Header;
           Header = Header->Next;
           delete aux;
           --len;
       }

   }
   void remove_pos(int pos){
       if(pos<0 || pos >=len) return;
       if(pos == 0) remove_first();
       else {
            Node* Aux = Header;
            for(int i=1;i<pos;i++){
                Aux = Aux->Next;
            }
            Aux->Next = (Aux->Next)->Next;
            --len;
       }
   }
   void remove_last(){
       remove_pos(len-1);
   }
};
#endif // AH
