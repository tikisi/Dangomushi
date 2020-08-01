//
//  Battle.cpp
//  Game
//
//  Created by Ryoma Usui on 2020/07/31.
//

#include "Battle.hpp"

Battle::Battle(const InitData& init)
: IScene(init) {
    
}

void Battle::update()
{
    stageUpdate();
}

void Battle::draw() const
{
    stageDraw();
}


void Battle::stageUpdate(){
    
}

void Battle::stageDraw() const {
    Rect(0,500,800,100).draw(Palette::Bisque);
}
