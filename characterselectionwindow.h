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
    CharacterSelectionWindow(QWidget *parent = nullptr);

public slots:
    void characterSelected(Character *character);

private:
    void createWidgets();
};

#endif // CHARACTERSELECTIONWINDOW_H
