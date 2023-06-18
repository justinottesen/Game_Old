REFERENCES:
Wikipedia - Perlin Noise:
  https://en.wikipedia.org/wiki/Perlin_noise
Haoyi's Programming Blog - Build your own Command Line with ANSI escape codes
  https://www.lihaoyi.com/post/BuildyourownCommandLinewithANSIescapecodes.html
CPP Reference - std::hash
  https://en.cppreference.com/w/cpp/utility/hash
CPP Reference - std::unique_ptr
  https://en.cppreference.com/w/cpp/memory/unique_ptr

CODING CONVENTIONS:
  - use camelCase
  - name private member variables following format m_VariableName
  - 2 spaces per indent, indent using spaces not tabs
  - Only use structs for pure data objects, should have no methods (maybe constructor?)
  - Keep lines to < 100 characters
  - ALWAYS use curly braces to indicate scope, even for one line if statements & for loops
  - Class format:   Not too strict about this one, just kinda do what makes sense
      1. typedefs
      2. Types / classes / structs
      3. PUBLIC Constructors & Assignments & Destructor
      4. Public functions + member variables
      5. Private functions
      6. Private variables
  - Use static_cast instead of c style casting
  - Do not ignore compiler warnings
  - Do not leak memory
  - Use smart pointers wherever possible

In general, follow the format you see. Some are more strict than others.

DECISIONS:
  - Currently each chunk holds a std::unique_ptr<Tile[]>, for runtime determined but fixed size.
    Options:
      1. std::unique_ptr<Tile[]>
      2. std::vector<Tile>
      3. Compile time determine chunk size, use std::array<Tile, ChunkSize>