//
//  Battle.hpp
//  Game
//
//  Created by Ryoma Usui on 2020/07/31.
//

#ifndef Battle_hpp
#define Battle_hpp
# pragma once
# include "Common.hpp"

#include <stdio.h>

class Battle : public MyApp::Scene
{
public:
    Battle(const InitData& init);
    
    void update() override;
    
    void draw() const override;
    
    
    void stageUpdate();
    void stageDraw() const;
};

#endif /* Battle_hpp */
