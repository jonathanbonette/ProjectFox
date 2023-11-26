// dialoghelper.cpp

#include "dialoghelper.h"
#include "dialogwindow.h"
#include <QLabel>
#include <QMovie>

void DialogHelper::updateBackground(DialogWindow *window, const QString &imagePath)
{
    QPixmap backgroundImage(imagePath);
    QPalette palette;
    palette.setBrush(window->backgroundRole(), backgroundImage);
    window->setPalette(palette);
}

void DialogHelper::updateMovieImage(DialogWindow *window, const QString &moviePath)
{
    QMovie *movie = new QMovie(moviePath);
    window->npcImgLabel->setMovie(movie);
    movie->start();

    window->npcImgLabel->setAlignment(Qt::AlignCenter);
    window->npcImgLabel->show();
    window->npcImgLabel->lower();
}

void DialogHelper::updateImageLabel(DialogWindow *window, const QString &imagePngPath)
{
    QPixmap image(imagePngPath);
    window->npcImgLabel->setPixmap(image);
    window->npcImgLabel->setAlignment(Qt::AlignCenter);
    window->npcImgLabel->show();
    window->npcImgLabel->lower();
}

void DialogHelper::updateLabel(DialogWindow *window, const QString &text, Qt::Alignment alignment, const QString &styleSheet)
{
    window->label->setText(text);
    window->label->setAlignment(alignment);
    window->label->setStyleSheet(styleSheet);
}

void DialogHelper::showAcceptGiftButton(DialogWindow *window)
{
    // Lógica para mostrar o botão "Aceitar o presente"
}

void DialogHelper::hideChoiceButtons(DialogWindow *window)
{
    window->leftButton->hide();
    window->rightButton->hide();
}

void DialogHelper::showChoiceButtons(DialogWindow *window)
{
    window->leftButton->show();
    window->rightButton->show();
}
