add_library( polynomial
    SHARED

    abstract_polynomial_equations.h

    linerequation.cpp
    linerequation.h

    quadraticequation.cpp
    quadraticequation.h

    cubicequation.cpp
    cubicequation.h

    root.h
)

target_include_directories( polynomial
  PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src;${CMAKE_BINARY_DIR}/src>"
    "$<INSTALL_INTERFACE:include>"
)
