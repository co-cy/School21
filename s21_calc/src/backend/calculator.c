//
// Created by Nana Daughterless on 6/29/22.
//

#include "calculator.h"

#include "math.h"

int cycle(t_stack **polish, t_ld_stack **numbers, long double x) {
  int error_code = 0;

  while (*polish) {
    if ((*polish)->lexeme->type == type_lexeme_number) {
      long double value;
      if (!strcmp((*polish)->lexeme->string, "x"))
        value = x;
      else
        value = strtold((*polish)->lexeme->string, NULL);

      *numbers = add_to_ld_stack(*numbers, value);
    } else {
      error_code = *numbers == NULL;
      if (!error_code) {
        long double number1 = pop_ld_stack(numbers);

        if (!strcmp((*polish)->lexeme->string, "cos")) {
          *numbers = add_to_ld_stack(*numbers, cosl(number1));
        }
        elif (!strcmp((*polish)->lexeme->string, "sin")) {
          *numbers = add_to_ld_stack(*numbers, sinl(number1));
        }
        elif (!strcmp((*polish)->lexeme->string, "tan")) {
          *numbers = add_to_ld_stack(*numbers, tanl(number1));
        }
        elif (!strcmp((*polish)->lexeme->string, "acos")) {
          *numbers = add_to_ld_stack(*numbers, acosl(number1));
        }
        elif (!strcmp((*polish)->lexeme->string, "asin")) {
          *numbers = add_to_ld_stack(*numbers, asinl(number1));
        }
        elif (!strcmp((*polish)->lexeme->string, "atan")) {
          *numbers = add_to_ld_stack(*numbers, atanl(number1));
        }
        elif (!strcmp((*polish)->lexeme->string, "sqrt")) {
          *numbers = add_to_ld_stack(*numbers, sqrtl(number1));
        }
        elif (!strcmp((*polish)->lexeme->string, "ln")) {
          *numbers = add_to_ld_stack(*numbers, logl(number1));
        }
        elif (!strcmp((*polish)->lexeme->string, "log")) {
          *numbers = add_to_ld_stack(*numbers, log10l(number1));
        }
        else {
          error_code = *numbers == NULL;
          if (!error_code) {
            long double number2 = pop_ld_stack(numbers);

            if (!strcmp((*polish)->lexeme->string, "+")) {
              *numbers = add_to_ld_stack(*numbers, number2 + number1);
            }
            elif (!strcmp((*polish)->lexeme->string, "-")) {
              *numbers = add_to_ld_stack(*numbers, number2 - number1);
            }
            elif (!strcmp((*polish)->lexeme->string, "*")) {
              *numbers = add_to_ld_stack(*numbers, number2 * number1);
            }
            elif (!strcmp((*polish)->lexeme->string, "/")) {
              *numbers = add_to_ld_stack(*numbers, number2 / number1);
            }
            elif (!strcmp((*polish)->lexeme->string, "mod")) {
              *numbers = add_to_ld_stack(*numbers, fmodl(number2, number1));
            }
            elif (!strcmp((*polish)->lexeme->string, "^")) {
              *numbers = add_to_ld_stack(*numbers, powl(number2, number1));
            }
            else {
              error_code = 1;
            }
          }
        }
      }

      if (error_code) break;
    }

    dump_lex_stack(polish);
  }

  return error_code;
}

int calc(char *string, long double x, long double *result) {
  *result = 0.0;

  t_stack *polish = string_to_polish(string);

  int error_code = 0;
  t_ld_stack *numbers = NULL;
  if (polish) {
    polish = reverse_lex_stack(polish);

    error_code = cycle(&polish, &numbers, x);
  }

  if (!error_code) {
    if (numbers)
      *result = pop_ld_stack(&numbers);
    else
      error_code = 1;
  }

  if (numbers) {
    free_ld_stack(&numbers);
    error_code = 1;
  }

  if (polish) {
    free_lex_stack(&polish);
    error_code = 1;
  }

  return error_code;
}

double credit_calc_annuity(double loan_amount, int period, double percent) {
  percent = percent / 1200;  // convert % -> value (/ 100) and convert year
                             // percent -> month percent (/ 12)

  return loan_amount * percent * powl((1 + percent), period) /
         (powl((1 + percent), period) - 1);
}

double credit_calc_differentiate(double loan_amount, int period, int cur_period,
                                 double percent) {
  percent = percent / 1200;  // convert % -> value (/ 100) and convert year
                             // percent -> month percent (/ 12)

  return loan_amount / period +
         percent * (loan_amount - (loan_amount * (cur_period - 1) / period));
}

double a(char **list_add, int cur_time, int *error_code) {
  char *pointer1 = NULL;
  char *pointer2 = NULL;

  double result = 0;

  int period = strtol(*list_add, &pointer1, 10);
  if (**list_add && *list_add == pointer1) {
    *error_code = 1;
  } else if (period >= cur_time) {
    double value = strtold(pointer1, &pointer2);
    if (*pointer1 && pointer1 == pointer2) {
      *error_code = 1;
    } else {
      *list_add = pointer2;
      result = value;
    }
  }

  return result;
}

t_deposit deposit_calc(double deposit_amount, int period, double percent,
                       double tax_percent, int pay_period, int capitalize,
                       char *list_add, char *list_pop, int *error_code) {
  tax_percent = tax_percent * pay_period / 1200;
  percent = percent * pay_period / 1200;
  *error_code = 0;

  double added = 0;
  t_deposit result = {0, 0};
  for (int i = pay_period; i <= period; i += pay_period) {
    double tmp = deposit_amount * percent;
    result.tax += tmp * (tax_percent);

    if (capitalize)
      deposit_amount += tmp * (1 - tax_percent);
    else
      added += tmp * (1 - tax_percent);

    double value = a(&list_add, i, error_code);
    if (!*error_code) {
      deposit_amount += value;

      value = a(&list_pop, i, error_code);
      if (!*error_code) deposit_amount -= value;
    }

    if (deposit_amount < 0) *error_code = 1;

    if (*error_code) break;
  }

  result.contribution = deposit_amount;
  if (!capitalize) result.contribution += added;

  return result;
}
