#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QWidget>
#include <QPushButton>
//#include "battlewindow.h"
#include "characterselectionwindow.h"
#include "dialogwindow.h"

class StartWindow : public QWidget
{
    Q_OBJECT

public:
    // Construtor
    StartWindow(QWidget *parent = nullptr);

signals:
    // Sinais emitidos quando os botões são clicados
    void quitButtonClicked();
    void selectCharacterButtonClicked();

public:
    DialogWindow dialogWindow;                          // Instância da janela de diálogo
    CharacterSelectionWindow characterSelectionWindow;  // Instância da janela de seleção de personagens
};

#endif // STARTWINDOW_H
