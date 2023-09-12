[![Stand With Ukraine](https://raw.githubusercontent.com/vshymanskyy/StandWithUkraine/main/banner-direct-single.svg)](https://stand-with-ukraine.pp.ua)

# mal-math

`mal-math` is a comprehensive C++20 mathematics library, providing a suite of utilities and structures to handle various mathematical constructs in an efficient and user-friendly manner.

## Table of Contents

- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Documentation](#documentation)
- [Contribute](#contribute)
- [License](#license)

## Features

- **Matrices, vectors and quaternions**: Generic mathematicals structures, supporting different dimensions and primitive types.
- **Efficiency**: Highly optimized functions using modern C++ features.
- **Extensibility**: Built with modularity in mind, making it easier to extend or adapt to specific needs.
- **Doxygen Comments**: Comprehensive Doxygen documentation for all classes, functions, and members, enabling automatic generation of detailed documentation.
- **Downsides**: Doesn't have SIMD(U*yet*).
## Installation

1. Clone the repository:
   ```
   git clone https://github.com/malatindez/math
   ```

## Usage

Here's a basic example on how to use the `vec` structure:

```cpp
#include "mal-math/vec.hpp"

int main() {
    mal_math::vec3 v1(1.0f, 2.0f, 3.0f);
    mal_math::vec3 v2(2.0f, 3.0f, 4.0f);
    mal_math::mat3 m1(v1, v2, 3,4,5);
    mal_math::mat3 m2(v1, v1, v1);
    auto result_v = v1 + v2;
    auto result_m = m1 + m2;
    std::cout << result_v; // 
    std::cout << result_m; // operator<< is overloaded as well
    // Do more stuff...
    return 0;
}
```

## Documentation

The documentation is available @ [malatindez.github.io/math](https://malatindez.github.io/math/)

## Contribute

1. Fork the repository.
2. Create your feature branch: `git checkout -b feature/my-new-feature`
3. Commit your changes: `git commit -m "Add my new feature"`
4. Push to the branch: `git push origin feature/my-new-feature`
5. Submit a pull request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.