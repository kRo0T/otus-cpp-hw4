cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(homework_4 VERSION ${PROJECT_VESRION})

#configure_file(version.h.in version.h)

add_executable(print_ip print_ip.cpp)

set_target_properties(print_ip PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(print_ip
    PRIVATE "${CMAKE_BINARY_DIR}"
)

if (MSVC)
    target_compile_options(print_ip PRIVATE
        /W4
    )
else ()
    target_compile_options(print_ip PRIVATE
        #-Wall -Wextra -pedantic -Werror
        -Wall -Wextra
    )
endif()

install(TARGETS print_ip RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT e.krotov@mail.ru)
include(CPack)

enable_testing()
include(CTest)
