#ifndef SCORER_HPP
#define SCORER_HPP

#include <folly/container/F14Map.h>
#include <iostream>
#include <cmath>

#ifndef EPSILON
#define EPSILON 0.001
#endif // EPSILON

namespace scorer {
    class Scorer {
        protected:
            folly::F14FastMap<std::string, std::string> *documents;
            folly::F14FastMap<std::string, unsigned long long> *wordFreqMap;
        public:
            Scorer(folly::F14FastMap<std::string, std::string> *documents, 
                folly::F14FastMap<std::string, unsigned long long> *wordFreqMap);
            virtual double score(unsigned long long docCount, unsigned long long docAppearances, 
                    unsigned long long termCount, unsigned long long docTermCount) = 0;
            virtual double score(const std::string &word, unsigned long long termCount, unsigned long long docTermCount) = 0;
            virtual ~Scorer();
    };
};

#endif // SCORER_HPP