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
#include <thread>

// Specific libs
#include "Lesson.h"

using namespace std;

#define RESET   "\033[0m"
#define PURPLE  "\033[35m"
#define RED     "\033[31m"
#define BLUE    "\033[34m"
#define YELLOW  "\033[33m"      /* Yellow */

std::string textToSave;
std::stringstream buffer;
std::vector<std::shared_ptr<Lane>> allLanes;
std::vector<std::shared_ptr<Group>> allGroups;
std::vector<std::shared_ptr<Instructor>> allInstructors;
WeeklySchedule weeklySchedule; // Creating a schedule

string timestamp(bool format) {// Tool Function 1 | Returns formatted string, which contains time/date from system. (Used by other functions)
  struct tm time; __time32_t aclock; char timestamp[32];
  _time32( &aclock );                                         // Get time in seconds.
  _localtime32_s( &time, &aclock );                           // Convert time to struct tm form.
  // The next line makes the timestamp in the format "18 Sep 2023 15:14:32".
  if (format) { strftime(timestamp, sizeof(timestamp), " %d %b %Y %H:%M:%S | ", &time); return string(timestamp); }
  strftime(timestamp, sizeof(timestamp), "%Y_%d_%m__%H_%M_%S", &time); // This line formats timestamp into "2024_11_01__17_11_07".
  return string(timestamp);
}

void save_file() {            // Tool Function 2 | Save the console output, even the program closed or stopped abruptly. (Used by other functions)
  ofstream myfile;                                            // Create the file object.
  myfile.open("schedule_search_history."+timestamp(0)+".txt");
  myfile << string(8, '/') << timestamp(1) << "Pool schedule search history " << string(8, '\\') << endl;
  myfile << textToSave;
  myfile.close();
}

// Tool Function 3 | Prints (or writes right into file) specific message based on the passed "_window". (Used by other functions)
void printMsg(int _window, string _text = "", int _w2 = -1, string _text2 = "", int _setw=66, int eqCount=-1) {  // 
  switch (_window) {
  case 0: 
    printMsg(16, " Pool Schedule Accounting Application ", -1, "", 39, 36);
    printMsg(17, "a");  printMsg(18, "Print the schedule for all the tracks, instructors and groups."); 
    printMsg(17, "b");  printMsg(18, "Print the schedule for the particular track or group."); 
    printMsg(17, "c");  printMsg(18, "Print the schedule for the particular instructor or student."); 
    printMsg(17, "d");  printMsg(18, "Create/modify group. Add/remove student to/from the group."); break;
  case 4: 
    printMsg(16, " Groups and students management ", -1, "", 30, 43);
    printMsg(17, "1");  printMsg(18, "Print the table with information for all students and groups."); 
    printMsg(17, "2");  printMsg(18, "Add the new student and assign it to the group."); 
    printMsg(17, "3");  printMsg(18, "Modify the information about the particular student."); 
    printMsg(17, "4");  printMsg(18, "Remove the student from the group."); break;
  case 10: textToSave.append(buffer.str()); buffer.str(""); break;
  case 11: cout << endl << _text << " : " << _text2 << endl; break;
  case 12: textToSave.append(buffer.str()); cout << buffer.str(); buffer.str(""); break;
  case 13: cout << buffer.str(); buffer.str(""); break; // Prints the content of "buffer" to STDOUT. Cleans "buffer".
  case 14: 
    buffer << endl << string(73, '-') << endl << timestamp(1) << "A problem occured in the program :\n" << _text << endl << string(73, '-'); 
    textToSave.append(buffer.str()); buffer.str(""); break;
  case 15: // Prepends the timestamp before the "_text". Writes alltogether into "buffer". Cleans buffer. Writes Only "_text" into "buffer".
    buffer << endl << timestamp(1) << string(3, '=') << setw(50) << left << _text << endl << string(77, '-') << endl; 
    textToSave.append(buffer.str()); buffer.str("");
    buffer << endl << string(10, '=') << setw(_setw) << left << _text << string(eqCount, '=') << endl << string(77, '-') << endl; break;
  case 16: cout << endl << string(2, '=') << setw(_setw) << left << _text << string(eqCount, '=') << endl; break;
  case 17: cout << string(77, '-') << endl << setw(2) << left << "|" << setw(5) << _text; break;
  case 18: cout << setw(2) << left << "|" << setw(_setw) << _text << setw(2) << right << "|" << endl; break;
  case 19: cout << "\nYou have pressed the key \"" << _text <<"\". There is no such option in this menu. Please try again.\n\n"; break;
  case 20: 
    printMsg(17, "TAB"); printMsg(18, "Back to the previous menu.", -1, ""); 
    printMsg(17, "ESC"); printMsg(18, "Exit the program.", -1, ""); cout << string(77, '-'); break;
  case 21: 
    printMsg(17, "TAB"); printMsg(18, "Back to the previous menu.", -1, ""); 
    printMsg(17, "BACKSPACE"); cout << setw(2) << left << " | " << setw(61) << "Remove the last character." << setw(2) << right << "|" << endl;
    printMsg(17, "ESC"); printMsg(18, "Exit the program.", -1, ""); cout << string(77, '-'); break;
  default: break;
  } if (_w2 != -1) printMsg(_w2, _text2, -1, "", _setw, eqCount);
}

