   #include <gtest/gtest.h>

   extern void my_function(int, int, int, int);

   TEST(MyFunctionTest, TooManyParams) {
       EXPECT_NO_FATAL_FAILURE(my_function(1, 2, 3, 4));
   }

   int main(int argc, char **argv) {
       ::testing::InitGoogleTest(&argc, argv);
       return RUN_ALL_TESTS();
   }