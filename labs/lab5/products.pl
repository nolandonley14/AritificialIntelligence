products(1, 1).

products(N, Nprod) :-
    N > 1,
    NMinus1 is N - 1,
    NCubed is N * N * N,
    products(NMinus1, NMinus1prod),
    Nprod is NCubed * NMinus1prod.
