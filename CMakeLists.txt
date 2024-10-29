cmake_minimum_required(VERSION 3.22)
project(POO_Lab_10_11)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH  "C:/Qt/6.7.0/mingw_64/lib/cmake/")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -W -Wextra")

find_package(Qt6Core REQUIRED)
find_package(Qt6Gui REQUIRED)
find_package(Qt6Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_executable(POO_Lab_10_11 main.cpp
        domain/Film.cpp
        domain/Film.h
        exceptions/FilmContainerServiceException.h
        exceptions/FilmServiceException.h
        exceptions/FilmRepositoryException.h
        exceptions/FilmValidatorException.h
        repository/FilmRepository.cpp
        repository/FilmRepoFile.h
        repository/FilmRepoLab.h
        repository/FilmRepository.h
        repository/FilmRepositoryAbstract.h
        service/FilmContainerService.cpp
        service/FilmContainerService.h
        service/FilmService.cpp
        service/FilmService.h
        service/undo.h
        test/TestModule.cpp
        test/TestModule.h
        validator/FilmValidator.cpp
        validator/FilmValidator.h
        ui/FilmGUI.h
        ui/FilmGUI.cpp
        ui/observer.h
        ui/CosCRUDGUI.h
        ui/CosReadOnlyGUI.h
        ui/MyListModel.h)

target_link_libraries(POO_Lab_10_11 Qt6::Widgets)
target_link_libraries(POO_Lab_10_11 Qt6::Core)
target_link_libraries(POO_Lab_10_11 Qt6::Gui)