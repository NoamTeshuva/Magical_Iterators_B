#include "MagicalContainer.hpp"
#include <stdexcept>
#include <algorithm>
#include <iostream>

using namespace std;

namespace ariel {

MagicalContainer::MagicalContainer() {} 

/********************************* for the Prime Iterator *********************/
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

void MagicalContainer::addElement(int number) {
    // Add the number to the elements vector
    elements.push_back(number);
    std::sort(elements.begin(), elements.end());
}

int MagicalContainer::size() {
    return this->elements.size();
}

void MagicalContainer::removeElement(int number) {
    bool exist = false;
    for (const auto& element : elements) {
        if (number == element) {
            exist = true;
        }
    }
    if (!exist) {
        std::__throw_runtime_error("cant remove not exist element");
    }

    // Find the position of the number in the elements vector
    auto it = std::find(elements.begin(), elements.end(), number);

    // If the number is found, remove it from the elements vector
    if (it != elements.end()) {
        elements.erase(it);

        // Check if the number was prime and remove its pointer from the primePointer vector
        if (isPrime(number)) {
            auto primePointerIt = std::find(primePointer.begin(), primePointer.end(), &(*it));
            if (primePointerIt != primePointer.end()) {
                primePointer.erase(primePointerIt);
            }
        }
    }
}

MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer& container)
    : container(container), index(0) {}

MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator& other)
    : container(other.container), index(other.index) {}

MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator=(const AscendingIterator& other) {
    if (this->container.elements != other.container.elements) {
        std::__throw_runtime_error("error");
    }
    if (this != &other) {
        container = other.container;
        index = other.index;
    }
    return *this;
}

bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator& other) const {
    // Compare the positions of the iterators
    return index < other.index;
}

bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator& other) const {
    // Compare the positions of the iterators
    return index > other.index;
}

bool MagicalContainer::AscendingIterator::operator<=(const AscendingIterator& other) const {
    // Compare the positions of the iterators
    return index <= other.index;
}

bool MagicalContainer::AscendingIterator::operator>=(const AscendingIterator& other) const {
    // Compare the positions of the iterators
    return index >= other.index;
}

bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator& other) const {
    return &container == &other.container && index == other.index;
}

bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator& other) const {
    return !(*this == other);
}

MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator++() {
    if (index == container.elements.size()) {
        std :: __throw_runtime_error("Cant increment beyond the end");
    }
    index++;
    return *this;
}

int MagicalContainer::AscendingIterator::operator*() const {
    return container.elements[index];
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() {
    index = 0;
    return *this;
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() {
    index = container.elements.size();
    return *this; 
}

// SideCrossIterator constructor
MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer& container)
    : container(container), forwardIndex(0), reverseIndex(container.elements.size() - 1),
      Forward(true), reachEnd(false), countLoop(0) {
}

// SideCrossIterator copy constructor
MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator& other)
    : container(other.container), forwardIndex(other.forwardIndex),
      reverseIndex(other.reverseIndex), Forward(other.Forward),
      reachEnd(other.reachEnd) {
}

// SideCrossIterator assignment operator
MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator& other) {
    if (this->container.elements != other.container.elements) {
        std::__throw_runtime_error("error");
    }
    if (this != &other) {
        container = other.container;
        forwardIndex = other.forwardIndex;
        reverseIndex = other.reverseIndex;
        Forward = other.Forward;
        reachEnd = other.reachEnd;
    }
    return *this;
}

bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator& other) const {
    // Compare the positions of the iterators
    if (Forward && other.Forward) {
        return forwardIndex < other.forwardIndex;
    } else if (!Forward && !other.Forward) {
        return reverseIndex > other.reverseIndex;
    } else {
        // Different traversal directions, prioritize forward traversal
        return forwardIndex < other.forwardIndex;
    }
}

bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator& other) const {
    // Compare the positions of the iterators
    if (Forward && other.Forward) {
        return forwardIndex > other.forwardIndex;
    } else if (!Forward && !other.Forward) {
        return reverseIndex < other.reverseIndex;
    } else {
        // Different traversal directions, prioritize forward traversal
        return forwardIndex > other.forwardIndex;
    }
}

