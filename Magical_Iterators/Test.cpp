#include <iostream>
#include "doctest.h"
#include "MagicalContainer.hpp"

using namespace ariel;
using namespace std;


TEST_CASE( "MagicalContainer")
{

MagicalContainer containerTester;

    SUBCASE ("adding elements")
    {
        containerTester.addElement(5);
        CHECK(containerTester.size()==1);
        containerTester.addElement(12);
        CHECK(containerTester.size()==2);
        containerTester.addElement(6);
        containerTester.addElement(7);
        containerTester.addElement(7);
        CHECK(containerTester.size()==4);
    }         

    SUBCASE ("removing elemnsts")
    {
        containerTester.addElement(7);
        containerTester.addElement(8);
        CHECK_NOTHROW(containerTester.removeElement(7));
        CHECK(containerTester.size()==1);
        CHECK_THROWS(containerTester.removeElement(11));
    }
}



TEST_CASE (" acsending iterator to fit demo")
{
    MagicalContainer containerTester;
    containerTester.addElement(17);
    containerTester.addElement(2);
    containerTester.addElement(25);
    containerTester.addElement(9);
    containerTester.addElement(3);
    SUBCASE(" iterating"){
        
        MagicalContainer::AscendingIterator it(containerTester);
        CHECK(*it == 2);
        ++it;
        CHECK(*it == 3);
        ++it;
        CHECK(*it == 9);
        ++it;
        CHECK(*it == 17);
        ++it;
        CHECK(*it == 25);
        ++it;
        CHECK(it == it.end());
    }
    SUBCASE(" iterate a null one")
    {
    MagicalContainer containerTesterNull;
    MagicalContainer::AscendingIterator it(containerTesterNull);
CHECK(it == it.end());
    }
}


TEST_CASE (" SideCross iterator to fit demo")
{
    MagicalContainer containerTester;
    containerTester.addElement(17);
    containerTester.addElement(2);
    containerTester.addElement(25);
    containerTester.addElement(9);
    containerTester.addElement(3);
    SUBCASE(" iterating"){
        MagicalContainer::SideCrossIterator it(containerTester);
        CHECK(*it == 2);
        ++it;
        CHECK(*it == 25);
        ++it;
        CHECK(*it == 3);
        ++it;
        CHECK(*it == 17);
        ++it;
        CHECK(*it == 9);
        ++it;
        CHECK(it == it.end());
    }
  
}

TEST_CASE (" PrimeIterator  to fit demo")
{
    MagicalContainer containerTester;
    containerTester.addElement(17);
    containerTester.addElement(2);
    containerTester.addElement(25);
    containerTester.addElement(9);
    containerTester.addElement(3);
    SUBCASE(" iterating"){
        MagicalContainer::PrimeIterator it(containerTester);
        CHECK(*it == 2);
        ++it;
        CHECK(*it == 3);
        ++it;
        CHECK(*it == 17);
        ++it;
        CHECK(it == it.end());
    }
    SUBCASE(" iterate a null one")
    {
    MagicalContainer containerTesterNull;
    MagicalContainer::PrimeIterator it(containerTesterNull);
    CHECK(it==it.end());
    }
}
