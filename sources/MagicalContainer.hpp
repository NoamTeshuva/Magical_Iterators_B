#pragma once
#include <vector>
#include <map>

using namespace std;

namespace ariel {

    class MagicalContainer {
    private:
        std::vector<int> elements;
        std::vector<int*> primePointer;

    public:
        MagicalContainer();
        void addElement(int number);
        int size();
        void removeElement(int number);

        class AscendingIterator {
        private:
            MagicalContainer& container;
            size_t index;

        public:
            AscendingIterator(MagicalContainer& container);
            AscendingIterator(const AscendingIterator& other); // Copy ctor
            AscendingIterator& operator=(const AscendingIterator& other); // Copy assignment

            bool operator==(const AscendingIterator& other) const; // Compare equality
            bool operator!=(const AscendingIterator& other) const; // Compare inequality

            bool operator<(const AscendingIterator& other) const;
            bool operator>(const AscendingIterator& other) const;
            bool operator<=(const AscendingIterator& other) const;
            bool operator>=(const AscendingIterator& other) const;

            AscendingIterator& operator++(); // Pre-increment
            int operator*() const; // Dereference

            AscendingIterator begin(); // Get iterator to beginning
            AscendingIterator end(); // Get iterator to end
        };

        class SideCrossIterator {
        private:
            MagicalContainer& container;
            size_t forwardIndex;
            size_t reverseIndex;
            bool Forward;
            bool reachEnd;
            int countLoop;

        public:
            SideCrossIterator(MagicalContainer& container);
            SideCrossIterator(const SideCrossIterator& other);
            SideCrossIterator& operator=(const SideCrossIterator& other);
            bool operator==(const SideCrossIterator& other) const;
            bool operator!=(const SideCrossIterator& other) const;
            bool operator<(const SideCrossIterator& other) const;
            bool operator>(const SideCrossIterator& other) const;
            bool operator<=(const SideCrossIterator& other) const;
            bool operator>=(const SideCrossIterator& other) const;
            SideCrossIterator& operator++();
            int operator*() const;
            SideCrossIterator begin();
            SideCrossIterator end();
            bool isEnd() const;
        };

        class PrimeIterator {
        private:
            MagicalContainer& container;
            size_t indexPointer;

        public:
            PrimeIterator(MagicalContainer& container);
            PrimeIterator(const PrimeIterator& other); // Copy ctor
            PrimeIterator& operator=(const PrimeIterator& other); // Copy assignment

            bool operator==(const PrimeIterator& other) const; // Compare equality
            bool operator!=(const PrimeIterator& other) const; // Compare inequality
            bool operator<(const PrimeIterator& other) const;
            bool operator>(const PrimeIterator& other) const;
            bool operator<=(const PrimeIterator& other) const;
            bool operator>=(const PrimeIterator& other) const;

            PrimeIterator& operator++(); // Pre-increment
            int operator*() const; // Dereference

            PrimeIterator begin(); // Get iterator to beginning
            PrimeIterator end(); // Get iterator to end
        };
    };
}