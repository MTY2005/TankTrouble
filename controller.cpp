#include "tanktrouble.hpp"
Controller::Controller(char l,char r,char f,char b,char s){
    left=l;
    right=r;
    forward=f;
    backward=b;
    shoot=s;
}
std::array<bool,5> Controller::status(){
    std::array<bool,5> ret={0,0,0,0,0};
    #define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
    if (KEY_DOWN(left)&&!KEY_DOWN(right)) ret[0]=1;
    if (KEY_DOWN(right)&&!KEY_DOWN(left)) ret[1]=1;
    if (KEY_DOWN(forward)&&!KEY_DOWN(backward)&&!KEY_DOWN(left)&&!KEY_DOWN(right)) ret[2]=1;
    if (KEY_DOWN(backward)&&!KEY_DOWN(forward)&&!KEY_DOWN(left)&&!KEY_DOWN(right)) ret[3]=1;
    if (KEY_DOWN(shoot)) ret[4]=1;
    #undef KEY_DOWN
    return ret;
}