// Tool Function 4 | Used to print the schedule. (Main loop, options a,b,c)
using PrintScheduleFunction = void (*)(const WeeklySchedule&); // Using a function pointer
// This printWeeklySchedule function uses the printSchedule function to output the weekly schedule
void printWeeklySchedule(const WeeklySchedule& schedule) {
  printSchedule(buffer, schedule, timestamp(1));
  printSchedule(cout, schedule, timestamp(1), 1);
  // printMsg(12);
  printMsg(10);
} PrintScheduleFunction printScheduleFunction = printWeeklySchedule;

// Tool Function 5 | Used by "ManageGroups" to print list of students per each group. (Main loop, option d - 1)
template <typename T0, typename T1, typename T2, typename T3, typename T4>
void print_row(std::ostream& os, T0 const& t0, T1 const& t1, T2 const& t2, T3 const& t3, T4 const& t4, 
bool last=false, bool groupName=false, bool color=false)
{
  if (groupName) { 
    os << (color ? BLUE : "" ) << "." << string(75, '-') << "." << endl << setw(1) << left 
    << "|" << std::setw(13) << left << " Group ID |   " << setw(61) << t0 << right << "|\n" << (color ? RESET : "" ); return; 
  }

  if (last) { os << (color ? YELLOW : "" ) << "*" << string(13, '-') << "*" << string(13, '-') << "*" << string(14, '-') << "*" 
    << string(17, '-') << "*" << string(14, '-') << "*" << (color ? RESET : "" ) << endl; return; } 

  os << (color ? YELLOW : "" ) << "." << string(75, '-') << ".\n" << "| " << setw(12) << left << t0 << "| " << setw(12) << left << t1 << "| " 
  << setw(13) << left << t2 << "| " << setw(16) << left << t3 << "| " << setw(12) << left << t4 << setw(2) << right << " |\n" << (color ? RESET : "" );
}

