#include "tanktrouble.hpp"
#include <cstdio>
Bullet::Bullet(double Xpos,double Ypos,double Dirx,double Diry,int Color):Object(Xpos,Ypos),Team(Color),maxage(20),size(0.05){
    dirx=Dirx;
    diry=Diry;
    age=0;
    Game::bulletcnt[Color]++;
    speed=1.0/20;//每秒移动一个单位
    fprintf(stderr,"bulletgen\n");
}
void Bullet::destroy(){
    for (auto iter=Game::bullets.begin();iter!=Game::bullets.end();iter++){
        if (*iter==this){
            Game::bullets.erase(iter);
            break;
        }
    }
    delete this;
    return;
}
void Bullet::move(){
    xpos+=speed*dirx;
    ypos+=speed*diry;
    if (++age==maxage){
        //子弹消失
        destroy();
        return;
    }
    bool crashx=0,crashy=0;
    for (auto ptr:Game::walls){
        if (ptr->direction){//竖着的
            if (ypos>=ptr->ypos && ypos<=ptr->ypos+1 && xpos>=ptr->xpos-size && xpos<=ptr->xpos+size){//撞墙
                crashx=1;
                fprintf(stderr,"bulletbounce\n");
            }
        }
        else{//横着的
            if (xpos>=ptr->xpos && xpos<=ptr->xpos+1 && ypos>=ptr->ypos-size && ypos<=ptr->ypos+size){//撞墙
                crashy=1;
                fprintf(stderr,"bulletbounce\n");
            }
        }
    }
    if (crashx||crashy){
        xpos-=speed*dirx;
        ypos-=speed*diry;
        if (crashx) dirx=-dirx;
        if (crashy) diry=-diry;
    }
}
Bullet::~Bullet(){
    Game::bulletcnt[color]--;
    fprintf(stderr,"bulletvanish\n");
}
