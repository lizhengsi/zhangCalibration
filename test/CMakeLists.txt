# generate executable file
add_executable( zhangCalibration main.cpp )

# link libs with exe
target_link_libraries( zhangCalibration zhanglib ${THIRD_PARTY_LIBS})