#ifndef DIALOGTREE_H
#define DIALOGTREE_H

#include <QVBoxLayout>
#include <QPushButton>

// Classe para representar um nó na árvore de diálogo
class DialogNode
{
public:
    // Construtor que recebe o texto do nó
    DialogNode(QString text, QString leftButtonText = "", QString rightButtonText = "");


    // Retorna o texto do nó
    const QString& getText() const;

    // Métodos para obter os filhos do nó
    DialogNode* getLeftChild() const;
    DialogNode* getRightChild() const;

    // Métodos para configurar os filhos do nó
    void setLeftChild(DialogNode* node);
    void setRightChild(DialogNode* node);

    QString getLeftButtonText() const;
    QString getRightButtonText() const;

private:
    QString text;               // Texto do nó
    DialogNode* leftChild;      // Filho da esquerda
    DialogNode* rightChild;     // Filho da direita

    // Texto dos botões personalizados
    QString leftButtonText;
    QString rightButtonText;
};

#endif // DIALOGTREE_H
