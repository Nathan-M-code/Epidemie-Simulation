#include "utile.h"

std::string intToString(int i) {
     std::ostringstream oss;
     oss << i;
     return oss.str();
}

// On suppose a<b
int rand_a_b(int a,int b){ //a inclu et b exclu
    return rand()%(b-a)+a;
}

std::string const BoolToString(bool b)
{
  return b ? "true" : "false";
}

float distance(sf::Vector2f &pos1, sf::Vector2f &pos2){
    return sqrt((pos2.x-pos1.x)*(pos2.x-pos1.x)+(pos2.y-pos1.y)*(pos2.y-pos1.y));
}
