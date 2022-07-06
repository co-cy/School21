//
// Created by Nana Daughterless on 6/29/22.
//

#include "s21_calc.h"
#include "math.h"


int calc(char *string, long double *result) {
    printf("STRING: _%s_\n", string);
    *result = 0.0;
    t_stack *polish = string_to_polish(string);

    int status = 0;
    t_ld_stack *numbers = NULL;
    if (polish) {
        polish = reverse_stack(polish);

        while (polish) {
            if (polish->lexeme->type == type_lexeme_number) {
                long double value = strtold(polish->lexeme->string, NULL);
                numbers = add_to_ld_stack(numbers, value);
            } else {
                status = numbers == NULL;
                if (!status) {
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
                        status = numbers == NULL;
                        if (!status) {
                            long double number2 = pop_ld_stack(&numbers);

                            if (!strcmp(polish->lexeme->string, "+")) {
                                numbers = add_to_ld_stack(numbers, number1 + number2);
                            } elif (!strcmp(polish->lexeme->string, "-")) {
                                numbers = add_to_ld_stack(numbers, number1 - number2);
                            } elif (!strcmp(polish->lexeme->string, "*")) {
                                numbers = add_to_ld_stack(numbers, number1 * number2);
                            } elif (!strcmp(polish->lexeme->string, "/")) {
                                numbers = add_to_ld_stack(numbers, number1 / number2);
                            } elif (!strcmp(polish->lexeme->string, "mod")) {
                                numbers = add_to_ld_stack(numbers, fmodl(number1, number2));
                            } elif (!strcmp(polish->lexeme->string, "^")) {
                                numbers = add_to_ld_stack(numbers, powl(number1, number2));
                            } else {
                                status = 1;
                            }
                        }
                    }
                }

                if (status) {
                    print_stack(polish);
                    break;
                }

            }

            dump_stack(&polish);
        }
    }

    if (!status) {
        if (numbers) {
            *result = pop_ld_stack(&numbers);
        } else {
            status = 1;
        }

    }

    if (numbers) {
        free_ld_stack(&numbers);
        status = 1;
    }

    if (polish) {
        free_stack(&polish);
        status = 1;
    }

    return status;
}