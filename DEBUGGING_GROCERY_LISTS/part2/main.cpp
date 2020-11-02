//
// PROVIDED CODE FOR HOMEWORK 4: GROCERY LISTS
//
// You may use none, a little, or all of this, as you choose, but we
// strongly urge you to examine it carefully.  You may modify this
// code as you wish to complete the assignment.
//

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <fstream>

#include "recipe.h"
#include "kitchen.h"

// Helper functions
void readRecipe(std::istream &istr, std::ostream &ostr, std::list<Recipe> &recipes);
void addIngredients(std::istream &istr, std::ostream &ostr, Kitchen &kitchen);
void printRecipe(std::istream &istr, std::ostream &ostr, const std::list<Recipe> &recipes);
void makeRecipe(std::istream &istr, std::ostream &ostr, const std::list<Recipe> &recipes, Kitchen &kitchen);

// The main loop parses opens the files for I/O & parses the input
int main(int argc, char *argv[])
{

  // Check the number of arguments.
  if (argc != 3)
  {
    std::cerr << "Usage: " << argv[0] << " in-file out-file\n";
    return 1;
  }
  // Open and test the input file.
  std::ifstream istr(argv[1]);
  if (!istr)
  {
    std::cerr << "Could not open " << argv[1] << " to read\n";
    return 1;
  }
  // Open and test the output file.
  std::ofstream ostr(argv[2]);
  if (!ostr)
  {
    std::cerr << "Could not open " << argv[2] << " to write\n";
    return 1;
  }

  // the kitchen & recipe list
  Kitchen kitchen;
  std::list<Recipe> recipes;

  // some variables to help with parsing
  char c;
  while (istr >> c)
  {
    if (c == 'r')
    {
      // READ A NEW RECIPE
      readRecipe(istr, ostr, recipes);
    }
    else if (c == 'a')
    {
      // ADD INGREDIENTS TO THE KITCHEN
      addIngredients(istr, ostr, kitchen);
    }
    else if (c == 'p')
    {
      // PRINT A PARTICULAR RECIPE
      printRecipe(istr, ostr, recipes);
    }
    else if (c == 'm')
    {
      // MAKE SOME FOOD
      makeRecipe(istr, ostr, recipes, kitchen);
    }
    else if (c == 'k')
    {
      // PRINT THE CONTENTS OF THE KITCHEN
      kitchen.printIngredients(ostr);
    }
    else
    {
      std::cerr << "unknown character: " << c << std::endl;
      exit(0);
    }
  }
}

void readRecipe(std::istream &istr, std::ostream &ostr, std::list<Recipe> &recipes)
{
  int units;
  std::string name, name2;
  istr >> name;
  // build the new recipe
  Recipe r(name);
  while (1)
  {
    istr >> units;
    if (units == 0)
      break;
    assert(units > 0);
    istr >> name2;
    for (std::list<Recipe>::const_iterator it = recipes.begin(); it != recipes.end(); it++)
    {
      if ((*it).getRecName() == name)
      {
        ostr << "Recipe for " << name << " already exists" << endl;
      }
    }

    r.addIngredient(name2, units);
  }

  // add it to the list
  recipes.push_back(r);
  ostr << "Recipe for " << name << " added" << std::endl;
}

void addIngredients(std::istream &istr, std::ostream &ostr, Kitchen &kitchen)
{
  int units;
  std::string name;
  int count = 0;
  while (1)
  {
    istr >> units;
    if (units == 0)
      break;
    assert(units > 0);
    istr >> name;
    // add the ingredients to the kitchen
    kitchen.addIngredient(name, units);
    count++;
  }

  ostr << count << " ingredients added to kitchen" << std::endl;
}

void printRecipe(std::istream &istr, std::ostream &ostr, const std::list<Recipe> &recipes)
{
  std::string name;
  istr >> name;
  for (std::list<Recipe>::const_iterator it = recipes.begin(); it != recipes.end(); it++)
  {
    if ((*it).getRecName() == name)
    {
      (*it).printRecipe(ostr);
      return;
    }
  }

  ostr << "No recipe for " << name << endl;
}

bool sort_for_list_ing(const Ingredient &a, const Ingredient &b)
{
  return (a.getIngName() < b.getIngName());
}

void makeRecipe(std::istream &istr, std::ostream &ostr, const std::list<Recipe> &recipes, Kitchen &kitchen)
{
  std::string name;
  istr >> name;
  list<Ingredient> ing_avaliable = kitchen.get_inginkitchen();
  list<Ingredient> ing_needed_for_recipe;
  for (std::list<Recipe>::const_iterator itr = recipes.begin(); itr != recipes.end(); itr++)
  {
    if ((*itr).getRecName() == name)
    {
      ing_needed_for_recipe = (*itr).get_ing_for_recipe();
      break;
    }
    else
    {
      ostr << "Don't know how to make " << name << endl;
    }
  }

  ing_needed_for_recipe.sort(sort_for_list_ing);
  ing_avaliable.sort(sort_for_list_ing);
  bool made = true;
  list<Ingredient> still_need;
  std::list<Ingredient>::iterator it_rec = ing_needed_for_recipe.begin(); //2a 3b
  std::list<Ingredient>::iterator it_ava = ing_avaliable.begin();         //2b
  int can_make = 1;
  for (; (it_ava != ing_avaliable.end()) && (it_rec != ing_needed_for_recipe.end()); it_ava++, it_rec++)
  {
    if ((*it_ava).getIngName() == (*it_rec).getIngName())
    {
      if ((*it_ava).getIngUnits() < (*it_rec).getIngUnits())
      {
        can_make = 0;
        break;
      }
    }
  }
  
  


  if(can_make == 0){
 std::list<Ingredient>::iterator it_rec = ing_needed_for_recipe.begin(); //2a 3b
  std::list<Ingredient>::iterator it_ava = ing_avaliable.begin();         //2b
  for (; (it_ava != ing_avaliable.end()) && (it_rec != ing_needed_for_recipe.end()); it_ava++, it_rec++)
  {
    if (((*it_ava).getIngName() == (*it_rec).getIngName())&&(((*it_rec).getIngUnits() - (*it_ava).getIngUnits())>0))
    {
      
        int diff = (*it_rec).getIngUnits() - (*it_ava).getIngUnits();
        ostr << "Cannot make " << name << ", need to buy:" << endl;

        ostr << "  " << diff << " unit of " << (*it_ava).getIngName() << endl;
        made = false;
      
    }
  }}else{
    //can make is true
    std::list<Ingredient>::iterator it_rec = ing_needed_for_recipe.begin(); //2a 3b
  std::list<Ingredient>::iterator it_ava = ing_avaliable.begin();         //2b
    for (; (it_ava != ing_avaliable.end()) && (it_rec != ing_needed_for_recipe.end()); it_ava++, it_rec++)
  {
    if ((*it_ava).getIngName() == (*it_rec).getIngName())
    {
      if ((*it_ava).getIngUnits() >= (*it_rec).getIngUnits())
      {
        int left = (*it_ava).getIngUnits() - (*it_rec).getIngUnits();
        kitchen.delete_ing((*it_ava).getIngName());
        Ingredient temp((*it_ava).getIngName(), left);
        kitchen.ingredients_list.push_back(temp);
      }}}
  }

  if (made == true)
  {
    ostr << "Made " << name << endl;
  }
}
