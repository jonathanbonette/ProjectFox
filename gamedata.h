#ifndef GAMEDATA_H
#define GAMEDATA_H

#include "character.h"
#include "dialogtree.h"

class GameData {

private:
    GameData() {}

public:
    void setPlayer(Character* p){
        player = p;
    }
    Character* getPlayer(){
        return player;
    }

    void setEnemy(Character* e) {
        enemy = e;
    }

    Character* getEnemy() {
        return enemy;
    }

    static GameData* getInstance() {
        if(_instance == 0){
            _instance = new GameData();
        }
        return _instance;
    }

    void setDialogWindow(DialogWindow* dialogWindow) {
        this->dialogWindow = dialogWindow;
    }

    DialogWindow* getDialogWindow() const {
        return dialogWindow;
    }

private:
    Character * player;
    Character * enemy;

    static GameData* _instance;

    DialogWindow* dialogWindow;
};

#endif // GAMEDATA_H
