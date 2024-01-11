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
//#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
#include <fstream>
#include <memory>
#include <windows.h>
#include <conio.h>
#include <string>
#include <iomanip>
#include <sstream>

// Specific libs
#include "Lane.h"
#include "Instructor.h"
#include "Group.h"

using namespace std;

#define RESET   "\033[0m"
#define BLUE    "\033[34m"
#define PURPLE  "\033[35m"
#define RED     "\033[31m"

string textToSave;
stringstream buffer;
std::vector<std::unique_ptr<Lane>> allLanes;
std::vector<std::unique_ptr<Group>> allGroups;
std::vector<std::unique_ptr<Instructor>> allInstructors;

// Tool Function 1 | Save the console output, even the program closed or stopped abruptly.
void save_file() {
  ofstream myfile;                    // Create the file object.

  // This block of code is used to get the current system timestamp into "timestamp".
  struct tm time;
  __time32_t aclock;
  char timestamp[32];
  _time32( &aclock );                 // Get time in seconds.
  _localtime32_s( &time, &aclock );   // Convert time to struct tm form.

  // This line makes the timestamp in the format "2024_11_01__17_11_07".
  strftime(timestamp, sizeof(timestamp), "%Y_%d_%m__%H_%M_%S", &time);
  myfile.open("schedule_search_history."+string(timestamp)+".txt");

  // This line makes the timestamp in the format "18 Sep 2023 15:14:32".
  strftime(timestamp, sizeof(timestamp), " %d %b %Y %H:%M:%S", &time);
  myfile << string(8, '/') << timestamp << " | Pool schedule search history " << string(8, '\\') << endl;

  myfile << textToSave;
  myfile.close();
}

// Tool Function 2
void printMsg(int _window, string _text = "", int _w2 = -1, int _w3 = -1, int _w4 = -1) {  // Функція, яка друкує конкретне вікно діалогу.
  SetConsoleOutputCP(1251);
  SetConsoleCP(1251);

  switch (_window) {
  case 0: 
    printMsg(16, " Pool Schedule Accounting Application ");
    printMsg(17, "a");  printMsg(18, "Print the generalized schedule across all the tracks, instructors and groups."); 
    printMsg(17, "b");  printMsg(18, "Print the schedule for the particular track or group."); 
    printMsg(17, "c");  printMsg(18, "Find and print the schedule for the particular instructor or student."); 
    printMsg(17, "d");  printMsg(18, "Create/modify group. Add/remove student to/from the group."); break;
  case 4: 
    printMsg(16, " Groups and students management ");
    printMsg(17, "1");  printMsg(18, "Print list of all the students and groups."); 
    printMsg(17, "2");  printMsg(18, "Add the student and assign it to the group."); 
    printMsg(17, "3");  printMsg(18, "Remove the student from the group."); break;
  // case 7: printMsg(17, "3");  printMsg(18, "."); 
  case 15: buffer << endl << string(30, '=') << setw(50) << left << _text << string(30, '=') << endl; textToSave.append(buffer.str()); break;
  case 16: cout << string(30, '=') << setw(40) << left << _text << string(30, '=') << endl; break;
  case 17: cout << string(100, '-') << endl << setw(2) << left << "|" << setw(4) << _text ;; break;
  case 18: cout << setw(2) << left << "|" << setw(90) << _text << setw(2) << right << "|" << endl; break;
  case 19: cout << "\nYou have pressed the key \"" << _text <<"\". There is no such option in this menu. Please try again.\n\n"; break;
  case 20: 
    printMsg(17, "TAB"); printMsg(18, "Back to the previous menu."); 
    printMsg(17, "ESC"); printMsg(18, "Exit the program."); cout << string(100, '-'); break;
  default: break;
  }
  if (_w2 != -1) printMsg(_w2); if (_w3 != -1) printMsg(_w3); if (_w4 != -1) printMsg(_w4);
}

// Tool Function 3
void printSchedule(bool generalized, bool particularTrack, bool particularGroup, bool particularPerson) {
  system("CLS");

  if (generalized) printMsg(15, " Printing the generalized schedule. ");
  
  if (particularTrack) printMsg(15, " Printing the schedule for the particular track. ");

  if (particularGroup) printMsg(15, " Printing the schedule for the particular group. ");

  if (particularPerson) printMsg(15, " Printing the schedule for the particular person. ");

  textToSave.append(buffer.str());
  cout << buffer.str();
  buffer.str("");
}

