#include "Node.h"
#include <QtMath>

#include <iostream>

using namespace std;

Node::Node(int value) {
    this->value = value;
    left = nullptr;
    right = nullptr;
    height = 1;
}

int Node::getHeight(Node *node) {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

Node *Node::rightRotation()
{
    auto x = left;
    auto t2 = x->right;

    // realiza rotación
    x->right = this;
    left = t2;

    // actualiza alturas
    height = 1 + qMax(Node::getHeight(left), Node::getHeight(right));
    x->height = 1 + qMax(Node::getHeight(x->left), Node::getHeight(x->right));

    // regresa raíz nueva
    return x;
}

Node *Node::leftRotation()
{
    auto y = right;
    auto t2 = y->left;

    // realiza rotación
    y->left = this;
    right = t2;

    // actualiza alturas
    height = 1 + qMax(Node::getHeight(left), Node::getHeight(right));
    y->height = 1 + qMax(Node::getHeight(y->left), Node::getHeight(y->right));

    // regresa raíz nueva
    return y;
}

int Node::getBalance(Node *node)
{
    if (node == nullptr) {
        return 0;
    }
    return Node::getHeight(node->getLeft()) - Node::getHeight(node->getRight());
}

Node *Node::getLesserNode()
{
    // dado un árbol de búsqueda no vacío, regresa el nodo
    // con el valor del dato más pequeño encontrado en ese árbol.
    // El árbol entero no necesita ser buscado
    auto actual = this;

    // bucle hacia abajo para encontrar la hoja más a la izquierda
    while (actual->getLeft() != nullptr) {
        actual = actual->getLeft();
    }
    return actual;
}
