# this Makefile was generated automatically by generic-makefile

.PHONY : target
target : banner ./output/bin.out
	
	
./output/bin.out : ./src/main.cpp  ./tmp/libproject.a
	@echo "\tCompiling binary."
	@mkdir -p ./output
	@g++ ./src/main.cpp -Wpedantic -L vlc -I ./src -I ./src/Entity -I ./src/Entity/Train -I ./src/Entity/Alarm -I ./src/CommandHandler -I ./src/CommandHandler/AlarmCommandHandler -I ./src/Kernel -I ./src/Kernel/Server -I ./src/Kernel/Client -I ./src/Controller -I ./src/Controller/WeatherController -I ./src/Controller/TrainController -I ./src/Controller/AlarmController -I ./src/Utils -I ./src/shared  -o ./output/bin.out ./tmp/libproject.a 
	
	
.PHONY : run
run : ./output/bin.out
	@echo "\tExecuting binary.\n"
	@time "./output/bin.out" 


./tmp/libproject.a : ./tmp/Entity/Train/Train.o ./tmp/Entity/Alarm/Alarm.o ./tmp/CommandHandler/AlarmCommandHandler/AlarmCommandHandler.o ./tmp/CommandHandler/CommandHandler.o ./tmp/Kernel/Server/Server.o ./tmp/Kernel/Client/Client.o ./tmp/Controller/WeatherController/WeatherController.o ./tmp/Controller/TrainController/TrainController.o ./tmp/Controller/AlarmController/AlarmController.o ./tmp/Utils/CommandSplitter.o 
	@echo "\tBuilding project library."
	@ar -rsc ./tmp/libproject.a ./tmp/Entity/Train/Train.o ./tmp/Entity/Alarm/Alarm.o ./tmp/CommandHandler/AlarmCommandHandler/AlarmCommandHandler.o ./tmp/CommandHandler/CommandHandler.o ./tmp/Kernel/Server/Server.o ./tmp/Kernel/Client/Client.o ./tmp/Controller/WeatherController/WeatherController.o ./tmp/Controller/TrainController/TrainController.o ./tmp/Controller/AlarmController/AlarmController.o ./tmp/Utils/CommandSplitter.o 


./tmp/Entity/Train/Train.o : ./src/Entity/Train/Train.cpp ./src/Entity/Train/Train.hpp
	@echo "\tPrecompiling object for ./src/Entity/Train/Train.cpp."
	@mkdir -p ./tmp/Entity/Train
	@g++ -c ./src/Entity/Train/Train.cpp -I ./src -I ./src/Entity -I ./src/Entity/Train -I ./src/Entity/Alarm -I ./src/CommandHandler -I ./src/CommandHandler/AlarmCommandHandler -I ./src/Kernel -I ./src/Kernel/Server -I ./src/Kernel/Client -I ./src/Controller -I ./src/Controller/WeatherController -I ./src/Controller/TrainController -I ./src/Controller/AlarmController -I ./src/Utils -I ./src/shared  -o ./tmp/Entity/Train/Train.o;


./tmp/Entity/Alarm/Alarm.o : ./src/Entity/Alarm/Alarm.cpp ./src/Entity/Alarm/Alarm.hpp
	@echo "\tPrecompiling object for ./src/Entity/Alarm/Alarm.cpp."
	@mkdir -p ./tmp/Entity/Alarm
	@g++ -c ./src/Entity/Alarm/Alarm.cpp -I ./src -I ./src/Entity -I ./src/Entity/Train -I ./src/Entity/Alarm -I ./src/CommandHandler -I ./src/CommandHandler/AlarmCommandHandler -I ./src/Kernel -I ./src/Kernel/Server -I ./src/Kernel/Client -I ./src/Controller -I ./src/Controller/WeatherController -I ./src/Controller/TrainController -I ./src/Controller/AlarmController -I ./src/Utils -I ./src/shared  -o ./tmp/Entity/Alarm/Alarm.o;


./tmp/CommandHandler/AlarmCommandHandler/AlarmCommandHandler.o : ./src/CommandHandler/AlarmCommandHandler/AlarmCommandHandler.cpp ./src/CommandHandler/AlarmCommandHandler/AlarmCommandHandler.hpp
	@echo "\tPrecompiling object for ./src/CommandHandler/AlarmCommandHandler/AlarmCommandHandler.cpp."
	@mkdir -p ./tmp/CommandHandler/AlarmCommandHandler
	@g++ -c ./src/CommandHandler/AlarmCommandHandler/AlarmCommandHandler.cpp -I ./src -I ./src/Entity -I ./src/Entity/Train -I ./src/Entity/Alarm -I ./src/CommandHandler -I ./src/CommandHandler/AlarmCommandHandler -I ./src/Kernel -I ./src/Kernel/Server -I ./src/Kernel/Client -I ./src/Controller -I ./src/Controller/WeatherController -I ./src/Controller/TrainController -I ./src/Controller/AlarmController -I ./src/Utils -I ./src/shared  -o ./tmp/CommandHandler/AlarmCommandHandler/AlarmCommandHandler.o;


