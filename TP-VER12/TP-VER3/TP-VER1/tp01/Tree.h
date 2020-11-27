#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <vector>
#include <time.h>
#include <functional>
#include <QTextStream>
#include <QListWidget>
#include <queue>
#include "Publicacion.h"

using namespace std;

template <typename T>
class Node{
  public:
  T data; // puntero
  Node* left;
  Node* right;
  int Altura;
  Node(T data, int Altura = 1,Node* left = nullptr, Node* right = nullptr): data(data), Altura(Altura),left(left), right(right){}
};

template <typename OBJ,typename KEY = OBJ>
class BST{
  public:
  Node<OBJ>* root;
  function<KEY(OBJ)> key;
  BST(function<KEY(OBJ)> key = [](OBJ obj){return obj;},Node<OBJ>* root = nullptr):key(key),root(root){}
  Node<OBJ>* getNode(KEY val){
      Node<OBJ>* current = this->root;
      while(current != nullptr){
        if(val == key(current->data)){ //<---
            return current;
        }else if(val < key(current->data)){
            current = current->left;
        }else if(val > key(current->data)){
            current = current->right;
        }
      }
      return nullptr;
  }
  Node<OBJ>* getNodepos(KEY val){
      Node<OBJ>* current = this->root;
      while(current != nullptr){
        if(val == key(current->data)){ //<---
            return current;
        }else if(val < key(current->data)){
            current = current->left;
        }else if(val > key(current->data)){
            current = current->right;
        }
      }
      return nullptr;
  }
  int max(int a, int b){
        return (a>b)? a:b;
    }
    int Altura(Node<OBJ>* N){
        if(N == nullptr)
          return 0;
        return N->Altura;
    }
    void ActualizarAltura(Node<OBJ>* node) {
        if (node != nullptr) {
            node->Altura = max(Altura(node->left), Altura(node->right)) + 1;
        }
    }

    void rotacion_R(Node<OBJ>*& node){
        Node<OBJ>* aux = node->left;
        node->left = aux->right;
        ActualizarAltura(node);
        aux->right = node;
        ActualizarAltura(aux);
        node = aux;
    }

    void rotacion_L(Node<OBJ>*& node){
      Node<OBJ>* aux = node->right;
      node->right = aux->left;
      ActualizarAltura(node);
      aux->left = node;
      ActualizarAltura(aux);
      node = aux;
    }

    int getBalance(Node<OBJ>* N){
        if(N == nullptr)
            return 0;
        return Altura(N->left) - Altura(N->right);
    }

    void add(OBJ val){add(this->root, val);}
    void add(Node<OBJ>*& node, OBJ val){
      // 1) Insertar BST normal
      Node<OBJ>* new_node = new Node<OBJ>(val);
      if(node == nullptr){
        node = new_node;
        return;
      }else{
      if(key(val) <= key(node->data)){
        add(node->left, val);
      }else{ //VAL > NODE->DATA
        add(node->right, val);
      }
      // 2) Actualizar alturas del antecesor
      node->Altura = 1 + max(Altura(node->left), Altura(node->right));
      // 3) Balance del antecesor
      int hl = Altura(node->left);
      int hr = Altura(node->right);

      if (hr - hl < -1) {
          hl = Altura(node->left->left);
          hr = Altura(node->left->right);
          if (hr > hl) {
              rotacion_L(node->left);
          }
          rotacion_R(node);
      } else if (hr - hl > 1) {
          hl = Altura(node->right->left);
          hr = Altura(node->right->right);
          if (hl > hr) {
              rotacion_R(node->right);
          }
          rotacion_L(node);
      } else {
          ActualizarAltura(node);
      }
      }
    }

  void add_node(Node<OBJ>* ref){add_node(this->root, ref);}
  void add_node(Node<OBJ>*& node, Node<OBJ>* ref){
    Node<OBJ>* new_node = ref;
    if(node == nullptr){
      node = new_node;
      return;
    }
    if(key(new_node->data) <= key(node->data)){
      add_node(node->left, new_node);
    }else{ //VAL > NODE->DATA
      add_node(node->right, new_node);
    }
  }

  void del(OBJ val){del(this->root, val);}
  void del(Node<OBJ>*& node, OBJ val){
    //CASO BASE
    if(node == nullptr) return;

    if(key(val) < key(node->data)){
      del(node->left, val);
    } else if(key(val) > key(node->data)){
      del(node->right, val);
    }else{
      if(node->left == nullptr){//NO TEIENE HIJO IZQUIERDO
        node = node->right;
      } else if(node->right == nullptr){//NO TIENE HIJO DERECHO
        node = node->left;
      }else{
        //TODO: MIN_NODE
        Node<OBJ>* temp = min_node(node->right);
        node->data = temp->data;
        del(node->right, temp->data);
      }
    }
  }

  void inorder(QListWidget* lista){ inorder(lista, this->root);}
  void inorder(QListWidget* lista, Node<OBJ>* node){
    //CASO BASE
    if(node == nullptr) return;
    inorder(lista,node->left);
    lista->addItem(node->data->toString());
    inorder(lista,node->right);
  }

  void postorder(QListWidget* lista){ postorder(lista, this->root);}
  void postorder(QListWidget* lista, Node<OBJ>* node){
    //CASO BASE
    if(node == nullptr) return;
    postorder(lista,node->right);
    lista->addItem(node->data->toString());
    postorder(lista,node->left);
  }

  void inorder_50(QListWidget* lista){ inorder_50(lista, this->root, 0);}
  void inorder_50(QListWidget* lista, Node<OBJ>* node, int n){
    //CASO BASE
    if(node == nullptr || n >= 60) return;
    inorder_50(lista,node->left,(n+1)*2);
    lista->addItem(node->data->toString());
    inorder_50(lista,node->right,(n+1)*2);
  }

  void postorder_50(QListWidget* lista){ postorder_50(lista, this->root, 0);}
  void postorder_50(QListWidget* lista, Node<OBJ>* node, int n){
    //CASO BASE
    if(node == nullptr || n >= 60) return;
    postorder_50(lista,node->right, (n+1)*2);
    lista->addItem(node->data->toString());
    postorder_50(lista,node->left, (n+1)*2);
  }

  void inorder_l(function<void(OBJ)> imprimir) { inorder_l(imprimir, this->root);}
  void inorder_l(function<void(OBJ)> imprimir, Node<OBJ>* node){
    if(node == nullptr) return;
    inorder_l(imprimir,node->left);
    imprimir(node->data);
    inorder_l(imprimir,node->right);
  }

  Node<OBJ>* findAll_query(QString query, QListWidget* ventana, function<QString(Publicacion*)> get){
      Node<OBJ>* node_null = nullptr;
      queue<Node<OBJ>*> q;
      ventana->clear();
      q.push(this->root);
      while(q.empty()==false){
          Node<OBJ>* actual = q.front();
          if(get(actual->data).contains(query,Qt::CaseInsensitive)){
            ventana->addItem(actual->data->toString());
          }
          q.pop();
          if(actual->left != NULL) q.push(actual->left);
          if(actual->right != NULL) q.push(actual->right);
      }
      return node_null;
  }

  Node<OBJ>* min_node(Node<OBJ>* node){
    if(node->left == nullptr) return node;
    while(node && node->left != nullptr){
      node = node->left;
    }
    return node;
  }

};


#endif // TREE_H
