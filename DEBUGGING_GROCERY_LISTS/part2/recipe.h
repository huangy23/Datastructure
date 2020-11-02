#ifndef recipe_h_
#define recipe_h_

#include "ingredient.h"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <list>

using namespace std;

class Recipe
{
public:
    //constructor
    Recipe();
    Recipe(string aName);

    //accessors
    string getRecName() const;
    list<Ingredient> get_ing_for_recipe() const;

    //modifier
    void addIngredient(string ing, int number);
    void printRecipe(ostream &ostr) const;

private:
    string name;

    list<Ingredient> ing_needed;
};

Recipe::Recipe()
{
    name = "defaut";
}

Recipe::Recipe(string aName)
{
    name = aName;
}

string Recipe::getRecName() const
{
    return name;
}

list<Ingredient> Recipe::get_ing_for_recipe() const
{
    return ing_needed;
}

void Recipe::addIngredient(string ing, int number)
{
    if (ing_needed.size() > 0)
    {
        for (list<Ingredient>::iterator itr = ing_needed.begin(); itr != ing_needed.end(); itr++)
        {
            if ((*itr).getIngName() == ing)
            {
                (*itr).add(number);
                break;
            }
            else
            {
                Ingredient temp(ing, number);
                ing_needed.push_back(temp);
                break;
            }
        }
    }
    else
    {
        Ingredient temp(ing, number);
        ing_needed.push_back(temp);
    }
}

bool sort_by_ing(const Ingredient &a, const Ingredient &b)
{
    return (a.getIngUnits() < b.getIngUnits());
}

void Recipe::printRecipe(ostream &ostr) const
{
    list<Ingredient> temp = ing_needed;
    temp.sort(sort_by_ing);
    list<Ingredient>::iterator it;
    ostr << "To make " << name << ", mix together:" << endl;
    for (it = temp.begin(); it != temp.end(); it++)
    {
        int unit = (*it).getIngUnits();
        if (unit < 2)
        {
            ostr << "  " << unit << " unit of " << (*it).getIngName() << endl;
        }
        else
        {
            ostr << "  " << unit << " units of " << (*it).getIngName() << endl;
        }
    }
}

#endif