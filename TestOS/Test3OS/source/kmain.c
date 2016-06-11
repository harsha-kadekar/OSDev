/***************************************************************************************************************
 Name: kmain.c
 Description: This is the starting point for the c code of the kernel. This will be called by the loader
 References: http://littleosbook.github.io/#getting-to-c
 Date: 6/10/2016
****************************************************************************************************************/

int main()
{
	return 0xF00DCAFE;			//Passing this value to verify whether call to main was successfull. after return EAX register should have this value.
}