bool MagicalContainer::SideCrossIterator::operator<=(const SideCrossIterator& other) const {
    // Compare the positions of the iterators
    return (*this < other) || (*this == other);
}

bool MagicalContainer::SideCrossIterator::operator>=(const SideCrossIterator& other) const {
    // Compare the positions of the iterators
    return (*this > other) || (*this == other);
}

// SideCrossIterator equality operator
bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator& other) const {
    return forwardIndex == other.forwardIndex && reverseIndex == other.reverseIndex;
}

// SideCrossIterator inequality operator
bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator& other) const {
    return !(*this == other);
}

MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++() {
    if (forwardIndex == container.elements.size() || (reverseIndex == 0 && container.size() != 1)) {    
        throw std::runtime_error("cant increase out of the size");
    }

    if (reachEnd) {
        return *this;
    } else {
        if (Forward) {
            if (forwardIndex < container.elements.size() - 1) {
                ++forwardIndex;
            } else {
                Forward = false;  // Switch to reverse traversal
            }
        } else {
            if (reverseIndex > 0) {
                --reverseIndex;
            } else {
                reachEnd = true;  // Reached the end of the traversal
            }
        }
    }
    Forward = !Forward;
    // Check if the iteration count has reached the vector's size
    ++countLoop;
    if (countLoop == container.elements.size()) {
        reachEnd = true;
        forwardIndex = container.elements.size();
        reverseIndex = container.elements.size();
    }

    return *this;
}

// SideCrossIterator dereference operator
int MagicalContainer::SideCrossIterator::operator*() const {
    if (Forward) {
        return container.elements[forwardIndex];
    } else {
        return container.elements[reverseIndex];
    }
}

// SideCrossIterator begin() function
MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() {
    forwardIndex = 0;
    reverseIndex = container.elements.size() - 1;
    Forward = true;
    reachEnd = false;
    return *this;
}

// SideCrossIterator end() function
MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() {
    forwardIndex = container.elements.size();
    reverseIndex = container.elements.size();
    reachEnd = true;
    return *this;
}

// SideCrossIterator isEnd() function
bool MagicalContainer::SideCrossIterator::isEnd() const {
    return reachEnd;
}

MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer& container)
    : container(container), indexPointer(0) {
    for (std::vector<int>::size_type i = 0; i < container.elements.size(); i++) {
        if (isPrime(container.elements[i])) {
            container.primePointer.push_back(&container.elements[i]);
        }
    }
}

// Copy constructor
MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator& other)
    : container(other.container), indexPointer(other.indexPointer) {}

// Assignment operator
MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator=(const PrimeIterator& other) {
    if (this->container.elements != other.container.elements) {
        std::__throw_runtime_error("error");
    }
    if (this != &other) {
        container = other.container;
        indexPointer = other.indexPointer;
    }
    return *this;
}

// Comparison operators
bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator& other) const {
    return indexPointer == other.indexPointer;
}

bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator& other) const {
    return indexPointer < other.indexPointer;
}

bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator& other) const {
    return indexPointer > other.indexPointer;
}

bool MagicalContainer::PrimeIterator::operator<=(const PrimeIterator& other) const {
    return (*this < other) || (*this == other);
}

bool MagicalContainer::PrimeIterator::operator>=(const PrimeIterator& other) const {
    return (*this > other) || (*this == other);
}

bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator& other) const {
    return indexPointer != other.indexPointer;
}

// Increment operator
MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator++() {
    if (indexPointer == container.primePointer.size()) {
        std::__throw_runtime_error("Cant increment beyond the end");
    }
    ++indexPointer;
    return *this;
}

// Dereference operator
int MagicalContainer::PrimeIterator::operator*() const {
    return *container.primePointer[indexPointer];
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() {
    indexPointer = 0;
    return *this;
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() {
    indexPointer = container.primePointer.size();
    return *this;
}

} // namespace ariel
