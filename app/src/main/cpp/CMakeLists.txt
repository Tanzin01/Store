cmake_minimum_required(VERSION 3.18.1)

project("Store")

add_library(store SHARED
            hello-jni.c
            Store.h)



# Include libraries needed for hello-jni lib
target_link_libraries(store
                      android
                      log)
