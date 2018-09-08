file(GLOB SRCS "*.cpp")

include_directories(".")

add_library(cuttle-vm SHARED ${SRCS})