./tmp/CommandHandler/CommandHandler.o : ./src/CommandHandler/CommandHandler.cpp ./src/CommandHandler/CommandHandler.hpp
	@echo "\tPrecompiling object for ./src/CommandHandler/CommandHandler.cpp."
	@mkdir -p ./tmp/CommandHandler
	@g++ -c ./src/CommandHandler/CommandHandler.cpp -I ./src -I ./src/Entity -I ./src/Entity/Train -I ./src/Entity/Alarm -I ./src/CommandHandler -I ./src/CommandHandler/AlarmCommandHandler -I ./src/Kernel -I ./src/Kernel/Server -I ./src/Kernel/Client -I ./src/Controller -I ./src/Controller/WeatherController -I ./src/Controller/TrainController -I ./src/Controller/AlarmController -I ./src/Utils -I ./src/shared  -o ./tmp/CommandHandler/CommandHandler.o;


./tmp/Kernel/Server/Server.o : ./src/Kernel/Server/Server.cpp ./src/Kernel/Server/Server.hpp
	@echo "\tPrecompiling object for ./src/Kernel/Server/Server.cpp."
	@mkdir -p ./tmp/Kernel/Server
	@g++ -c ./src/Kernel/Server/Server.cpp -I ./src -I ./src/Entity -I ./src/Entity/Train -I ./src/Entity/Alarm -I ./src/CommandHandler -I ./src/CommandHandler/AlarmCommandHandler -I ./src/Kernel -I ./src/Kernel/Server -I ./src/Kernel/Client -I ./src/Controller -I ./src/Controller/WeatherController -I ./src/Controller/TrainController -I ./src/Controller/AlarmController -I ./src/Utils -I ./src/shared  -o ./tmp/Kernel/Server/Server.o;


./tmp/Kernel/Client/Client.o : ./src/Kernel/Client/Client.cpp ./src/Kernel/Client/Client.hpp
	@echo "\tPrecompiling object for ./src/Kernel/Client/Client.cpp."
	@mkdir -p ./tmp/Kernel/Client
	@g++ -c ./src/Kernel/Client/Client.cpp -I ./src -I ./src/Entity -I ./src/Entity/Train -I ./src/Entity/Alarm -I ./src/CommandHandler -I ./src/CommandHandler/AlarmCommandHandler -I ./src/Kernel -I ./src/Kernel/Server -I ./src/Kernel/Client -I ./src/Controller -I ./src/Controller/WeatherController -I ./src/Controller/TrainController -I ./src/Controller/AlarmController -I ./src/Utils -I ./src/shared  -o ./tmp/Kernel/Client/Client.o;


./tmp/Controller/WeatherController/WeatherController.o : ./src/Controller/WeatherController/WeatherController.cpp ./src/Controller/WeatherController/WeatherController.hpp
	@echo "\tPrecompiling object for ./src/Controller/WeatherController/WeatherController.cpp."
	@mkdir -p ./tmp/Controller/WeatherController
	@g++ -c ./src/Controller/WeatherController/WeatherController.cpp -I ./src -I ./src/Entity -I ./src/Entity/Train -I ./src/Entity/Alarm -I ./src/CommandHandler -I ./src/CommandHandler/AlarmCommandHandler -I ./src/Kernel -I ./src/Kernel/Server -I ./src/Kernel/Client -I ./src/Controller -I ./src/Controller/WeatherController -I ./src/Controller/TrainController -I ./src/Controller/AlarmController -I ./src/Utils -I ./src/shared  -o ./tmp/Controller/WeatherController/WeatherController.o;


