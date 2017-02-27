#include "BinaryTreeAVL.h"

#include <QtMath>
#include <QDebug>
#include <QFile>
#include <QProcess>

#include <iostream>

using namespace std;

BinaryTreeAVL::BinaryTreeAVL() {
    root = nullptr;
}

Node *BinaryTreeAVL::add(Node *node, int value) {

    // Realiza la rotación de árbol binario de búsqueda
    if (node == nullptr) {

        return new Node(value);

    }

    if (value < node->getValue()) {

        node->setLeft(add(node->getLeft(), value));

    } else {

        node->setRight(add(node->getRight(), value));

    }

    // Actualiza la altura de este nodo anterior
    node->setHeight(1 + qMax(Node::getHeight(node->getLeft()), Node::getHeight(node->getRight())));

    const int balance = Node::getBalance(node);

    // Si este nodo se desequilibra, entonces hay 4 casos

    // Caso izquierda izquierda
    if (balance > 1 && value < node->getLeft()->getValue()) {

        this->ll++;

        return node->rightRotation();

    }

    // Caso derecha derecha
    if (balance < -1 && value > node->getRight()->getValue()) {

        this->rr++;

        return node->leftRotation();

    }

    // Caso izquierda derecha
    if (balance > 1 && value > node->getLeft()->getValue()) {

        this->lr++;

        node->setLeft(node->getLeft()->leftRotation());

        return node->rightRotation();

    }

    // Caso derecha izquierda
    if (balance < -1 && value < node->getRight()->getValue()) {


        this->rl++;
        node->setRight(node->getRight()->rightRotation());

        return node->leftRotation();

    }

    // Regresa el nodo sin cambiar
    return node;

}

Node *BinaryTreeAVL::remove(Node *root, int value) {

    // Realiza la eliminación normal
    if (root == nullptr) {
        return nullptr;
    }

    /*
     * Si el dato para borrar es más pequeño que el dato de la raíz
     * entonces está en el subárbol izquierdo
     */
    if (value < root->getValue()) {

        root->setLeft(remove(root->getLeft(), value));

    /*
     * Si el dato para borrar es más grande que el dato de la raíz
     * entonces está en el subárbol derecho
     */

    } else if (value > root->getValue()) {

        root->setRight(remove(root->getRight(), value));

    /*
     * Si el dato es el mismo que el dato de la raíz, entonces este es el nodo
     * para borrar
     */

    } else {

        // Nodo con un solo hijo o ninguno
        if (root->getLeft() == nullptr || root->getRight() == nullptr) {

            auto temp = root->getLeft() ? root->getLeft() : root->getRight();

            // Caso sin hijo
            if (temp == nullptr) {

                temp = root;

                root = nullptr;

            // Caso con un solo hijo
            } else {

                // Copia el contenido del hijo no vacío
                *root = *temp;
            }

            delete temp;

        } else {

            /*
             * Nodo con dos hijos
             * obtiene el sucesor en inorden
             * el más pequeño en el subárbol derecho
             */

            auto temp = root->getRight()->getLesserNode();

            // Copia el dato del sucesor en inorden a este nodo
            root->setValue(temp->getValue());

            // Elimina el sucesor en inorden
            root->setRight(remove(root->getRight(), temp->getValue()));

        }
    }

    // Si el árbol tenía solo un nodo entonces adiós
    if (root == nullptr) {
        return nullptr;
    }

    // Actualiza la altura del nodo actual
    root->setHeight(1 + qMax(Node::getHeight(root->getLeft()), Node::getHeight(root->getRight())));

    // Obtiene el factor de equilibrio de este nodo para saber si este nodo se desequilibró
    const int balance = Node::getBalance(root);

    // Si este nodo se desequilibró, entonces hay 4 casos

    // Caso izquierda izquierda
    if (balance > 1 && Node::getBalance(root->getLeft()) >= 0) {

        return root->rightRotation();

    }

    // Caso izquierda derecha
    if (balance > 1 && Node::getBalance(root->getLeft()) < 0) {

        root->setLeft(root->getLeft()->leftRotation());

        return root->rightRotation();

    }

    // Caso derecha derecha
    if (balance < -1 && Node::getBalance(root->getRight()) <= 0) {

        return root->leftRotation();

    }

    // Caso der izq
    if (balance < -1 && Node::getBalance(root->getRight()) > 0) {

        root->setRight(root->getRight()->rightRotation());

        return root->leftRotation();

    }

    return root;
}

