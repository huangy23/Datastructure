#include "athelete.h"
#include <iostream>
#include <vector>
#include <cstdlib> //convert str to int or float
#include <string>
#include <cmath> //using pow

using namespace std;

Player::Player()
{
    first_name = "hanzo";
    last_name = "huang";
    country = "AAA";
    one_hundred_meters = 0;
    long_jump = 0;
    shot_up = 0;
    high_jump = 0;
    four_hundred_meters = 0;
    meters_hurdles = 0;
    discus_throw = 0;
    pole_vault = 0;
    javelin_throw = 0;

    one_hundred_meters_points = 0;
    long_jump_points = 0;
    shot_up_points = 0;
    high_jump_points = 0;
    four_hundred_meters_points = 0;
    meters_hurdles_points = 0;
    discus_throw_points = 0;
    pole_vault_points = 0;
    javelin_throw_points = 0;
    long_meters_points = 0;

    total_points = 0;
}

Player::Player(std::string aFirstName, std::string aLastName, std::string aCountry)
{
    first_name = aFirstName;
    last_name = aLastName;
    country = aCountry;
}

//accessors
std::string Player::getFirstName() const { return first_name; }
std::string Player::getLastName() const { return last_name; }
std::string Player::getCountry() const { return country; }

float Player::get100_METERS() const { return one_hundred_meters; }
float Player::getLONG_JUMP() const { return long_jump; }
float Player::getSHOT_PUT() const { return shot_up; }
float Player::getHIGH_JUMP() const { return high_jump; }
float Player::get400_METERS() const { return four_hundred_meters; }
float Player::get110_METERS_HURDLES() const { return meters_hurdles;}
float Player::getDISCUS_THROW() const { return discus_throw; }
float Player::getPOLE_VAULT() const { return pole_vault; }
float Player::getJAVELIN_THROW() const { return javelin_throw; }
std::string Player::get1500_METERS() const { return long_meters; }

int Player::get100_METERS_points() const { return one_hundred_meters_points; }
int Player::getLONG_JUMP_points() const { return long_jump_points; }
int Player::getSHOT_PUT_points() const { return shot_up_points; }
int Player::getHIGH_JUMP_points() const { return high_jump_points; }
int Player::get400_METERS_points() const { return four_hundred_meters_points; }
int Player::get110_METERS_HURDLES_points() const { return meters_hurdles_points; }
int Player::getDISCUS_THROW_points() const { return discus_throw_points; }
int Player::getPOLE_VAULT_points() const { return pole_vault_points; }
int Player::getJAVELIN_THROW_points() const { return javelin_throw_points; }
int Player::get1500_METERS_points() const { return long_meters_points; }
int Player::getTotal_points() const { return total_points; }

//modifiers
void Player::addEvent(std::string e, float score)
{
    if (e == "POLE_VAULT")
    {
        pole_vault = score;
        pole_vault_points = (int)(0.2797 * (pow(((score * 100) - 100), 1.35)));
        total_points += pole_vault_points;
    }
    if (e == "JAVELIN_THROW")
    {
        javelin_throw = score;
        javelin_throw_points = (int)(10.14 * (pow((score - 7), 1.08)));
        total_points += javelin_throw_points;
    }
    if (e == "SHOT_PUT")
    {
        shot_up = score;
        shot_up_points = (int)(51.39 * (pow((score - 1.5), 1.05)));
        total_points += shot_up_points;
    }
    if (e == "HIGH_JUMP")
    {
        high_jump = score;
        high_jump_points = (int)(.8465 * (pow(((score * 100) - 75), 1.42)));
        total_points += high_jump_points;
    }
    if (e == "400_METERS")
    {
        four_hundred_meters = score;
        four_hundred_meters_points = (int)(1.53775 * (pow((82 - score), 1.81)));
        total_points += four_hundred_meters_points;
    }
    if (e == "110_METERS_HURDLES")
    {
        meters_hurdles = score;
        meters_hurdles_points = (int)(5.74352 * (pow((28.5 - score), 1.92)));
        total_points += meters_hurdles_points;
    }
    if (e == "DISCUS_THROW")
    {
        discus_throw = score;
        discus_throw_points = (int)(12.91 * (pow((score - 4), 1.1)));
        total_points += discus_throw_points;
    }
    if (e == "100_METERS")
    {
        one_hundred_meters = score;
        one_hundred_meters_points = (int)(25.4347 * (pow((18 - score), 1.81)));
        total_points += one_hundred_meters_points;
    }
    if (e == "LONG_JUMP")
    {
        long_jump = score;
        long_jump_points = (int)(.14354 * (pow(((score * 100) - 220), 1.4)));
        total_points += long_jump_points;
    }
    if (e == "1500_METERS")
    {
        long_meters_points = (int)(0.03768 * (pow((480 - score), 1.85)));
        total_points += long_meters_points;
    }
}

void Player::setFirstName(std::string s) { first_name = s; }
void Player::setLastName(std::string s) { last_name = s; }
void Player::setCountry(std::string s) { country = s; }
void Player::set1500_METERS(std::string s) { long_meters = s; }

bool sort_by_points(const Player& a, const Player& b){
	return a.getTotal_points() > b.getTotal_points();
}

bool sort_by_country_lastname(const Player& a, const Player& b){
    if (a.getCountry() == b.getCountry())
    {
        return (a.getLastName() < b.getLastName());
    }
    else
    {
        return (a.getCountry() < b.getCountry());
    }   
}

bool sort_by_100m(const Player& a,const Player& b){
    return a.get100_METERS_points() > a.get100_METERS_points();
}