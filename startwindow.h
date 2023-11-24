#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QWidget>
#include <QPushButton>
#include "battlewindow.h"
#include "characterselectionwindow.h"
#include "dialogtree.h"

class StartWindow : public QWidget
{
    Q_OBJECT

public:
    // Construtor
    StartWindow(QWidget *parent = nullptr);

signals:
    // Sinais emitidos quando os botões são clicados
    void startButtonClicked();
    void quitButtonClicked();

    // Test Remover Após Mesclar Telas ***
    void battleButtonClicked();
    void selectCharacterButtonClicked();

public:
    DialogWindow dialogWindow;                          // Instância da janela de diálogo
    CharacterSelectionWindow characterSelectionWindow;  // Instância da janela de seleção de personagens
    BattleWindow battleWindow;                          // Instância da janela de batalha

};

#endif // STARTWINDOW_H
