# dummy file to save folder

add_executable(TestBoostAsio delete_me.cpp)

target_link_libraries(TestBoostAsio PRIVATE Boost::asio)

set_target_properties(TestBoostAsio PROPERTIES
    AUTOMOC OFF
    AUTOUIC OFF
    AUTORCC OFF
)