# Discourse : Commentary on Python/C++ {#discourse}

## How is my code?

1. Setters/getters
    - [Use case for setters/getters](https://stackoverflow.com/a/1568230/7248295)
    - Do we really need setters/getters?
    - We can publically expose const data members of a class as opposed to implementing getters for a private const. Simply because the const members cannot be modified so data integrity isn't an issue.
    - Can we expose non const data members as public?
      1. If value needs to be mofified externally, but no additional checks are required inside a setter (type check is sufficient)
      2.  What if additional checks are required later on?
          - [It will be a maintenance nightmare to find all the direct assignments.](https://stackoverflow.com/a/1568103/7248295)
          - [We can publically expose data members as long as they are of the type that we **really** want.](https://stackoverflow.com/a/51616894/)

## 2. Design notes

- Our core C++ library, which includes the data-structures that store the symbols in the model, axioms, and algorithms that implement the interpretation of the model "should be independent" of any extensions/wrappers that we write. This would prevent us from tainting the C++ library with python dependencies.
- *pybind11* extensions and related translation services would depend on the core C++ library, but not vice-versa. 
- The point of *pybind11* extensions is to ease research and learning, use cases where the overhead is minor or can be ignored. Otherwise, specifying the problem directly into the C++ data-structures should be considered, e.g. for production use.