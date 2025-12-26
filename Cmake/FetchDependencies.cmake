include(FetchContent)


set(CMAKE_AUTOMOC OFF)
set(CMAKE_AUTORCC OFF)
set(CMAKE_AUTOUIC OFF)

function(installBoostModule module_name boost_version)
    string(PREPEND full_module_name sw_boost_)
    set(full_module_name "${full_module_name}${module_name}")

    FetchContent_Declare(${full_module_name}
        GIT_REPOSITORY "https://github.com/boostorg/${module_name}.git"
        GIT_TAG ${boost_version}
        GIT_PROGRESS TRUE
        GIT_SHALLOW TRUE
    )
    FetchContent_MakeAvailable(${full_module_name})
endfunction()


set(BOOST_VERSION boost-1.88.0)
set(BOOST_MODULES
    # Boost core
    assert
    static_assert
    config
    core
    headers
    throw_exception
    system

    # For boost::intrusive_ptr & asio
    smart_ptr

    # For boost::asio
    variant2
    tokenizer
    unordered
    regex
    range
    optional
    functional
    typeof
    utility
    mpl
    function_types
    describe
    container_hash
    fusion
    conversion
    detail
    iterator
    numeric_conversion
    function
    move
    intrusive
    tuple
    container
    lexical_cast
    exception
    preprocessor
    concept_check
    bind
    array
    io
    algorithm
    date_time
    predef
    winapi
    type_traits
    integer
    pool
    mp11
    context
    align
    asio
)

foreach (module IN LISTS BOOST_MODULES)
    installBoostModule(${module} ${BOOST_VERSION})
endforeach ()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)