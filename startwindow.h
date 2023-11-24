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
    StartWindow(QWidget *parent = nullptr);

signals:
    void startButtonClicked();
    void quitButtonClicked();
    void selectCharacterButtonClicked();

    // Test Remover Após Mesclar Telas ***
    void battleButtonClicked();

public:
    DialogWindow dialogWindow;                          // Declarando DialogWindow como uma variável membro
    CharacterSelectionWindow characterSelectionWindow;  // Adiciona a janela de seleção de personagens
    BattleWindow battleWindow;

};

#endif // STARTWINDOW_H
