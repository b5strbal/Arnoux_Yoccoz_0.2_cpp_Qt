#ifndef PERMUTATION_H
#define PERMUTATION_H

#include <vector>

/*!
 * \brief The Permutation class represents a permutation on integers 0, 1, ..., n-1.
 * \author Balazs Strenner, strenner@math.wisc.edu
 * \date April 19, 2013
 * \see IntervalExchangeBase, IntervalExchangeMap, TwistedIntervalExchangeMap,
 *      IntervalExchangeFoliationDisk
 *
 * As usual, a list like {3, 2, 0, 1} codes the following permutation on 4 elements:
 * 0->3, 1->2, 2->0, 3->1. If the permutation is considered to be a one-to-one
 * function {0,1,...,n-1}->{0,1,...,n-1}, then the above list is the list of the
 * values of this function at points 0, 1, ..., n-1.
 *
 * When composing two Permutations, we compose them as one usually composes two
 * functions, i.e. (p1*p2)(x) = p1(p2(x)).
 */
class Permutation{
public:
    Permutation(); // Constructs the permutation on a 1-element set.
    Permutation(const std::vector<unsigned int> &functionValues);
    static Permutation rotatingPermutation(int size, int rotationAmount);
    static Permutation reversingPermutation(int size);
    Permutation inverse() const;
    unsigned int size() const;
    unsigned int operator[](unsigned int index) const { return m_functionValues[index]; }
    friend Permutation operator*(const Permutation& p1, const Permutation& p2);
    friend std::ostream& operator<<(std::ostream& out, const Permutation& perm);

    template <typename Type>
    std::vector<Type> actOn(const std::vector<Type>& vec) const{
        if (size() != vec.size()) {
            throw std::runtime_error("A permutation can't act on a vector if the sizes are different.");
        }
        std::vector<Type> newVector(size());
        for (unsigned int i = 0; i < size(); i++) {
            newVector[m_functionValues[i]] = vec[i];
        }
        return newVector;
    }


private:
    std::vector<unsigned int> m_functionValues;
};


#endif // PERMUTATION_H








