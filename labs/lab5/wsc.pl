is_in_class(toby, csc380).
is_in_class(bob, csc480).
is_in_class(toby, csc480).
is_in_class(nolan, csc380).
is_in_class(tucker, csc380).

is_in_room(csc480, wsc100).
is_in_room(csc380, wsc238).
is_in_room(csc310, wsc217).

has_temperature(wsc100, 65).
has_temperature(wsc238, 92).
has_temperature(wsc217, 80).
has_temperature(wsc236, 83).

is_hot(Person) :-
    is_in_class(Person, _),
    is_in_room(_, _),
    has_temperature(_, Temp),
    Temp > 80.
