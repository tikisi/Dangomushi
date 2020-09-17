//
//  Battle.hpp
//  Game
//
//  Created by Ryoma Usui on 2020/07/31.
//

#ifndef Battle_hpp
#define Battle_hpp
# include "Common.hpp"
# include "Player.hpp"
# include "Boss.hpp"
# include "Stage.hpp"
# include "Bullet.hpp"

#define STAGE_NUM 4
class BattleScene : public MyApp::Scene
{
private:
    Stage stage[STAGE_NUM];
    Bullet bullets[30];
    Battle::Player player;
    Boss boss;
public:
    BattleScene(const InitData& init);
    
    void update() override;
    
    void draw() const override;
    
    void stageInit();
    void stageUpdate();
    void stageDraw() const;
    
    void playerInit();
    void playerUpdate();
    void playerDraw() const;
    
    void bossInit();
    void bossUpdate();
    void bossDraw() const;
    
    void shotInit();
    void shotUpdate();
    void shotDraw() const;
    
    
    void homing();
    void bulletInit(int num, double speed, double spiral);
};

#endif /* Battle_hpp */
