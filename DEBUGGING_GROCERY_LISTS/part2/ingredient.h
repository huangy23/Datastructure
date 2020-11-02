#ifndef ingredient_h_
#define ingredient_h_

using namespace std;

class Ingredient
{
public:
    //constructor
    Ingredient();
    Ingredient(string aName, int aUnit);

    //accessors
    string getIngName() const;
    int getIngUnits() const;

    //modifier
    void add(int number);
    void minus(int number);

private:
    string name;
    int unit;
};

Ingredient::Ingredient()
{
    name = "n";
    unit = 0;
}

Ingredient::Ingredient(string aName, int aUnit)
{
    name = aName;
    unit = aUnit;
}

string Ingredient::getIngName() const
{
    return name;
}

int Ingredient::getIngUnits() const
{
    return unit;
}

void Ingredient::add(int number)
{
    unit += number;
}

void Ingredient::minus(int number)
{
    unit = unit - number;
}

#endif