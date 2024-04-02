.PHONY : all clean test
#target setup
target_name = matrix 
headers_name = matrix 

#dirs setup
src_dir := sources/
header_dir := sources/
build_dir := bin/
test_dir := tests/

#CC setup
CC := clang++
debug_flags := -fsanitize=address -fsanitize=undefined -fsanitize=leak
	

#declaring a dependences 
target := $(addprefix $(src_dir), $(target_name)) 
target := $(addsuffix .cpp, $(target))

objects := $(addprefix $(build_dir), $(target_name))
objects := $(addsuffix .o, $(objects))

headers := $(addprefix $(header_dir), $(headers_name)) 
headers := $(addsuffix .h, $(headers)) 



all : $(build_dir) $(objects)

$(build_dir) : 
	mkdir $(build_dir)


$(objects) : $(build_dir)%.o : $(target) $(headers) 
	$(CC) -c $(src_dir)$*.cpp  -o  $(build_dir)$*.o


#test setup
test_src := $(wildcard $(test_dir)*.cpp)
test_files := $(test_src:.cpp=.out)


test : $(test_files) 
	@echo "All test passed"

$(test_files) : %.out: $(target) $(headers) $(objects)  $(test_src)
	$(CC) $*.cpp $(objects) -o $*.out -lgtest -lgtest_main $(debug_flags)
	$*.out


clean : 
	rm -f $(objects)
	rm -f $(test_files)