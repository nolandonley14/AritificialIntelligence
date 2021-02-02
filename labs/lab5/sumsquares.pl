sum(1, 1).

sum(N, NSumSquare) :-
    N > 1,
    NMinus1 is N - 1,
    Nsquared is N * N,
    sum(NMinus1, Total),
    NSumSquare is Nsquared + Total.
