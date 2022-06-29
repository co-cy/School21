//
// Created by Nana Daughterless on 6/29/22.
//

#include "s21_calc.h"
#include "math.h"



int calc(char *string, long double *result) {
    *result = 0.0;
    t_stack *polish = string_to_polish(string);

    int status = 0;
    t_stack *numbers = NULL;
    if (polish) {
        polish = reverse_stack(polish);

        while (polish) {
            if (polish->lexeme->type == type_lexeme_number) {
                numbers = add_to_stack(numbers, create_lexeme(polish->lexeme->string, polish->lexeme->type));
            } else {
                t_lexeme *number_1 = pop_stack(&numbers);
                status = !number_1;

                if (!status) {
                    if (!strcmp(polish->lexeme->string, "cos")) {

                    } elif (!strcmp(polish->lexeme->string, "sin")) {

                    } elif (!strcmp(polish->lexeme->string, "tan")) {

                    } elif (!strcmp(polish->lexeme->string, "acos")) {

                    } elif (!strcmp(polish->lexeme->string, "asin")) {

                    } elif (!strcmp(polish->lexeme->string, "atan")) {

                    } elif (!strcmp(polish->lexeme->string, "sqrt")) {

                    } elif (!strcmp(polish->lexeme->string, "ln")) {

                    } elif (!strcmp(polish->lexeme->string, "log")) {
                    } else {
                        t_lexeme *number_2 = pop_stack(&numbers);
                        status = !number_2;

                        if (!strcmp(polish->lexeme->string, "+")) {

                        } elif (!strcmp(polish->lexeme->string, "-")) {

                        } elif (!strcmp(polish->lexeme->string, "*")) {

                        } elif (!strcmp(polish->lexeme->string, "/")) {

                        } elif (!strcmp(polish->lexeme->string, "mod")) {

                        } elif (!strcmp(polish->lexeme->string, "^")) {

                        } else {
                            status = 1;
                        }
                    }
                }

                if (status) {
                    break;
                }

                dump_stack(&polish);
            }
        }
    }

    return status;
}