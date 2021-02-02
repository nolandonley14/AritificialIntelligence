animal(dog)  :- is_true('has fur'), is_true('says woof').
animal(cat)  :- is_true('has fur'), is_true('says meow').
animal(duck) :- is_true('has feathers'), is_true('says quack').
animal(mouse) :- is_true('is small'), is_true('says squeak').
animal(lion) :- is_true('has fur'), is_true('says roar').
animal(giraffe) :- is_true('is tall'), is_true('has spots').
animal(elephant) :- is_true('is big'), is_true('has trunk').
animal(bear) :- is_true('has fur'), is_true('is Mercer\'s Mascot').
animal(cheetah) :- is_true('has spots'), is_true('is fast').
animal(dolphin) :- is_true('can swim'), is_true('is smart').

is_true(Q) :-
        format("~w?\n", [Q]),
        read(yes).
