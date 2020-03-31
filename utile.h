#ifndef UTILE_H_INCLUDED
#define UTILE_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iostream>
#include <string>
#include <cmath>

std::string intToString(int i);
int rand_a_b(int a,int b);
std::string const BoolToString(bool b);
float distance(sf::Vector2f &pos1, sf::Vector2f &pos2);



#endif // UTILE_H_INCLUDED
