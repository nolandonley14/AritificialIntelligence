hassize(bluebird,small).
hascovering(bird,feathers).
hascolor(bluebird, blue).
hasproperty(bird,flies).
isa(bluebird,bird).
isa(bird,vertebrate).

is_bird(Bird) :-
    hascovering(Bird,feathers),
    hasproperty(Bird, flies),
    hassize(Bird,_),
    hascolor(Bird,_).
