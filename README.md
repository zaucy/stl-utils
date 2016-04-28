# STL Utils Library

Standard Template Library Utilility Library (STLUL)

This headers only library aims to provide some extra utilities to the Standard Template Library. Things that are typically available in other programming languages that are not available in C++.

## Current Status
### basic_string<>
#### utils::split_string (string, delimiter)
__return__: `std::vector<string_type>`

Splits a string by a delimiter. The delimiter may be a single character or a string.

#### utils::split_string_once (string, delimiter)
__return__: `std::pair<string_type, string_type>`

Splits a string on the first occurrence of the delimiter. The delimiter may be a single character or a string.
