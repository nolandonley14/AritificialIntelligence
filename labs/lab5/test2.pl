male(bart).
male(homer).
male(abe).

female(marge).
female(maggie).
female(lisa).

parent_of(marge, maggie).
parent_of(marge, lisa).
parent_of(marge, bart).
parent_of(homer, maggie).
parent_of(homer, lisa).
parent_of(homer, bart).
parent_of(abe, homer).
parent_of(orivlle, abe).

father_of(F, K) :- male(F), parent_of(F,K).
mother_of(M, K) :-
    female(M),
    parent_of(M,K).

grandparent_of(G, K) :-
    parent_of(G, P),
    parent_of(P, K).

has_kid(P) :- parent_of(P, K).
