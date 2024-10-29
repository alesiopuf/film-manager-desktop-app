//
// Created by user on 4/3/2024.
//

#ifndef POO_LAB_6_7_TESTMODULE_H
#define POO_LAB_6_7_TESTMODULE_H


#include <vector>
#include "../domain/Film.h"

class TestModule {

private:
    static void testFilmService();

    static void testFilmContainerService();

    static void testFilmRepository();

    static void testFilmValidator();

public:
    static void testAll();
};


#endif //POO_LAB_6_7_TESTMODULE_H
