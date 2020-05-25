# IOSet
The aim of this project is to use the C++ type system to detect and avoid errors by precisely
defining subsets of types. For this possible values are collected in a set, implemented
as a single-linked list with a sort and duplicate removal normalization.

This set can then be used as the input for functions, the possible output values are
automatically deduced by the type system and are broadcasted to different functions.

This complete process is implement using C++ meta programming with concepts.

**Due to the limitations of most C++ compilers when recursively resolving templates this can not
be used for real world applications.**
