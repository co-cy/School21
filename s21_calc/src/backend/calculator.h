//
// Created by Nana Daughterless on 6/27/22. Created
//

#ifndef S21_CALC_S21_CALC_H
#define S21_CALC_S21_CALC_H


#ifdef __cplusplus
extern "C" {
#endif


#include <string.h>


#include "structs/operators/operators.h"
#include "structs/ld_stack/ld_stack.h"
#include "structs/lexeme/lexem.h"
#include "structs/lex_stack/lex_stack.h"

typedef struct s_deposit {
    double tax;
    double contribution;
} t_deposit;

int word_to_polish(char *word, t_stack **polish, t_stack **operators);

t_stack *string_to_polish(char *string);

int calc(char *string, long double x, long double *result);
double credit_calc_annuity(double loan_amount, int period, double percent);
double credit_calc_differentiate(double loan_amount, int period, int cur_period, double percent);
t_deposit deposit_calc(double deposit_amount, int period, double percent, double tax_percent, int pay_period, int capitalize, char* list_add, char* list_pop, int* error_code);

#ifdef __cplusplus
}
#endif


#endif //S21_CALC_S21_CALC_H

