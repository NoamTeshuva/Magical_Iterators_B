#pragma once
#include <vector>
#include <map>

using namespace std;
namespace ariel{

class MagicalContainer{
protected:
std::map<int , bool> elements;


public:
MagicalContainer();
void addElement (int number);
int size();
void removeElement(int number);



/*

************************** TAKEN FROM THE GIT OF THE COURSR********************

*/
//-------------------------------------------------------------------
	// iterator related code:
	// inner class and methods that return instances of it)
	//-------------------------------------------------------------------
	

    
	struct Node {
    std::pair<int, bool> m_value;
    Node* m_next;
    Node(const int v, Node* n)
        : m_value(v, false), m_next(n) {
    }
};
    


class AscendingIterator {
private:
    MagicalContainer &container;
    std::map<int, bool>::iterator current;

public:
AscendingIterator( MagicalContainer& container);
AscendingIterator(const AscendingIterator& other); //Copy ctor

AscendingIterator& operator=(const AscendingIterator& other);// copy

bool operator==(const AscendingIterator& other)const ;//compare
bool operator!=(const AscendingIterator& other)const;//compare
const AscendingIterator operator++();// inc

int operator*() const; // access value

AscendingIterator begin();
AscendingIterator end();
};

	//-------------------------------------------------------------------
    class SideCrossIterator {
        private:
            MagicalContainer& container;
            std::map<int, bool>::iterator forwardIter;
            std::map<int, bool>::reverse_iterator reverseIter;
            bool isForward;
            bool isEndReached;
            int iterationCount;

        public:
            SideCrossIterator(MagicalContainer& container);

                SideCrossIterator(const SideCrossIterator& other);


            SideCrossIterator& operator=(const SideCrossIterator& other);// copy
 

            bool operator==(const SideCrossIterator& other) const;
            bool operator!=(const SideCrossIterator& other) const;
            bool operator>(const SideCrossIterator& other) const;
            bool operator<(const SideCrossIterator& other) const;
            int operator*() const;
            SideCrossIterator& operator++();
            SideCrossIterator begin();
            SideCrossIterator end();
            bool isEnd() const;
};
	//-------------------------------------------------------------------





class PrimeIterator{
private:
 MagicalContainer &container;
    std::map<int, bool>::iterator current;

public:
PrimeIterator(MagicalContainer& container);
PrimeIterator(const PrimeIterator& other); //Copy ctor

PrimeIterator& operator=(const PrimeIterator& other);// copy

bool operator==(const PrimeIterator& other)const ;//compare
bool operator!=(const PrimeIterator& other)const;//compare
const PrimeIterator operator++();// inc

int operator*() const; // access value

PrimeIterator begin();
PrimeIterator end();

};



}; // End of class MagicalContainer
}