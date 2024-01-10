// #include <iostream>
// #include "Instructor.h"
// #include "Lesson.h"

// #define RESET   "\033[0m"
// #define BLUE    "\033[34m"
// #define PURPLE  "\033[35m"
// #define RED     "\033[31m"      

// int main()
// {
// 	Instructor instructor1("Krutiy", "+38(063)8651819", 300.0);
// 	Instructor instructor2("Stetsyk", "+38(096)5631589", 300.0);
// 	Instructor instructor3("Yakhno", "+38(095)7834967", 350.0);
// 	Instructor instructor4("Dovzhanskyi", "+38(067)6145363", 300.0);
// 	Instructor instructor5("Shira", "+38(063)3255133", 350.0);
// 	Instructor instructor6("Kolchak", "+38(067)1345840", 300.0);
// 	Instructor instructor7("Panchyshyn", "+38(067)7462681", 300.0);
// 	Instructor instructor8("Hrynenko", "+38(050)5560642", 300.0);
// 	Instructor instructor9("Kinash", "+38(099)4884404", 400.0);

// 	std::cout << BLUE << "25 METER POOL SCHEDULE\n\n" << RESET;
// 	std::cout << RED << "FOR YOUTH DEVELOPMENT " << RESET << "Empowering young people to reach their full potential\n";
// 	std::cout << RED << "FOR HEALTHY LIVING " << RESET << "Improving individual and community well-being\n";
// 	std::cout << RED << "FOR SOCIAL RESPONSIBILITY " << RESET << "Providing support and inspiring action in our communities\n\n";
// 	std::cout << "Choose one of the following options:\n";
// 	std::cout << "1. " << std::endl;
// 	std::cout << "2. " << std::endl;
// 	std::cout << "3. " << std::endl;
// 	std::cout << "4. " << std::endl;
// 	std::cout << "5. Exit" << std::endl;
// }


/* Мета: написати програму для автоматизації обліку роботу басейна. У басейна є 3 плавальні доріжки. На кожній з доріжок в окремий момент часу може працювати тільки один тренер з певною групою. Кількість осіб в групі обмежена. Для простоти припустимо числом 10. Потрібно розробити програму, яка б дозволяла формувати розклад роботи тренера. Припустимо, що заклад працює з 9:00 до 21:00 за київським часом, кожного дня, крім неділі. Але окремий тренер може працювати якусь певну кількість годин і днів з цього часу. Потім його може змінити інший тренер. Потрібно створити список тренерів з прізвищами, номерами телефонів, ставками погодинної оплати і розкладом занять.

В розкладі занять має бути вказано номер доріжки, час проведення занять і група. Має бути можливість формування зведеного розкладу по всіх доріжках, тренерах, групах. Має бути можливість створення і вилучення нових груп і додавання й вилучення дітей, які займаються плаванням. В кожного учасника групи має бути ім’я, ім’я одного з батьків, контактний номер телефона, обсяг проплачених коштів і прив’язка до певного списку занять. Потрібно розробити можливість пошуку учасника за контактним номером телефона і вивід на екран розкладу занять на тиждень для нього.

Для виконання завдання можете використовувати будь-які структури даних. Але результати треба буде зберігати у файл до наступного запуска програми.

У вас мають бути наступні класи і об’єкти:
1. Доріжки мають номер і список занять.
2. Заняття характеризується часом, номером доріжки, тренером і групою.
3. Тренер має прізвище, номер телефону, погодинна ставка і пов’язаний із списком занять.
4. Група має номер і список учнів, пов’язана із заняттями.
5. Учень має прізвище, прізвище, ім’я одного з батьків, контактний номер телефона і кількість проплачених занять. */

// General libraries
#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <string>
#include <iomanip>
// #include <vector>
#include <sstream>

 // Specific libs
 #include "Lesson.h"
 #include "Instructor.h"

using namespace std;
string textToSave;
stringstream buffer;

// Tool Function 1 | Save the latest console output, even the program closed or stopped abruptly.
void save_file() {
  ofstream myfile;
  myfile.open ("GeneralPoolSchedule.txt");
  myfile << textToSave;
  myfile.close();
}

// // Tool Function 2
// void printAndSave(string _text) {
//   cout << _text;
//   textToSave = _text;
// }

