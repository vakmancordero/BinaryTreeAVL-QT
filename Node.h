#ifndef AVLNODE_H
#define AVLNODE_H

class Node {

public:
    Node(int value);

    int getValue() const {
        return value;
    }

    Node *getLeft() const {
        return left;
    }

    Node *getRight() const {
        return right;
    }

    void setValue(int value) {
        this->value = value;
    }

    void setHeight(int height) {
        this->height = height;
    }

    void setLeft(Node *left) {
        this->left = left;
    }

    void setRight(Node *right) {
        this->right = right;
    }

    Node *rightRotation();

    Node *leftRotation();

    Node *getLesserNode();

    static int getHeight(Node *node);

    static int getBalance(Node *node);

private:

    int value;
    int height;

    Node *left;
    Node *right;

};

#endif
