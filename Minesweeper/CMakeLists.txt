cmake_minimum_required(VERSION 3.19)
project(Minesweeper LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(Minesweeper
    WIN32 MACOSX_BUNDLE
    main.cpp
    menuprincipal.cpp
    menuprincipal.h
    menuprincipal.ui
    frminiciosesion.h
    frminiciosesion.cpp
    frminiciosesion.ui
    frmregistro.h
    frmregistro.cpp
    frmregistro.ui
    usuario.h
    usuario.cpp
    manejousuario.h
    manejousuario.cpp
    frmmenujuego.h
    frmmenujuego.cpp
    frmmenujuego.ui
    tableroLogico.h
    celda.h
    tableroLogico.cpp
    Celda.cpp
)

target_link_libraries(Minesweeper
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS Minesweeper
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Minesweeper
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)

install(SCRIPT ${deploy_script})