cmake_minimum_required(VERSION 2.8)

project( Carta )

add_executable( Carta carta.cpp )

find_package( OpenCV REQUIRED )
find_package( Boost COMPONENTS program_options REQUIRED )


target_link_libraries( Carta ${OpenCV_LIBS} ${Boost_LIBRARIES})
