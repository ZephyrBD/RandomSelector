cmake_minimum_required(VERSION 3.29)
project(RandomSelector)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "E:/Qt/6.8.0/mingw_64")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Multimedia
        Network
        REQUIRED)

add_executable(${PROJECT_NAME}
        include/ElaWidgetTools.qrc
        main.cpp
        randomselector.cpp
        res.qrc
        settings.cpp
        Filehelp.h
        UIhelp.h
        node.h
        randomselector.h
        settings.h
        randomselector.ui
        settings.ui
        version.rc
)

target_link_libraries(RandomSelector
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Multimedia
        Qt::Network
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/ElaWidgetTools.lib
)

include_directories(
        include
)
if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/platforms/")
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/styles/qmodernwindowsstyle${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/styles/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/styles/qmodernwindowsstyle${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/styles/")
    endif ()

    # 添加 Multimedia 和 Network 库
    foreach (QT_LIB Core Gui Widgets Multimedia Network)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)

    # 复制 MinGW 运行时库
    set(MINGW_RUNTIME_LIBS "libstdc++-6.dll" "libgcc_s_seh-1.dll" "libwinpthread-1.dll")
    foreach (LIB ${MINGW_RUNTIME_LIBS})
        if (EXISTS "${QT_INSTALL_PATH}/bin/${LIB}")
            add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy
                    "${QT_INSTALL_PATH}/bin/${LIB}"
                    "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
        endif ()
    endforeach ()

    # 复制多媒体后端插件
    set(MULTIMEDIA_PLUGINS_DIR "${QT_INSTALL_PATH}/plugins/multimedia")
    if (EXISTS "${MULTIMEDIA_PLUGINS_DIR}")
        file(GLOB MULTIMEDIA_PLUGINS "${MULTIMEDIA_PLUGINS_DIR}/*.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/multimedia/")
        foreach (PLUGIN ${MULTIMEDIA_PLUGINS})
            add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy
                    "${PLUGIN}"
                    "$<TARGET_FILE_DIR:${PROJECT_NAME}>/multimedia/")
        endforeach ()
    endif ()

    file(COPY "lib/ElaWidgetTools.dll" DESTINATION "${CMAKE_BINARY_DIR}")
    set_target_properties(${PROJECT_NAME} PROPERTIES
            WIN32_EXECUTABLE TRUE
            MACOSX_BUNDLE TRUE
    )
    set_target_properties(${PROJECT_NAME} PROPERTIES
            ENVIRONMENT "QT_PLUGIN_PATH=$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins")
endif ()