void BinaryTreeAVL::add(int value) {

    root = add(root, value);

    rotaciones();

    this->show();
}

void BinaryTreeAVL::rotaciones() {
    cout << "Izquierda a derecha: " << this->lr << endl;
    cout << "Derecha a izquierda: " << this->rl << endl;
    cout << "Izquierda a izquierda: " << this->ll << endl;
    cout << "Derecha a derecha: " << this->rr << endl;
}

void BinaryTreeAVL::remove(int value) {

    root = remove(root, value);

    rotaciones();

    this->show();

}

void BinaryTreeAVL::preOrder(Node *root) {
    if (root != nullptr) {
        cout << root->getValue() << "\n";
        preOrder(root->getLeft());
        preOrder(root->getRight());
    }
}

void BinaryTreeAVL::postOrder(Node *root) {
    if (root != nullptr) {
        postOrder(root->getLeft());
        postOrder(root->getRight());
        cout << root->getValue() << "\n";
    }
}

void BinaryTreeAVL::inOrder(Node *root) {
    if (root != nullptr) {
        inOrder(root->getLeft());
        cout << root->getValue() << "\n";
        inOrder(root->getRight());
    }
}



void BinaryTreeAVL::graph(Node* node, QTextStream *stream) {

    if (node != NULL) {

        *stream << "\t\t" << "n" << node->getValue() << "[label=\"" << node->getValue() <<"\"];" << endl;

        if (node->getLeft() != NULL) {

            *stream << "\t\tn" << node->getValue() << "--" << "n" << node->getLeft()->getValue() << ";" << endl;

            this->graph(node->getLeft(), stream);

        } else {

            *stream << "\t\t" << "n" << node->getValue() << "leftNull" << "[style=\"filled\",label=\"NULL\"];" << endl;

            *stream << "\t\tn" << node->getValue() << "--" << "n" << node->getValue() << "leftNull" << endl;

        }

        if (node->getRight() != NULL) {

            *stream << "\t\tn" << node->getValue() << "--" << "n" << node->getRight()->getValue() << ";" << endl;

            this->graph(node->getRight(), stream);

        } else {

            *stream << "\t\t" << "n" << node->getValue() << "rightNull" << "[style=\"filled\",label=\"NULL\"];" << endl;

            *stream << "\t\tn" << node->getValue() << "--" << "n" << node->getValue() << "rightNull" << endl;

        }

    }

}

QByteArray BinaryTreeAVL::prepareGraph() {

    QByteArray byteArray = QByteArray();

    QTextStream stream(&byteArray, QIODevice::ReadWrite);

    stream << "graph ""{" << endl;
    stream << "\tnode[fontsize=10,margin=0,width=\".4\", height=\".3\"];" << endl;
    stream << "\tsubgraph cluster17{" << endl;

    this->graph(this->root, &stream);

    stream << "\t}\n" << "}" << endl;

    stream.flush();

    return byteArray;

}

void BinaryTreeAVL::show() {

    QProcess* process = new QProcess();
    QByteArray byteArray = this->prepareGraph();

    QFile file("C:/Files/avl.dot");
    file.open(QIODevice::WriteOnly);
    file.write(byteArray);
    file.close();

    process->start("dot", QStringList() << "-Tpng" << "C:/Files/avl.dot" << "-o" << "C:/Files/avl.png");
    process->waitForReadyRead(100);

    qDebug() << process->arguments();
    qDebug() << process->readAll();
    qDebug() << process->exitCode();

    /*
    QByteArray data;
    QPixmap pixmap = QPixmap();

    while(process->waitForReadyRead(100)){
        data.append(process->readAll());
    }

    pixmap.loadFromData(data);

    this->_scene->addPixmap(pixmap);
    this->_view->show();
    */

}

Node* BinaryTreeAVL::find(int value, Node* node) {

    if (node != NULL) {

        if (value == node->getValue()) {

            return node;

        }

        if (value < node->getValue()) {

            return find(value, node->getLeft());

        } else {

            return find(value, node->getRight());

        }

    } else {

        return NULL;

    }

}

Node* BinaryTreeAVL::find(int value){

    return this->find(value, this->root);

}