// Tool Function 4 | If "tui" (terminal-user-interface) is false, then only add/remove the student and end.
// void manageGroups(bool _tui, unique_ptr<Student> _student=nullptr, unique_ptr<Group> _group=nullptr, bool add=true) {
void manageGroups(bool _tui, unique_ptr<Student> _student=nullptr, bool add=true) {

  if (!_tui) {
    // Here would be code on how to add the student to the group right away, without dialog, that's when the "bool = _tui = true"
    return;
  }

  char qt; 
  bool run = true, inOption = false;
  system("CLS");
  printMsg(4, "", 20); 
  while (run) {
    if (_kbhit()) {
      system("CLS");
      qt = _getch();
      // cout << "\nGRP MANAGE | strin(1, qt) = " << string(1, qt) << endl;
      // cout << "\nGRP MANAGE | qt = " << qt << endl;
      switch (qt) {
        case(9):                       // decimal 9 - "TAB" as char (ASCII) | Go back to the previous menu.
          if (inOption) { inOption=false; printMsg(4, "", 20); } 
          else return; break; 
        case(27): std::exit(0); break; // decimal 27 - "ESCAPE" as char (ASCII) | Exit Program.

        case(49):                      // decimal 49 - "1" as char (ASCII) | Print all students,all groups.
          if (inOption) printMsg(19, string(1, qt), 20); 
          else {  
            // buffer << string(8, '=') << "Printing all students from all the groups" << string(8, '=') << endl;
            printMsg(15, " Printing all students from all the groups ");
            // textToSave.append(buffer.str());
            cout << buffer.str();
            buffer.str("");
            inOption = true; 
          } break; 
        
        default: 
          printMsg(19, string(1, qt), 20); 
          break;
      }
    }
  }

  return;
}

