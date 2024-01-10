#include <iostream>
#include "Instructor.h"
#include "Lesson.h"

#define RESET   "\033[0m"
#define BLUE    "\033[34m"
#define PURPLE  "\033[35m"
#define RED     "\033[31m"      

int main()
{
	Instructor instructor1("Krutiy", "+38(063)8651819", 300.0);
	Instructor instructor2("Stetsyk", "+38(096)5631589", 300.0);
	Instructor instructor3("Yakhno", "+38(095)7834967", 350.0);
	Instructor instructor4("Dovzhanskyi", "+38(067)6145363", 300.0);
	Instructor instructor5("Shira", "+38(063)3255133", 350.0);
	Instructor instructor6("Kolchak", "+38(067)1345840", 300.0);
	Instructor instructor7("Panchyshyn", "+38(067)7462681", 300.0);
	Instructor instructor8("Hrynenko", "+38(050)5560642", 300.0);
	Instructor instructor9("Kinash", "+38(099)4884404", 400.0);

	std::cout << BLUE << "25 METER POOL SCHEDULE\n\n" << RESET;
	std::cout << RED << "FOR YOUTH DEVELOPMENT " << RESET << "Empowering young people to reach their full potential\n";
	std::cout << RED << "FOR HEALTHY LIVING " << RESET << "Improving individual and community well-being\n";
	std::cout << RED << "FOR SOCIAL RESPONSIBILITY " << RESET << "Providing support and inspiring action in our communities\n\n";
	std::cout << "Choose one of the following options:\n";
	std::cout << "1. " << std::endl;
	std::cout << "2. " << std::endl;
	std::cout << "3. " << std::endl;
	std::cout << "4. " << std::endl;
	std::cout << "5. Exit" << std::endl;
}
