find_package(Boost 1.55 COMPONENTS system)
find_package(OpenSSL REQUIRED)
find_package (Threads)
find_package(GTest REQUIRED)
set (CMAKE_CXX_STANDARD 17)

add_executable(TwitchXX-Tests Clip.t.cpp TwitchXX-Tests.cpp Entitlement.t.cpp Game.t.cpp AppAccessToken.t.cpp
                              UserAccessToken.t.cpp Stream.t.cpp TestConstants.h StreamMetadata.t.cpp User.t.cpp
                              UserFollows.t.cpp Video.t.cpp TestLogger.cpp TestLogger.h BitsLeaderboard.t.cpp
                              TestUtils.cpp TestUtils.h v5/Action.t.cpp v5/Channel.t.cpp v5/UserFollows.t.cpp)

target_include_directories(TwitchXX-Tests PUBLIC
        .)
target_link_libraries(TwitchXX-Tests TwitchXX Boost::system ${OPENSSL_LIBRARIES} cpprest ${GTEST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

