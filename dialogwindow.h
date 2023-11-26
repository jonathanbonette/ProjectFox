#ifndef DIALOGWINDOW_H
#define DIALOGWINDOW_H

#include "battlewindow.h"
#include "dialogtree.h"
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QLabel>

// Classe para representar a janela de diálogo com árvore de escolhas
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
    void handleSpecialNode();
    void handleAcceptGift();
    void handleGetItems();

public:
    // Método para criar os widgets da janela
    void createWidgets();

    DialogNode* currentNode;    // Nó atual na árvore de diálogo

    QLabel* label;              // Rótulo para exibir o texto do nó

    QLabel *npcImgLabel;

    QPushButton* leftButton;        // Botão para escolher a opção da esquerda
    QPushButton* rightButton;       // Botão para escolher a opção da direita
    QPushButton* acceptGiftButton;  // Botão de aceitar o presente
    QPushButton* getItemsButton;    // Botão de pegar os itens

    BattleWindow* battleWindow;
};

#endif // DIALOGWINDOW_H
