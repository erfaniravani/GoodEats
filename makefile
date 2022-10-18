CC = g++
CCT = g++ -std=c++11
STD = -std=c++11 -Wall -pedantic
CF=$(STD)
BUILD_DIR = build
TEMPLATE_DIR = .template
SERVERFILES = server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp

all: $(BUILD_DIR) goodeats.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/template_parser.o: utils/template_parser.cpp utils/template_parser.hpp utils/request.cpp utils/request.hpp utils/utilities.hpp utils/utilities.cpp
	$(CC) $(CF) -c utils/template_parser.cpp -o $(BUILD_DIR)/template_parser.o

$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) $(CF) -c utils/response.cpp -o $(BUILD_DIR)/response.o

$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) $(CF) -c utils/request.cpp -o $(BUILD_DIR)/request.o

$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) $(CF) -c utils/utilities.cpp -o $(BUILD_DIR)/utilities.o

$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp utils/template_parser.hpp utils/template_parser.cpp
	$(CC) $(CF) -c server/server.cpp -o $(BUILD_DIR)/server.o

$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/route.cpp -o $(BUILD_DIR)/route.o




$(BUILD_DIR)/handlers.o: src/handlers.cpp src/handlers.hpp src/website.hpp src/defines.hpp src/exceptions.hpp $(SERVERFILES)
	$(CC) $(CF) -c src/handlers.cpp -o $(BUILD_DIR)/handlers.o

$(BUILD_DIR)/my_server.o: src/my_server.cpp src/my_server.hpp $(SERVERFILES)
	$(CC) $(CF) -c src/my_server.cpp -o $(BUILD_DIR)/my_server.o

$(BUILD_DIR)/main.o: src/main.cpp src/my_server.hpp src/handlers.hpp src/website.hpp src/exceptions.hpp src/defines.hpp $(SERVERFILES)
	$(CCT) -c src/main.cpp -o $(BUILD_DIR)/main.o



$(BUILD_DIR)/website.o: src/website.hpp src/website.cpp src/recipe.hpp src/member.hpp src/filter.hpp src/shelf.hpp src/exceptions.hpp src/defines.hpp
	$(CCT) -c src/website.cpp -o $(BUILD_DIR)/website.o

$(BUILD_DIR)/filter.o: src/filter.hpp src/filter.cpp src/recipe.hpp src/exceptions.hpp src/defines.hpp src/member.hpp
	$(CCT) -c src/filter.cpp -o $(BUILD_DIR)/filter.o

$(BUILD_DIR)/member.o: src/member.hpp src/member.cpp src/defines.hpp src/exceptions.hpp src/recipe.hpp
	$(CCT) -c src/member.cpp -o $(BUILD_DIR)/member.o

$(BUILD_DIR)/recipe.o: src/recipe.hpp src/recipe.cpp src/defines.hpp src/exceptions.hpp
	$(CCT) -c src/recipe.cpp -o $(BUILD_DIR)/recipe.o

$(BUILD_DIR)/shelf.o: src/shelf.hpp src/shelf.cpp src/defines.hpp src/exceptions.hpp
	$(CCT) -c src/shelf.cpp -o $(BUILD_DIR)/shelf.o

goodeats.out: $(BUILD_DIR)/my_server.o $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o $(BUILD_DIR)/website.o $(BUILD_DIR)/member.o $(BUILD_DIR)/shelf.o $(BUILD_DIR)/filter.o $(BUILD_DIR)/recipe.o
	$(CC) $(CF) $(BUILD_DIR)/my_server.o $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o $(BUILD_DIR)/website.o $(BUILD_DIR)/member.o $(BUILD_DIR)/shelf.o $(BUILD_DIR)/filter.o $(BUILD_DIR)/recipe.o -o goodeats.out

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(TEMPLATE_DIR) *.o *.out &> /dev/null
