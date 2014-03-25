PROBLEMS=1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 18 19
PROBLEMS+=20 21 22 23 24 25 27 28 29
PROBLEMS+=30 31
PROBLEMS+=48
PROBLEMS+=67

#used when working with a problem. compile/link only this one
#PROBLEMS=48

#HELPING VARS
PROB_NAMES=$(addprefix problem,$(PROBLEMS))
PROB_DIRS=$(addsuffix /,$(PROB_NAMES))

#EXPANDED FILENAMES
DEP_SRC= euler.cpp results.cpp $(join $(PROB_DIRS),$(addsuffix .cpp,$(PROB_NAMES)))
#no header files needed for now
DEP_HDR=#$(patsubst %.cpp,%.h,$(DEP_SRC))
DEP_OBJ=$(patsubst %.cpp,%.o,$(DEP_SRC))
DEP_DESC=$(patsubst %.cpp,%.d,$(DEP_SRC))

#COMPILE VARS
CXX=g++-4.8 #set the compiler to be used
CXXFLAGS+=-std=c++11 #compile enabling the new c++ standard
CXXFLAGS+=-march=native #Build architecture set to the current machine's architecture
CXXFLAGS+=-Wall -Wextra -pedantic #enable all warnings
CXXFLAGS+=-O4
CXXFLAGS+=-fpic
#CXXFLAGS+=-flto #link time optimization
#CXXFLAGS+=-fwhole-program #gcc optimization
#CXXFLAGS+= -g #include debugging symbols

LDFLAGS += -Wl,--no-as-needed # to work around a ubuntu 13.10 bug
LDFLAGS += -fuse-linker-plugin -pthread #include threading library

#custom rules
#makefile driver creation rules (suppress creation message)
%.d: %.cpp
	@$(CXX) $(CXXFLAGS) $< -MM -MF $@

#TARGETS

euler: $(DEP_OBJ)
	$(CXX) $(CXXFLAGS) $(DEP_OBJ) -o $@ $(LDFLAGS)

.PHONY: clear run
clear:
	$(RM) euler $(DEP_OBJ) $(DEP_DESC) 

run: euler
	./euler

memtest: CXXFLAGS=-march=native -std=c++11 -Wall -Wextra -g
memtest: clear euler
	valgrind --read-var-info=yes -q ./euler

debug: CXXFLAGS=-march=native -std=c++11 -Wall -Wextra -g
debug: clear euler
	gdb --quiet -ex=run ./euler

-include $(DEP_DESC)
-include euler.d

