#ifndef DIALOGTREE_H
#define DIALOGTREE_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

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

class DialogWindow : public QMainWindow
{
    Q_OBJECT

public:
    // Construtor e destrutor
    DialogWindow(QWidget *parent = nullptr);
    ~DialogWindow();

public slots:
    // Slot para lidar com as escolhas do usuário
    void handleChoice();

private:
    // Método para criar os widgets da janela
    void createWidgets();

    DialogNode* currentNode;    // Nó atual na árvore de diálogo
    QLabel* label;              // Rótulo para exibir o texto do nó
    QPushButton* leftButton;    // Botão para escolher a opção da esquerda
    QPushButton* rightButton;   // Botão para escolher a opção da direita
};

#endif // DIALOGTREE_H
