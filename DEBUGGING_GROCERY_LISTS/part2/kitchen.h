#ifndef kitchen_h_
#define kitchen_h_

#include <iostream>
#include "ingredient.h"
#include <vector>

#include <list> //need list to store ingredients

using namespace std;

class Kitchen
{
public:
    //constructor
    Kitchen();
    Kitchen(string aName);

    list<Ingredient> get_inginkitchen() const
    {
        return ingredients_list;
    }

    //modifier
    void addIngredient(string igdt, int number);

    void printIngredients(ostream &ostr) const;

    void delete_ing(string name)
    {
        for (std::list<Ingredient>::iterator i = ingredients_list.begin(); i != ingredients_list.end(); i++)
        {
            if ((*i).getIngName() == name)
            {
                i = ingredients_list.erase(i);
            }
        }
    }


    string name;
    list<Ingredient> ingredients_list;
};

Kitchen::Kitchen()
{
    name = "default_kitchen";
}

Kitchen::Kitchen(string aName)
{
    name = aName;
}

void Kitchen::addIngredient(string igdt, int number)
{
    if (ingredients_list.size() > 0)
    {
        //int count = 0 ;
        for (list<Ingredient>::iterator itr = ingredients_list.begin(); itr != ingredients_list.end(); itr++)
        {
            if ((*itr).getIngName() == igdt)
            {
                (*itr).add(number);
                break;
            }
            else
            {
                Ingredient temp(igdt, number);
                ingredients_list.push_back(temp);
                break;
            }
        }
    }
    else
    {
        Ingredient temp(igdt, number);
        ingredients_list.push_back(temp);
    }
}

bool sort_ing(const Ingredient &a, const Ingredient &b)
{
    return (a.getIngUnits() < b.getIngUnits());
}

void Kitchen::printIngredients(ostream &ostr) const
{
    list<Ingredient> temp = ingredients_list;
    temp.sort(sort_ing);
    ostr << "In the kitchen:" << endl;
    for (list<Ingredient>::const_iterator itr = temp.begin(); itr != temp.end(); itr++)
    {
        int n = (*itr).getIngUnits();
        if (n < 2)
        {
            ostr << "  " << n << " unit of " << (*itr).getIngName() << endl;
        }
        else
        {
            ostr << "  " << n << " units of " << (*itr).getIngName() << endl;
        }
    }
}

#endif