#include "dialogtree.h"

DialogNode::DialogNode(const QString &text)
    : text(text), leftChild(nullptr), rightChild(nullptr)
{
}

// Implementações dos métodos da classe DialogNode

const QString& DialogNode::getText() const { return text; }

DialogNode* DialogNode::getLeftChild() const { return leftChild; }

DialogNode* DialogNode::getRightChild() const { return rightChild; }

void DialogNode::setLeftChild(DialogNode* node) { leftChild = node; }

void DialogNode::setRightChild(DialogNode* node) { rightChild = node; }
