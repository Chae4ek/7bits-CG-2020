#pragma once

class Player
{
private:
    int pos_x;
    int pos_y;
public:
    Player();
    
    int GetPosX();
    int GetPosY();
    
    void Left();
    void Right();
    void Up();
    void Down();
};