int main() {
  std::atexit(save_file);
  SetConsoleOutputCP(1251);
  SetConsoleCP(1251);

  // Create "Lane" objects.
  unique_ptr<Lane> lane1_ptr(new Lane(1));
  unique_ptr<Lane> lane2_ptr(new Lane(2));
  unique_ptr<Lane> lane3_ptr(new Lane(3));
  allLanes.push_back(std::move(lane1_ptr));
  allLanes.push_back(std::move(lane2_ptr));
  allLanes.push_back(std::move(lane3_ptr));

  // Create "Instructor" objects.
  unique_ptr<Instructor> instructor1_ptr(new Instructor("Krutiy", "+38(063)8651819", 300.0));
  unique_ptr<Instructor> instructor2_ptr(new Instructor("Stetsyk", "+38(096)5631589", 300.0));
  unique_ptr<Instructor> instructor3_ptr(new Instructor("Yakhno", "+38(095)7834967", 350.0));
  unique_ptr<Instructor> instructor4_ptr(new Instructor("Yakhno", "+38(095)7834967", 350.0));
  unique_ptr<Instructor> instructor5_ptr(new Instructor("Dovzhanskyi", "+38(067)6145363", 300.0));
  unique_ptr<Instructor> instructor6_ptr(new Instructor("Shira", "+38(063)3255133", 350.0));
  unique_ptr<Instructor> instructor7_ptr(new Instructor("Kolchak", "+38(067)1345840", 300.0));
  unique_ptr<Instructor> instructor8_ptr(new Instructor("Panchyshyn", "+38(067)7462681", 300.0));
  unique_ptr<Instructor> instructor9_ptr(new Instructor("Hrynenko", "+38(050)5560642", 300.0));
  unique_ptr<Instructor> instructor10_ptr(new Instructor("Kinash", "+38(099)4884404", 400.0));
  allInstructors.push_back(std::move(instructor1_ptr));
  allInstructors.push_back(std::move(instructor2_ptr));
  allInstructors.push_back(std::move(instructor3_ptr));
  allInstructors.push_back(std::move(instructor4_ptr));
  allInstructors.push_back(std::move(instructor5_ptr));
  allInstructors.push_back(std::move(instructor6_ptr));
  allInstructors.push_back(std::move(instructor7_ptr));
  allInstructors.push_back(std::move(instructor8_ptr));
  allInstructors.push_back(std::move(instructor9_ptr));
  allInstructors.push_back(std::move(instructor10_ptr));
  
  // Create "Group" objects.
  // unique_ptr<Group> group1_ptr(new Group(1));
  // auto group1_ptr = make_unique<Group>(1);
  // unique_ptr<Group> group2_ptr(new Group(2));
  // unique_ptr<Group> group3_ptr(new Group(3));
  // allGroups.push_back(std::move(group1_ptr));
  // allGroups.push_back(std::move(group2_ptr));
  // allGroups.push_back(std::move(group3_ptr));

  // Create "Student" objects.
                                              //  lastN, parentN, phoneN,     paidLessons
  // unique_ptr<Student> student1_ptr(new Student("Tichenko","Sharl","+38(730)7621483", 4));
  // auto orderBucket = make_unique<ShopOrder>();
  // auto student1_ptr = make_unique<Student>("Tichenko","Sharl","+38(730)7621483", 4);
  // shared_ptr<Student> student2_ptr(new Student("Chujkevych","Ustym","+380(884)8890726", 10));
  // shared_ptr<Student> student3_ptr(new Student("Pidoplichko","Emil","+380(248)8717477", 9));
  // shared_ptr<Student> student4_ptr(new Student("Ovrah","Jonas","+380(668)4952298", 8));
  // shared_ptr<Student> student5_ptr(new Student("Hrynishak","Fedir","+380(404)2303088", 3));
  // shared_ptr<Student> student6_ptr(new Student("Turkevych","Avrelii","+380(118)7284874", 4));
  // shared_ptr<Student> student7_ptr(new Student("Kompanec","Lyubodar ","+380(783)5566764", 2));

  // cout << "MAIN | student1_ptr.get()->getLastName()" << student1_ptr.get()->getLastName() << endl;
  // cout << "student2_ptr.get()->getLastName()" << student2_ptr.get()->getLastName() << endl;
  

  // manageGroups(0, std::move(student1_ptr), std::move(group1_ptr), 1);
  // manageGroups(0, std::move(student1_ptr), 1);
  // manageGroups(0, student2_ptr, group1_ptr, 1);
  // manageGroups(0, student3_ptr, group1_ptr, 1);
  // manageGroups(0, student4_ptr, group1_ptr, 1);
  // manageGroups(0, student5_ptr, group1_ptr, 1);
  // manageGroups(1, student2_ptr, group1_ptr, 1);
  // manageGroups(1, student3_ptr, group1_ptr, 1);
  // manageGroups(1, student4_ptr, group1_ptr, 1);
  // allGroups[1].get()->addStudentToGroup(student1_ptr);

  char qt; 
  bool run = true, inOption = false;

  //system("CLS");
  printMsg(0, "", 20); 
  while (run) {
    if (_kbhit()) {
      system("CLS");
      qt = _getch();
      switch (qt) {  // decimal 9 - "TAB" as char (ASCII) | Go back to the main menu.
        case(9): printMsg(0, "", 20); inOption = false; break; 
        case(27): return 0; break; // decimal 27 - "ESCAPE" as char (ASCII) | Exit Program.
        case(97):                  // decimal 97 - "a" as char (ASCII) | Print generalized schedule.
          if (inOption) printMsg(19, string(1, qt), 20); 
          else { printSchedule(1,0,0,0); printMsg(20); inOption = true; } break; 
        case(98): // decimal 98 - "b" as char (ASCII) | Print the schedule for the particular track or group. 
          if (inOption) printMsg(19, string(1, qt), 20); 
          else { printSchedule(0,1,1,0); inOption = true; } break; 
        case(99): // decimal 99 - "c" as char (ASCII) | Print the schedule for the particular instructor or student.
          if (inOption) printMsg(19, string(1, qt), 20); 
          else { printSchedule(0,0,0,1); inOption = true; } break; 
        case(100): // decimal 100 - "d" as char (ASCII) | Modify/create groups. Add/remove students to/from the group.
          if (inOption) printMsg(19, string(1, qt), 20); 
          else { manageGroups(1); printMsg(0, "", 20); }
          break;
        default: 
          printMsg(19, string(1, qt), 20); 
          break;
      }
    }
  } run = true;
  return 0;
}
