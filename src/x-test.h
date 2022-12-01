#ifndef __x_testing_h
#define __x_testing_h

#define TEST(NAME,BLOCK) \
int ##NAME_test(){\
    printf("---[start,test]--- %s -------------------------------------------------",NAME);\
    BLOCK\
    printf("---[end  ,test]--- %s -------------------------------------------------",NAME);\
}
#define TEST_inline(NAME,BLOCK) \
{\
    printf("---[start,test]--- %s -------------------------------------------------",NAME);\
    BLOCK\
    printf("---[end  ,test]--- %s -------------------------------------------------",NAME);\
}

#endif