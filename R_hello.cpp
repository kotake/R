#include <RInside.h> 

int main(int argc, char *argv[]) {
RInside R(argc, argv); 
R["txt"] = "Hello, world!\n"; 
R.parseEvalQ("cat(txt)"); 
exit(0);
}
