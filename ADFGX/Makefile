MAIN = encrypt decrypt

HEADERS = $(CRYPTOLIB_DIR)/*.h

# House-keeping build targets.

all : $(MAIN)
tests : $(TESTS)

clean :
	rm -f $(MAIN) $(TESTS) gtest.a gtest_main.a *.o

%: %.cpp
	$(CXX) -g -o $@ $<


