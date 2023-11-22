#pragma once
#include <memory>
#include <string>
#include <utility>
#include <vector>

class Disjunction_subets
{
  private:
    std::string name;
    int index;
    static int current_index;
    std::vector<std::shared_ptr<Disjunction_subets>> elements;
    std::weak_ptr<Disjunction_subets> parent;

  public:
    Disjunction_subets(std::string name);

    static void make_union(std::shared_ptr<Disjunction_subets> name_1, std::shared_ptr<Disjunction_subets> name_2);

    int find_in_which_Set();
};
