//
// Created by Nana Daughterless on 6/28/22.
//

#include "comparison.h"

int string_is_command(char *string) {
  /// Checks whether the string is an command
  int is = 0;

  for (t_operator *cur_operator = get_list_operators();
       !is && cur_operator->short_name; cur_operator++) {
    if (!strcmp(string, cur_operator->long_name)) is = 1;
  }

  return is;
}
