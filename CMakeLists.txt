add_executable(reduce-sum
    reduce-sum.cc)

target_link_libraries(reduce-sum
    PRIVATE OMPC::Runtime)

