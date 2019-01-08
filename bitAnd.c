#include <stdio.h>
#define bitAnd(x,y) (~(~x|~y))
void main(int argc, char **argv){
    bitAnd(3,6);
    return;
}
