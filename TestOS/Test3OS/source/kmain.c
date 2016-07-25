/***************************************************************************************************************
 Name: kmain.c
 Description: This is the starting point for the c code of the kernel. This will be called by the loader
 References: http://littleosbook.github.io/#getting-to-c
 Date: 6/10/2016
****************************************************************************************************************/
#include "iodisplay.h"
#include "string_functions.h"

int main()
{
	/*char *test = "asflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;l\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;ljlasfaf\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljs\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nasflkjalskjalsfjlasfjljasl;fkjalsfjlaskjfljasfl;jlsfj;lasjf;ljslfjl;asfl;jl;lj\nThis is my test string.";
	int nlen = string_length(test);*/

	init_console();
	//puts(test, nlen);
	return 0xF00DCAFE;			//Passing this value to verify whether call to main was successfull. after return EAX register should have this value.

}
