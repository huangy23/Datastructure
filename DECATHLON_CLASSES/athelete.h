#include <iostream>

#include <vector>

class Player
{
public:
    Player();
    Player(std::string aFirstName, std::string aLastName, std::string aCountry);
    //ACCESSORS
    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getCountry() const;
    float get100_METERS() const;
    float getLONG_JUMP() const;
    float getSHOT_PUT() const;
    float getHIGH_JUMP() const;
    float get400_METERS() const;
    float get110_METERS_HURDLES() const;
    float getDISCUS_THROW() const;
    float getPOLE_VAULT() const;
    float getJAVELIN_THROW() const;
    std::string get1500_METERS() const;

    int get100_METERS_points() const;
    int getLONG_JUMP_points() const;
    int getSHOT_PUT_points() const;
    int getHIGH_JUMP_points() const;
    int get400_METERS_points() const;
    int get110_METERS_HURDLES_points() const;
    int getDISCUS_THROW_points() const;
    int getPOLE_VAULT_points() const;
    int getJAVELIN_THROW_points() const;
    int get1500_METERS_points() const;
    int getTotal_points() const;

    //MODIFIERS
    void addEvent(std::string e, float score);
    void setFirstName(std::string s);
    void setLastName(std::string s);
    void setCountry(std::string s);
    void set1500_METERS(std::string s);

private:
    std::string first_name;
    std::string last_name;
    std::string country;

    float one_hundred_meters;
    float long_jump;
    float shot_up;
    float high_jump;
    float four_hundred_meters;
    float meters_hurdles;
    float discus_throw;
    float pole_vault;
    float javelin_throw;
    std::string long_meters;

    int one_hundred_meters_points;
    int long_jump_points;
    int shot_up_points;
    int high_jump_points;
    int four_hundred_meters_points;
    int meters_hurdles_points;
    int discus_throw_points;
    int pole_vault_points;
    int javelin_throw_points;
    int long_meters_points;

    int total_points;
};

bool sort_by_points(const Player& a, const Player& b);
bool sort_by_country_lastname(const Player& a, const Player& b);
bool sort_by_100m(const Player& a,const Player& b);