// Tool Function 6 | If "tui" (terminal-user-interface) is false, then add/remove the student non-interactively.
bool manageGroups(bool _tui, shared_ptr<Student> _student=nullptr, bool _add=true, bool _random=true, int _groupNum=0, bool toSTDOUT=false) {

  if (!_tui) {
    if (!_student) 
      { printMsg(14, "The \"_student\" object was passed with \"nullptr\" value to the \"" + string(__func__) + "\" function."); return true; }
    bool assigned = false; int assignedG = 1;
    for (auto group : allGroups) { auto groupp = group.get();
      if (groupp->getAllStudents().size() == 10) continue;
      else if (!_random) { 
        if (groupp->getNumber() == _groupNum) { groupp->addStudentToGroup(_student); assigned = true; assignedG = groupp->getNumber(); break; } 
        else continue;
      } groupp->addStudentToGroup(_student); assigned = true; assignedG = groupp->getNumber(); break;
    }
    if (!assigned && toSTDOUT)
      _random ? printMsg(14, "Unfortunately, all the groups are full.") : printMsg(14, "Unfortunately, the group \""+to_string(_groupNum) + "\"is full");
    else if (toSTDOUT) printMsg(16, " The entered student was successfully assigned to the group number " + to_string(assignedG) + " ", 20, "", 59, 5);
    return assigned;
  }

  bool inOption2 = false, confirm = true; char qt2 = ' ';
  auto validateField = [qt2](string& str, bool strIsPNum=false, bool strIsNum=false, bool strIsGroupId=false) mutable {
    if (!strIsPNum && !strIsNum && str.length() < 2) {cout << "\n This value cannot be empty or have less than 2 characters.\n\n"; return false;}
    if (strIsPNum && (str.length() < 12 || str.length() > 15) )
    {cout << "\n The phone number cannot be less than 11 characters, (including country code).\n It cannot be more than 15 characters.\n\n"; return false;}
    for (int i = 0; i < str.length(); i++) { qt2 = str[i]; 
      // 65-90 in ASCII means range of upper case letters, 97-122 - lower case letteres. 
      if ( ((qt2 <= 64) || (qt2 >= 91)) && ((qt2 <= 96) || (qt2 >= 123)) && !strIsPNum && !strIsNum ) 
      { cout << "\n This value accepts only letters \"abcdefghijklmnpqrstuvwxyz\" (upper and lower case).\n You've entered other characters as well. "
            << "Please use BACKSPACE to correct the value.\n\n";
        return false; }
      // 48-57 in ASCII means range of digits. 40-41 are "()". 43 is "+". 
      if ( ((qt2 <= 47) || (qt2 >= 58)) && (qt2 != 43) && (qt2 != 40) && (qt2 != 41) && strIsPNum && !strIsNum) 
      { cout << "\n This value accepts only characters \"0123456789()+\". You've entered other characters as well.\n"
            << "Please use BACKSPACE to correct the value.\n\n";  return false; }
      if ( ((qt2 <= 47) || (qt2 >= 58)) && !strIsPNum && strIsNum) 
      { cout << "\n This value accepts only digits \"0123456789\". You've entered other characters as well.\n"
            << " Please use BACKSPACE to correct the value.\n\n";  return false; }
      if (strIsGroupId) { bool ableToAssignToGroup=false, groupExist=false;
        cout << " The list of available groups (their group ids), excluding full (10 students already) groups: \n ";
        for (auto group : allGroups) {
          cout << group.get()->getNumber() << " ";
          if (group.get()->getAllStudents().size() == 10) { 
            if (stoi(str) == group.get()->getNumber()) { groupExist = true; ableToAssignToGroup=false; }
            continue; 
          } else if (stoi(str) == group.get()->getNumber()) { groupExist = true; ableToAssignToGroup = true; }
        }
        if (!groupExist) { cout << "\n The group with the ID \""+str+"\" does not exist. Please use BACKSPACE to correct the value.\n";return false;}
        if (!ableToAssignToGroup) { cout << "Not able to assign to the group with ID \"" + str + "\".\n\n"; return false; }
      }
    } return true;
  };

  auto checkInput = [validateField, qt2](string& fieldVar, string fieldVarMeaning,
                                  bool fieldVarIsPNum=false, bool fieldVarIsNum=false, bool strIsGroupId=false) mutable {
    system("CLS"); printMsg(16, " Enter the details for the new student: ",-1,"",40, 31); printMsg(11, fieldVarMeaning, 21, fieldVar);
    while (true)
      if (_kbhit() && (qt2 = _getch())) { 
        system("CLS");
        switch (qt2) {
          case(9): return false;                                         // decimal 9 - "TAB" as char (ASCII)       | Go back to the main menu.
          case(27): std::exit(0);                                        // decimal 27 - "ESCAPE" as char (ASCII)   | Exit Program.
          case(8):                                                       // decimal 8 - "BACKSPACE" as char (ASCII) | Delete last character.
            if (fieldVar.empty()) 
              { printMsg(16, " Enter the details for the new student: ",-1,"",40,31); printMsg(11, fieldVarMeaning, 21, fieldVar); continue; }
            fieldVar.pop_back(); printMsg(16, " Enter the details for the new student: ",-1,"",40,31);printMsg(11, fieldVarMeaning, 21, fieldVar); continue;
          case(10):case(13): // 10 - LINE FEED ("ENTER" key on Linux). 13 - CARRIAGE RETURN ("ENTER" on Windows)
            if (!validateField(fieldVar, fieldVarIsPNum, fieldVarIsNum, strIsGroupId)) { printMsg(11, fieldVarMeaning, 21, fieldVar); continue;}
            system("CLS"); return true;
          default: 
            fieldVar += qt2;
            printMsg(16," Enter the details for the new student: ",-1,"",40,31); printMsg(11, fieldVarMeaning, 21, fieldVar); continue;
        }
      }
  };

  system("CLS"); printMsg(4, "", 20); string firstN="", lastN="", parentN="", phoneNum="", paidL="", groupN="";
  while (true)
    if (_kbhit() && (qt2 = _getch())) { system("CLS");
      switch (qt2) {
        case(9):                                                  // decimal 9 - "TAB" as char (ASCII)     | Go back to the previous menu.
          if (inOption2) { inOption2=false; printMsg(4, "", 20); } 
          else return true; break; 
        case(27): std::exit(0);                                   // decimal 27 - "ESCAPE" as char (ASCII) | Exit Program.

        case(49):                                                 // decimal 49 - "1" as char (ASCII)      | Print all students,all groups.
          if (inOption2) printMsg(19, string(1, qt2), 20); 
          else {  
            printMsg(15, " Printing all students from all the groups ", -1, "", 40, 24);
            for (auto _group : allGroups) { auto _groupp = _group.get();
                                                                  // Print into the "Buffer", eventually, File - not colored.
              print_row(buffer, _groupp->getNumber() ,"", "", "", "", 0, 1);
              print_row(buffer, "First name" ,"Last name", "Parent name", "Phone number", "Paid lessons");
                                                                  // Print into the STDOUT - Colored.
              print_row(cout, _groupp->getNumber() ,"", "", "", "", 0, 1, 1);
              print_row(cout, "First name" ,"Last name", "Parent name", "Phone number", "Paid lessons", 0, 0, 1);
              for (auto _student : _groupp->getAllStudents()) 
              { auto _studentt = _student.get();
                                                                  // Print into the "Buffer", eventually, File - not colored.
                print_row(buffer, _studentt->getFirstName(), _studentt->getLastName(), _studentt->getParentName(), 
                _studentt->getPhoneNumber(), _studentt->getPaidLessons());
                                                                  // Print into the STDOUT - Colored.
                print_row(cout, _studentt->getFirstName(), _studentt->getLastName(), _studentt->getParentName(), 
                _studentt->getPhoneNumber(), _studentt->getPaidLessons(), 0, 0, 1);
              }
            } 
            print_row(buffer, 0, 0, 0, 0, 0, 1);                  // Print into the "Buffer", eventually, File - not colored.
            print_row(cout, 0, 0, 0, 0, 0, 1, 0, 1);              // Print into the STDOUT - Colored.
            // .---------------------------------------------------------------------------.
            // | group id    | 1                                                           |
            // .---------------------------------------------------------------------------.
            // | First name  | Last name   | Parent name  | Phone number    | Paid lessons |
            // .---------------------------------------------------------------------------.
            // | Yaroslava   | Arseniuk    | Nihoslav     | +38(542)2578432 | 7            |
            // ...
            // .---------------------------------------------------------------------------.
            // | group id    | 2                                                           |
            // .---------------------------------------------------------------------------.
            // | First name  | Last name   | Parent name  | Phone number    | Paid lessons |
            // .---------------------------------------------------------------------------.
            // | Panas       | Turkevych   | Avrelii      | +38(011)8728487 | 4            |
            // ...
            printMsg(10); inOption2 = true; 
          } break; 

        case(50):                                                 // decimal 50 - "2" as char (ASCII) | Print all students,all groups.
          if (inOption2) printMsg(19, string(1, qt2), 20); 
          else {
            printMsg(16, " Enter the details for the new student: ", -1, "", 59, 2);
            // Ref: checkInputLambda = [validateField](char& qt2, string& fieldVar, string fieldVarMeaning,
            //                     bool fieldVarIsPNum=false, bool fieldVarIsNum=false) mutable {
            if ( !checkInput(firstN, " Student's first name", 0, 0)   || !checkInput(lastN, " Student's last name", 0, 0) 
                || !checkInput(parentN, " Parent's first name", 0, 0) || !checkInput(phoneNum, " Phone number (in the format: \"+38(095)4779450\")", 1) 
                || !checkInput(paidL, " Paid lessons",0,1) 
                || !checkInput(groupN, " Group number (or leave it empty for the random available group) ",0,1,1) ) 
              { inOption2 = false; firstN="", lastN="",parentN="",phoneNum="",paidL=""; printMsg(4, "", 20); break; }

            printMsg(16, " You've entered the new Student with the following details. ", -1, "", 59, 14);
            std::transform(firstN.begin(), firstN.end(), firstN.begin(),[](unsigned char c) { return std::tolower(c); });
            std::transform(lastN.begin(), lastN.end(), lastN.begin(),[](unsigned char c) { return std::tolower(c); });
            std::transform(parentN.begin(), parentN.end(), parentN.begin(),[](unsigned char c) { return std::tolower(c); });
            firstN[0] = std::toupper(firstN[0]), lastN[0] = std::toupper(lastN[0]), parentN[0] = std::toupper(parentN[0]);

            if (groupN.empty()) groupN = "(empty)";
            print_row(cout,groupN,0,0,0,0,0,1,1);
            print_row(cout, "First name", "Last name", "Parent name", "Phone number", "Paid lessons",0,0,1);
            print_row(cout, firstN, lastN, parentN, phoneNum, paidL, 0,0,1); 
            // print_row(buffer, 0, "", "", 0, 0, 1);
            printMsg(16, " Please press \"ENTER\" if these details are correct. ", 16, " Or press any other key to discard.", 54, 21);
            qt2 = _getch(); if (qt2 != 13) { inOption2 = false; firstN="", lastN="",parentN="",phoneNum="",paidL="",groupN=""; system("CLS"); 
              printMsg(16, " Entered information was discarded.",20,"",54,21); break; }

               // Reference: bool manageGroups(bool _tui, shared_ptr<Student> _student=nullptr, bool _add=true, 
                                            // bool _random=true, int _groupNum=0, bool toSTDOUT=false)
            if (groupN[0] == '(') manageGroups(0, std::make_shared<Student>(firstN, lastN, parentN, phoneNum, stoi(paidL)),1,1,0,1);
            else manageGroups(0, std::make_shared<Student>(firstN, lastN, parentN, phoneNum, stoi(paidL)),1,0,stoi(groupN),1);
            firstN="", lastN="",parentN="",phoneNum="",paidL="",groupN=""; inOption2 = true;
          } break;

        default: 
          printMsg(19, string(1, qt2), 20); 
          break;
      }
    }
  return true;
}

