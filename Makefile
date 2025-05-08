# This Makefile provides you with quick access to usefule commands

PORT = 8080
BUILD_DIR = build
TRANSITE_EXE = $(BUILD_DIR)/bin/transit_service

.PHONY: all web service transit_service clean run debug docs lint lintQ

# default behaviour is to compile the project
all: transit_service

# compiles both the web and service part of the project
transit_service: web service

# front-end of project, install node_modules if not found, then runs npm run build to compile front-end
web:
ifeq ($(wildcard web/node_modules/.),)
	cd web; npm install; cd ..;
endif
	cd web; npm run build; cd ..

# back-end of project, runs the Makefile within the service folder
service:
	$(MAKE) -C service

# quick shortcut to run the project, will not recompile project if changes had been made
# you can change port with PORT={port}, ex: make run PORT=8090
run:
ifeq (,$(wildcard $(TRANSITE_EXE)))
	$(MAKE) -j
endif
	./$(TRANSITE_EXE) $(PORT) web/dist

# shortcut to run gdb for debugging, will recompile if changes were made
debug: transit_service
	gdb --args ./$(TRANSITE_EXE) $(PORT) web/dist

# cleans up the build directory
clean:
	rm -rf $(BUILD_DIR)

# generates doxygen files
docs:
	cd docs; doxygen Doxyfile; cd ..;

# runs clang-format
lint:
	clang-format -style=Google -i $(shell find ./service/include/simulationmodel/ ./service/src/simulationmodel/ -type f -name '*.cc' -o -name '*.h') 