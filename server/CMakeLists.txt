cmake_minimum_required (VERSION 2.8.11)

project (server.out)

set(SOURCES
    app/src/Controller/AlarmController.cpp
    app/src/Controller/TrainController.cpp
    app/src/Controller/WeatherController.cpp

    app/src/CommandHandler/CommandHandler.cpp
    app/src/CommandHandler/NightStandCommandHandler.cpp
    app/src/CommandHandler/SpeakerCommandHandler.cpp

    app/src/Entity/Alarm.cpp
    app/src/Entity/Train.cpp

    app/src/Kernel/Client.cpp
    app/src/Kernel/Server.cpp

    app/src/Utils/commandSplitter.cpp
    app/src/Utils/responses.cpp

    app/src/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${PROJECT_SOURCE_DIR}/app/include
)