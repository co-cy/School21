//
// Created by Nana Daughterless on 5/9/22.
//

long long int s21_factorial(long long int n) {
    long long int res = 1;

    for (long long int i = 1;n > 0;n--, i++) {
        res *= i;
    }
    return res;
}