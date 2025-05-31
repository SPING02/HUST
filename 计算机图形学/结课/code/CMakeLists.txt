add_executable(algo main.cpp shader.cpp camera.cpp stb_image.cpp cube.cpp "include/glm/detail/glm.cpp" "include/glm/simd/common.h" "include/glm/simd/exponential.h" "include/glm/simd/geometric.h" "include/glm/simd/integer.h" "include/glm/simd/matrix.h" "include/glm/simd/neon.h" "include/glm/simd/packing.h" "include/glm/simd/platform.h" "include/glm/simd/trigonometric.h" "include/glm/simd/vector_relational.h")


target_include_directories(algo PUBLIC ./include)
target_link_libraries(algo PUBLIC glfw glad glm assimp::assimp STB)

configure_file(shaders/colors.vs colors.vs COPYONLY)
configure_file(shaders/colors.fs colors.fs COPYONLY)
configure_file(shaders/light_cube.vs light_cube.vs COPYONLY)
configure_file(shaders/light_cube.fs light_cube.fs COPYONLY)

install(TARGETS algo RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(FILES shaders/colors.vs shaders/colors.fs shaders/light_cube.vs shaders/light_cube.fs
	DESTINATION ${CMAKE_INSTALL_BINDIR}
)