int main() {
  std::atexit(save_file);
  for (int i=1; i<=3; i++) {                                      // Generating the 3 "Lane" objects and 4 "Group" objects.
    allLanes.push_back(std::make_shared<Lane>(i));                // Create "Lane" objects.
    allGroups.push_back(std::make_shared<Group>(i));              // Create "Group" objects.
  } allGroups.push_back(std::make_shared<Group>(4));
  unique_ptr<string>::pointer tmp0 = new string[5]{};             // Generating the 8 "Instructor" objects.
  unique_ptr<string>::pointer tmp1 = new string[5]{"Krutiy","Stetsyk","Yakhno","Dovzhanskyi","Shira"};
  unique_ptr<string>::pointer tmp2 = new string[5]{"+38(063)8651819","+38(096)5631589","+38(095)7834967","+38(067)6145363","+38(063)3255133"}, tmp3;
  unique_ptr<double>::pointer tmp4 = new double[5]{300.0,300.0,350.0,300.0,350.0}; unique_ptr<int>::pointer tmp5;
  for (int i=0; i<=4; i++) allInstructors.push_back(std::make_shared<Instructor>(tmp1[i], tmp2[i], tmp4[i]));
  allInstructors.push_back(std::make_shared<Instructor>("Kolchak", "+38(067)1345840", 300.0));
  allInstructors.push_back(std::make_shared<Instructor>("Panchyshyn", "+38(067)7462681", 300.0));
  allInstructors.push_back(std::make_shared<Instructor>("Kinash", "+38(099)4884404", 400.0));

  // Generating the 5 "Student" objects. Assigning them all to the "Group" with the "number" field = 3.
  tmp0 = new string[5]{"Zhozefina","Ilona","Lesia","Ruslan","Nikodim"};
  tmp1 = new string[5]{"Tichenko","Chujkevych","Pidoplichko","Ovrah","Hrynishak"}, tmp3 = new string[5]{"Sharl","Ustym","Emil","Jonas","Fedir"};
  tmp2 = new string[5]{"+38(730)7621483","+38(088)4889072","+38(024)8871747","+380(668)495229","+38(040)4230308"}; tmp5 = new int[5]{4,10,9,8,3};
  for (int i=0; i<=4; i++) manageGroups(0, std::make_shared<Student>(tmp0[i],tmp1[i],tmp3[i],tmp2[i],tmp5[i]),1,0,3);

  // For reference | bool manageGroups(bool _tui, shared_ptr<Student> _student=nullptr, bool _add=true, 
  //                                   bool _random=true, int _groupNum=0, bool toSTDOUT=false)

  // Generating another 5 "Student" objects. Assigning them to the groups, randomly.
  tmp0 = new string[5]{ "Yaroslava","yAkIv","aRtuR","iVaN","Barbara" };
  tmp1 = new string[5]{"Arseniuk","Pastukh","NEchytailo","POLozhii","HOlovinskyi"}, tmp3 = new string[5]{"Nihoslav","Pershyk","Chestyslav","Velet","Klym"};
  tmp2 = new string[5]{"+38(542)2578432","+38(472)7682276","+38(827)3367671","+38(352)3966987","+38(797)4122186"}; tmp5 = new int[5]{7,6,6,5,7};
  for (int i=0; i<=4; i++) manageGroups(0, std::make_shared<Student>(tmp0[i],tmp1[i],tmp3[i],tmp2[i], tmp5[i]));

  // Generating the 2 "Student" objects. Assigning them all to the "Group" with the "number" field = 2.
  manageGroups(0, std::make_shared<Student>("Panas","turkevych","avrelii","+38(011)8728487", 4),1,0,2);
  manageGroups(0, std::make_shared<Student>("Ostap","KoMpAneC","Lyubodar ","+38(078)3556676", 2),1,0,2);
  manageGroups(0, nullptr,1,0,1); // Generating the "Student" object as "nullptr" and passing it to this same function.

  weeklySchedule.days.push_back({ "Monday", {
      {"09:00-09:45", allLanes[0], allInstructors[2], allGroups[0]},
      {"10:15-11:00", allLanes[0], allInstructors[2], allGroups[0]},
      {"10:15-11:00", allLanes[1], allInstructors[3], allGroups[2]},
      {"11:30-12:15", allLanes[0], allInstructors[2], allGroups[3]},
      {"11:30-12:15", allLanes[1], allInstructors[3], allGroups[2]},
  } });

  weeklySchedule.days.push_back({ "Tuesday", {
        {"16:30-17:15", allLanes[2], allInstructors[0], allGroups[1]},
        {"17:45-18:30", allLanes[2], allInstructors[0], allGroups[1]},
    } });

  weeklySchedule.days.push_back({ "Wednesday", {
        {"10:15-11:00", allLanes[0], allInstructors[6], allGroups[0]},
        {"10:15-11:00", allLanes[1], allInstructors[5], allGroups[3]},
        {"11:30-12:15", allLanes[0], allInstructors[6], allGroups[0]},
        {"11:30-12:15", allLanes[1], allInstructors[5], allGroups[3]},
        {"15:15-16:00", allLanes[2], allInstructors[1], allGroups[2]},
    } });

  weeklySchedule.days.push_back({ "Thursday", {
        {"16:30-17:15", allLanes[2], allInstructors[0], allGroups[1]},
        {"17:45-18:30", allLanes[2], allInstructors[0], allGroups[1]},
    } });

  weeklySchedule.days.push_back({ "Friday", {
        {"09:00-09:45", allLanes[0], allInstructors[1], allGroups[2]},
        {"10:15-11:00", allLanes[2], allInstructors[7], allGroups[3]},
        {"10:15-11:00", allLanes[0], allInstructors[1], allGroups[2]},
        {"11:30-12:15", allLanes[2], allInstructors[7], allGroups[3]},
        {"12:45-13:30", allLanes[2], allInstructors[7], allGroups[0]},
  } });

  weeklySchedule.days.push_back({ "Saturday", {
        {"11:30-12:15", allLanes[1], allInstructors[4], allGroups[1]},
        {"12:45-13:30", allLanes[1], allInstructors[4], allGroups[1]},
  } });

  char qt = ' '; bool inOption = false;
  printMsg(0, "", 20); 
  while (true) {
    if (_kbhit()) {
      system("CLS");
      qt = _getch();
      switch (qt) {                                               // dec 9 - "TAB" as char (ASCII) | Go back to the main menu.
        case(9): printMsg(0, "", 20); inOption = false; break; 
        case(27): return 0; break;                                // dec 27 - "ESCAPE" as char (ASCII) | Exit Program.
        case(97):                                                 // dec 97 - "a" as char (ASCII) | Print generalized schedule.
          if (inOption) printMsg(19, string(1, qt), 20); 
          else { printScheduleFunction(weeklySchedule); printMsg(20); inOption = true; } break; 

        case(98):                                                 // dec 98 - "b" as char (ASCII) | Print schedule for specific track,group. 
          if (inOption) printMsg(19, string(1, qt), 20);
          else {
            int groupOrLaneNumber; std::cout << "Enter 'g' for group or 'l' for lane: " << (qt = _getch()) << endl;
            if (qt == 103 || qt == 108) { std::cout << "Enter " << (qt == 103 ? "group" : "lane") << " number: "; std::cin >> groupOrLaneNumber; } 
            else { std::cerr << "\nInvalid option. Use 'g' for group or 'l' for lane.\n"; break; }
            printScheduleForGroupOrLane(buffer, weeklySchedule, qt, groupOrLaneNumber, timestamp(1)); printMsg(12, "", 20);
            inOption = true; 
          } break;

        case(99):                                                 // dec 99 - "c" as char (ASCII) | Print schedule for specific instructor, student.
          if (inOption) printMsg(19, string(1, qt), 20); 
          else { printMsg(15, " Printing schedule for the particular person. ", 13, "", 45, 21); inOption = true; } break; 

        case(100):                                                // dec 100 - "d" as char (ASCII) | Modify/create groups. Add/remove students.
          if (inOption) printMsg(19, string(1, qt), 20); 
          else { manageGroups(1); printMsg(0, "", 20); } break;

        default: 
          printMsg(19, string(1, qt), 20); break;
      }
    }
  } 
  return 0;
}
