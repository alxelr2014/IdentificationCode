# Channel Simulation

## Main Objectives
1. Prime number generation: currently the code uses a [Eratosthenes' sieve](https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes) which is a simple algorithm. A more sophisticated prime generation algorithm might be better suited.

2. Randomized Primes: It seems that the 3-step algorithm does not really use all the `k`th first primes. Therefore, maybe we can use a randomized prime generation algorithm to boost the efficiency of the algorithm. However, this might come at expense of more complicated error analysis. 
3. Other channels: How does the algorithm generalize to other channels like *binary erasure*, *non-symmetric binary*, *noisy binary symmetric channel*, and general *DMC*? 
4. Error Analysis: A detailed analysis for type 1 and 2 errors-- with graphs. 
5. A more thorough understanding of the algorithm and the paper itself.
6. Extending the algorithm: In what ways can we generalize the algorithms? removing the primes! relationship with other coding schemes, their similarities, and their differences! Other improvements and optimizations!

## TODO List
- Miller-Rabin error analysis
- Improve the Miller-Rabin in the code and improve the code for BSC
- Pictorial representation of sieve of Eratosthenes
- Sources of randomness and determining the required randomness in the PNG
- proof Mertens' second theorem
- PNT statement, variations, corollary, history of proof, proof sketch
- Adding the code and the algorithms to the report
- Generate an error curve for noiseless BSC