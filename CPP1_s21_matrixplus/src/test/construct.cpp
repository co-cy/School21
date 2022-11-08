//
// Created by Nana Daughterless on 10/29/22.
//

#include "gtest/gtest.h"
#include "s21_matrix_oop.h"

TEST(ConstructTest, test1) { ASSERT_ANY_THROW(S21Matrix a(-100, 10)); }

TEST(ConstructTest, test2) { ASSERT_ANY_THROW(S21Matrix a(100, -100)); }

TEST(ConstructTest, test3) { ASSERT_NO_THROW(S21Matrix a(1, 0)); }

TEST(ConstructTest, test4) { ASSERT_NO_THROW(S21Matrix a(0, 100)); }
