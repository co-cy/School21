//
// Created by Nana Daughterless on 6/29/22.
//

#include "calculator.h"
#include "math.h"


int calc(char *string, long double x, long double *result) {
    *result = 0.0;

    char str[256];
    sprintf(str, "echo \"%s\" > ~/a", string);
    system(str);

    t_stack *polish = string_to_polish(string);

    int error_code = 0;
    t_ld_stack *numbers = NULL;
    if (polish) {
        polish = reverse_lex_stack(polish);

        // TODO: Move logic to another function
        while (polish) {
            if (polish->lexeme->type == type_lexeme_number) {
                long double value;
                if (!strcmp(polish->lexeme->string, "x"))
                    value = x;
                else
                    value = strtold(polish->lexeme->string, NULL);

                numbers = add_to_ld_stack(numbers, value);
            } else {
                error_code = numbers == NULL;
                if (!error_code) {
                    long double number1 = pop_ld_stack(&numbers);

                    if (!strcmp(polish->lexeme->string, "cos")) {
                        numbers = add_to_ld_stack(numbers, cosl(number1));
                    } elif (!strcmp(polish->lexeme->string, "sin")) {
                        numbers = add_to_ld_stack(numbers, sinl(number1));
                    } elif (!strcmp(polish->lexeme->string, "tan")) {
                        numbers = add_to_ld_stack(numbers, tanl(number1));
                    } elif (!strcmp(polish->lexeme->string, "acos")) {
                        numbers = add_to_ld_stack(numbers, acosl(number1));
                    } elif (!strcmp(polish->lexeme->string, "asin")) {
                        numbers = add_to_ld_stack(numbers, asinl(number1));
                    } elif (!strcmp(polish->lexeme->string, "atan")) {
                        numbers = add_to_ld_stack(numbers, atanl(number1));
                    } elif (!strcmp(polish->lexeme->string, "sqrt")) {
                        numbers = add_to_ld_stack(numbers, sqrtl(number1));
                    } elif (!strcmp(polish->lexeme->string, "ln")) {
                        numbers = add_to_ld_stack(numbers, logl(number1));
                    } elif (!strcmp(polish->lexeme->string, "log")) {
                        numbers = add_to_ld_stack(numbers, log10l(number1));
                    } else {
                        error_code = numbers == NULL;
                        if (!error_code) {
                            long double number2 = pop_ld_stack(&numbers);

                            if (!strcmp(polish->lexeme->string, "+")) {
                                numbers = add_to_ld_stack(numbers, number2 + number1);
                            } elif (!strcmp(polish->lexeme->string, "-")) {
                                numbers = add_to_ld_stack(numbers, number2 - number1);
                            } elif (!strcmp(polish->lexeme->string, "*")) {
                                numbers = add_to_ld_stack(numbers, number2 * number1);
                            } elif (!strcmp(polish->lexeme->string, "/")) {
                                numbers = add_to_ld_stack(numbers, number2 / number1);
                            } elif (!strcmp(polish->lexeme->string, "mod")) {
                                numbers = add_to_ld_stack(numbers, fmodl(number2, number1));
                            } elif (!strcmp(polish->lexeme->string, "^")) {
                                numbers = add_to_ld_stack(numbers, powl(number2, number1));
                            } else {
                                error_code = 1;
                            }
                        }
                    }
                }

                if (error_code)
                    break;
            }

            dump_lex_stack(&polish);
        }
    }

    if (!error_code) {
        if (numbers) {
            *result = pop_ld_stack(&numbers);
        } else {
            error_code = 1;
        }

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