add_executable( line-test
    line_ecqual.cxx
    test.h
)

target_link_libraries( line-test
    PRIVATE
    polynomial
    Qt${QT_VERSION_MAJOR}::Core
    )

add_executable( quadr-test quadr_ecqual.cxx )

target_link_libraries( quadr-test
    PRIVATE
    polynomial
    Qt${QT_VERSION_MAJOR}::Core
    )

add_executable( cub-test cub_ecqual.cxx )

target_link_libraries( cub-test
    PRIVATE
    polynomial
    Qt${QT_VERSION_MAJOR}::Core
    )
