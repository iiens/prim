//
// Created by doe on 17/04/2021.
//

#ifndef STRUCTURE_LIST_TEST_H
#define STRUCTURE_LIST_TEST_H

struct test_List_S {
    char* description;
    void (*function)(void);
};
typedef struct test_List_S test_List;

#endif //STRUCTURE_LIST_TEST_H
