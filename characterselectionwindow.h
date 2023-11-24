#ifndef CHARACTERSELECTIONWINDOW_H
#define CHARACTERSELECTIONWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include "character.h"

class CharacterSelectionWindow : public QWidget
{
    Q_OBJECT

public:
    // Construtor
    CharacterSelectionWindow(QWidget *parent = nullptr);

public slots:
    // Slot para processar a seleção do personagem
    void characterSelected(Character *character);

private:
    // Método para criar widgets na tela de seleção de personagens
    void createWidgets();
};

#endif // CHARACTERSELECTIONWINDOW_H
