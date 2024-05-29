# CMakeList.txt : projet CMake pour Game engine, incluez la source et définissez
# la logique spécifique au projet ici.
#
cmake_minimum_required (VERSION 3.8)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

# Ajoutez une source à l'exécutable de ce projet.
add_executable (GameEngine "GameEngine.cpp" "GameEngine.h" "main.cpp"  "ResourceManager.h" "ResourceManager.cpp" "LabelManager.h" "labelManager.cpp" "ButtonManager.h" "ButtonManager.cpp")

target_link_libraries(GameEngine SDL2::SDL2 SDL2::SDL2main SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET GameEngine PROPERTY CXX_STANDARD 20)
endif()

# TODO: Ajoutez des tests et installez des cibles si nécessaire.
