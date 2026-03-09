cmake_minimum_required(VERSION 3.28.3)

project(btree)

set(BTREE_SRCS
    src/btree/btree.c
)

set(BTREE_HDRS
    inc/
)

add_library(btree ${BTREE_SRCS})

target_include_directories(btree PUBLIC ${BTREE_HDRS})

set(SOURCES
    src/main.c
)

add_executable(app ${SOURCES})
target_link_libraries(app btree)