./tmp/Controller/TrainController/TrainController.o : ./src/Controller/TrainController/TrainController.cpp ./src/Controller/TrainController/TrainController.hpp
	@echo "\tPrecompiling object for ./src/Controller/TrainController/TrainController.cpp."
	@mkdir -p ./tmp/Controller/TrainController
	@g++ -c ./src/Controller/TrainController/TrainController.cpp -I ./src -I ./src/Entity -I ./src/Entity/Train -I ./src/Entity/Alarm -I ./src/CommandHandler -I ./src/CommandHandler/AlarmCommandHandler -I ./src/Kernel -I ./src/Kernel/Server -I ./src/Kernel/Client -I ./src/Controller -I ./src/Controller/WeatherController -I ./src/Controller/TrainController -I ./src/Controller/AlarmController -I ./src/Utils -I ./src/shared  -o ./tmp/Controller/TrainController/TrainController.o;


./tmp/Controller/AlarmController/AlarmController.o : ./src/Controller/AlarmController/AlarmController.cpp ./src/Controller/AlarmController/AlarmController.hpp
	@echo "\tPrecompiling object for ./src/Controller/AlarmController/AlarmController.cpp."
	@mkdir -p ./tmp/Controller/AlarmController
	@g++ -c ./src/Controller/AlarmController/AlarmController.cpp -I ./src -I ./src/Entity -I ./src/Entity/Train -I ./src/Entity/Alarm -I ./src/CommandHandler -I ./src/CommandHandler/AlarmCommandHandler -I ./src/Kernel -I ./src/Kernel/Server -I ./src/Kernel/Client -I ./src/Controller -I ./src/Controller/WeatherController -I ./src/Controller/TrainController -I ./src/Controller/AlarmController -I ./src/Utils -I ./src/shared  -o ./tmp/Controller/AlarmController/AlarmController.o;


./tmp/Utils/CommandSplitter.o : ./src/Utils/CommandSplitter.cpp ./src/Utils/CommandSplitter.hpp
	@echo "\tPrecompiling object for ./src/Utils/CommandSplitter.cpp."
	@mkdir -p ./tmp/Utils
	@g++ -c ./src/Utils/CommandSplitter.cpp -I ./src -I ./src/Entity -I ./src/Entity/Train -I ./src/Entity/Alarm -I ./src/CommandHandler -I ./src/CommandHandler/AlarmCommandHandler -I ./src/Kernel -I ./src/Kernel/Server -I ./src/Kernel/Client -I ./src/Controller -I ./src/Controller/WeatherController -I ./src/Controller/TrainController -I ./src/Controller/AlarmController -I ./src/Utils -I ./src/shared  -o ./tmp/Utils/CommandSplitter.o;


.PHONY : googletest banner
googletest : banner   


./tmp/libgtest.a : ./tmp/gtest_main.o ./tmp/gtest-all.o
	@echo "\tCompiling googletest library."
	@ar -rc ./tmp/libgtest.a ./tmp/gtest-all.o ./tmp/gtest_main.o


./tmp/gtest_main.o : ./make-files/googletest/googletest/src/gtest_main.cc
	@echo "\tPrecompiling googletest object for ./make-files/googletest/googletest/src/gtest_main.cc."
	@mkdir -p ./tmp
	@g++ -isystem ./make-files/googletest/googletest/include -I ./make-files/googletest/googletest -pthread -c ./make-files/googletest/googletest/src/gtest_main.cc -o ./tmp/gtest_main.o

./tmp/gtest-all.o : ./make-files/googletest/googletest/src/gtest-all.cc
	@echo "\tPrecompiling googletest object for ./make-files/googletest/googletest/src/gtest-all.cc"
	@mkdir -p ./tmp
	@g++ -isystem ./make-files/googletest/googletest/include -I ./make-files/googletest/googletest -pthread -c ./make-files/googletest/googletest/src/gtest-all.cc -o ./tmp/gtest-all.o


.PHONY : banner
banner :
	@cat ./make-files/fancy_banner_short.txt


.PHONY : help
help:
	@cat ./make-files/banner.txt
	@cat ./make-files/help.txt


.PHONY : clean
clean:
	@echo "\tRemoving temporal files"
	@if [ -d "./tmp" ]; then rm -rf ./tmp; fi
	@echo "\tRemoving binary files"
	@if [ -d "./output/*.out" ]; then rm ./output/*.out; fi


.PHONY : init-gest
init-gest:
	@echo "\tClonning googletest to make-files"
	@if [ -d "make-files/googletest" ]; then \
		echo "googletest is already cloned"; \
	else \
		git clone https://github.com/google/googletest.git make-files/googletest; \
		rm ./make-files/googletest/googletest/.git -rf; \
	fi;


.PHONY : rm-gest
rm-gest:
	@echo "\tRemoving googletest repository"
	@if [ -d "make-files/googletest" ]; then \
		rm make-files/googletest -rf; \
	fi;

#    __
# __( o)>
# \ <_ ) r90
