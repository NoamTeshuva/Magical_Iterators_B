#include "MagicalContainer.hpp"
#include <stdexcept>

using namespace std;
namespace ariel{

MagicalContainer ::MagicalContainer() {} 


/*********************************for the prime Iterator*********************/
bool isPrime(int number) {
        if (number < 2)
            return false;

        for (int i = 2; i * i <= number; ++i) {
            if (number % i == 0)
                return false;
        }

        return true;
    }
/***********************************************************************************/

void MagicalContainer::addElement(int number)
{
elements [number]=  isPrime(number);
}

int MagicalContainer:: size()
{
    return this->elements.size();
}

void MagicalContainer::removeElement(int number)
{
    auto it = elements.find(number);
    if (it == elements.end()) {
        throw std::runtime_error("Element not found");
    }
    elements.erase(it);
}



MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer& container)
    : container(container), current(container.elements.begin()) {}

MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator& other)
    : current(other.current), container(other.container) {}

MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator=(const AscendingIterator& other) {
    if (this != &other) {
        current = other.current;
        container = other.container;
    }
    return *this;
}

bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator& other) const {
    return current == other.current;
}

bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator& other) const {
    return current != other.current;
}

const MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::operator++() {
    ++current;
    return *this;
}

int MagicalContainer::AscendingIterator::operator*() const {
    return current->first; // Access the key of the map element
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() {
    current=container.elements.begin();
    return *this;
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() {
   current = container.elements.end();
   return *this;
}







// Constructor
MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer& container)
    : container(container), forwardIter(container.elements.begin()), reverseIter(container.elements.rbegin()), isForward(true), isEndReached(false) {
}

// Copy constructor
MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator& other)
    : container(other.container), forwardIter(other.forwardIter), reverseIter(other.reverseIter), isForward(other.isForward), isEndReached(other.isEndReached), iterationCount(other.iterationCount) {
}

MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator& other) {
    if (this != &other) {
        // Assign the member variables of the iterator
        forwardIter = other.forwardIter;
        reverseIter = other.reverseIter;
        isForward = other.isForward;
        isEndReached = other.isEndReached;
        iterationCount = other.iterationCount;
    }
    return *this;
}



bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator& other) const {
    return *forwardIter == *other.forwardIter && *reverseIter == *other.reverseIter;
}

bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator& other) const {
    return !(*this == other);
}

// Increment operator
MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++() {
    if (isEndReached) {
        return *this;
    }

    if (isForward) {
        if (forwardIter != container.elements.end()) {
            ++forwardIter;
        }
    } else {
        if (reverseIter != container.elements.rend()) {
            ++reverseIter;
        }
    }

    isForward = !isForward;

    ++iterationCount;
    if (iterationCount == container.size()) {
        isEndReached = true;
        forwardIter = container.elements.end();
        reverseIter = container.elements.rend();
    }

    return *this;
}

// Dereference operator
int MagicalContainer::SideCrossIterator::operator*() const {
    if (isForward && forwardIter != container.elements.end()) {
        return forwardIter->first; // Access the key of the map element
    }
    if (!isForward && reverseIter != container.elements.rend()) {
        return reverseIter->first; // Access the key of the map element
    }
    return -1; // Return a default value to handle invalid cases
}

// Begin iterator
MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() {
    return SideCrossIterator(container);
}

// End iterator
MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() {
    SideCrossIterator iter(container);
    iter.isEndReached = true;
    iter.forwardIter = container.elements.end();
    iter.reverseIter = container.elements.rend();
    return iter;
}












// PrimeIterator
// Constructor
MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer& container)
    : container(container), current(container.elements.begin()) {
}

// Copy constructor
MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator& other)
    : container(other.container), current(other.current) {}

// Assignment operator
MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator=(const PrimeIterator& other) {
    if (this != &other) {
        container = other.container;
        current = other.current;
    }
    return *this;
}

// Comparison operators
bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator& other) const {
    return current == other.current;
}

bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator& other) const {
    return current != other.current;
}

// Increment operator
const MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::operator++() {
    ++current;
    // Find the next prime number
    while (current != container.elements.end() && !current->second) {
        ++current;
    }
    return *this;
}

// Dereference operator
int MagicalContainer::PrimeIterator::operator*() const {
    return current->first; // Access the key of the map element
}

// Begin iterator
MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() {
      current=container.elements.begin();
    return *this;
}

// End iterator
MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() {
   current = container.elements.end();
   return *this;}




}



