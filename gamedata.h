// Test ***
// gamedata.h

#ifndef GAMEDATA_H
#define GAMEDATA_H

#include "dialogtree.h"
#include "character.h"

class GameData
{
public:
    static GameData* getInstance();

    Character* getPlayer() const;
    Character* getEnemy() const;

    AttackResult getPlayerAttackResult() const;
    AttackResult getEnemyAttackResult() const;

    void setPlayer(Character* player);
    void setEnemy(Character* enemy);

    void setPlayerAttackResult(const AttackResult& result);
    void setEnemyAttackResult(const AttackResult& result);

    // Test ***
    void setDialogWindow(DialogWindow* dialogWindow) {
        this->dialogWindow = dialogWindow;
    }

    DialogWindow* getDialogWindow() const {
        return dialogWindow;
    }

private:
    GameData();

    Character* player;
    Character* enemy;

    AttackResult playerAttackResult;
    AttackResult enemyAttackResult;

    // Test ***
    DialogWindow* dialogWindow;
};

#endif // GAMEDATA_H


// ##########################

//#ifndef GAMEDATA_H
//#define GAMEDATA_H

//#include "character.h"
//#include "dialogtree.h"

//class GameData {

//private:
//    GameData() {}

//public:
//    void setPlayer(Character* p){
//        player = p;
//    }
//    Character* getPlayer(){
//        return player;
//    }

//    void setEnemy(Character* e) {
//        enemy = e;
//    }

//    Character* getEnemy() {
//        return enemy;
//    }

//    static GameData* getInstance() {
//        if(_instance == 0){
//            _instance = new GameData();
//        }
//        return _instance;
//    }

//    void setDialogWindow(DialogWindow* dialogWindow) {
//        this->dialogWindow = dialogWindow;
//    }

//    DialogWindow* getDialogWindow() const {
//        return dialogWindow;
//    }

//private:
//    Character * player;
//    Character * enemy;

//    static GameData* _instance;

//    DialogWindow* dialogWindow;
//};

//#endif // GAMEDATA_H
