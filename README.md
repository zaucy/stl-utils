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

#### utils::trim_string (string, character_set)
__return__: string_type

Removes the beginning and end characters matching any characters in the `character_set`. The `character_set` parameter will accept a `std::initializer_list<char_type>` or a `char_type` to create a default character set. Characters will be check through a list or a single character, respectively.

You may also create your own character_set class. A single member function is required to be considered a character_set class. The signatures is as follows:
```cpp
// Check if `c` belongs to this character set
bool MyCharacterSet::is_character(char_type c) const;
```
A 'whitespace' character set is provided for you for convenience. If you have C++14 enabled you can use variable templates to access it with `utils::whitespace_characters<char_type>`. Otherwise you'll have to create an instance of `utils::whitespace_character_set<char_type>` and use that instead.

__EXAMPLE__
```cpp
// should return "HELLO WORLD"
utils::trim("      HELLO WORLD       ", ' ');

// using C++14 variable templates
utils::trim("\t\t HELLO WORLD \r\n ", utils::whitespace_characters<char>);

// using C++ without variable templates
utils::trim("\t\t HELLO WORLD \r\n ", utils::whitespace_character_set<char>());
```