// Tool Function 2 
void printSchedule(bool generalized, bool particularTrack, bool particularGroup, bool particularPerson) {
  system("CLS");

  if (generalized) buffer << "\nPrinting the generalized schedule.\n";
  if (particularTrack) buffer << "\nPrinting the schedule for the particular track.\n";
  if (particularGroup) buffer << "\nPrinting the schedule for the particular group.\n";
  if (particularPerson) buffer << "\nPrinting the schedule for the particular person.\n";

  textToSave = buffer.str();
  std::cout << textToSave << '\n';
  buffer.str("");
}

// Tool Function 3
void groupAndStudentsManagement() {

}


// Tool Function 4
void printMsg(int _window, string _text = "", int _w2 = -1, int _w3 = -1, int _w4 = -1) {  // Функція, яка друкує конкретне вікно діалогу.
  SetConsoleOutputCP(1251);
  SetConsoleCP(1251);

  switch (_window) {
  case 0: 
      cout << string(32, '=') << " Pool Schedule Accounting Application " << string(32, '=') << endl;
      printMsg(17, "a");  printMsg(18, "Print the generalized schedule across all the tracks, trainers and groups."); 
      printMsg(17, "b");  printMsg(18, "Print the schedule for the particular track or group."); 
      printMsg(17, "c");  printMsg(18, "Find and print the schedule for the particular trainer or student."); 
      printMsg(17, "d");  printMsg(18, "Modify/create groups. Add/remove students to/from the group."); 
      break;

  case 1: cout << string(50, '=') << endl; printSchedule(1,0,0,0); break;
  case 2: cout << string(50, '=') << endl; printSchedule(0,1,1,0); break;
  case 3: cout << string(50, '=') << endl; printSchedule(0,0,0,1); break;
  case 4: cout << string(50, '=') << endl; groupAndStudentsManagement(); break;
  case 17: cout << string(100, '-') << endl << setw(2) << left << "|" << setw(4) << _text ;; break;
  case 18: cout << setw(2) << left << "|" << setw(90) << _text << setw(2) << right << "|" << endl; break;
  case 19: cout << "\nYou have pressed the key \"" << _text <<"\". There is no such option in this menu. Please try again.\n\n"; break;
  case 20: 
    printMsg(17, "TAB"); printMsg(18, "Back to the main menu."); 
    printMsg(17, "ESC"); printMsg(18, "Exit the program."); cout << string(100, '-'); break;
  default: break;
  }
  if (_w2 != -1) printMsg(_w2); if (_w3 != -1) printMsg(_w3); if (_w4 != -1) printMsg(_w4);
}

int main() {
  std::atexit(save_file);
  SetConsoleOutputCP(1251);
  SetConsoleCP(1251);

  char qt; 
  bool run = true, inOption = false;

  system("CLS");
  printMsg(0, "", 20); 
  while (run) {
    if (_kbhit()) {
      system("CLS");
      qt = _getch();
      switch (qt) {
        // decimal 9 - "TAB" as char (ASCII) | Go back to the main menu.
        case(9): printMsg(0, "", 20); inOption = false;
          break; 
        // decimal 27 - "ESCAPE" as char (ASCII) | Exit Program.
        case(27): return 0; break;           

        // decimal 97 - "a" as char (ASCII) | Print generalized schedule.
        case(97): 
          if (inOption) printMsg(19, string(1, qt), 20); 
          else { printMsg(1, "", 20); inOption = true; }
          break; 
        // decimal 98 - "b" as char (ASCII) | Print the schedule for the particular track or group.
        case(98): 
          if (inOption) printMsg(19, string(1, qt), 20); 
          else { printMsg(2, "", 20); inOption = true; }
          break; 
        // decimal 99 - "c" as char (ASCII) | Print the schedule for the particular trainer or student.
        case(99): 
          if (inOption) printMsg(19, string(1, qt), 20); 
          else { printMsg(3, "", 20); inOption = true; }
          break; 
        // decimal 100 - "d" as char (ASCII) | Modify/create groups. Add/remove students to/from the group.
        case(100): 
          if (inOption) printMsg(19, string(1, qt), 20); 
          else { printMsg(4, "", 20); inOption = true; }
          break; 
    
        default: 
          printMsg(19, string(1, qt), 20); 
          break;
      }
      // cout << qt;
    }
  } run = true;
}