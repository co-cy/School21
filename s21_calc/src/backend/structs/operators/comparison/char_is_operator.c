//
// Created by Nana Daughterless on 6/28/22.
//

#include "comparison.h"

int char_is_operator(char symbol) {
  /// Check whether the symbol is an operator
  int is = 0;

  for (t_operator *cur_operator = get_list_operators();
       !is && cur_operator->short_name; cur_operator++)
    if (symbol == cur_operator->short_name) is = 1;

  return is;
}
