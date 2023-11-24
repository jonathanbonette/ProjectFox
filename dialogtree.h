#ifndef DIALOGTREE_H
#define DIALOGTREE_H

#include <QVBoxLayout>
#include <QPushButton>

// Classe para representar um nó na árvore de diálogo
class DialogNode
{
public:
    // Construtor que recebe o texto do nó
    DialogNode(const QString &text);

    // Retorna o texto do nó
    const QString& getText() const;

    // Métodos para obter os filhos do nó
    DialogNode* getLeftChild() const;
    DialogNode* getRightChild() const;

    // Métodos para configurar os filhos do nó
    void setLeftChild(DialogNode* node);
    void setRightChild(DialogNode* node);

private:
    QString text;               // Texto do nó
    DialogNode* leftChild;      // Filho da esquerda
    DialogNode* rightChild;     // Filho da direita
};

#endif // DIALOGTREE_H
