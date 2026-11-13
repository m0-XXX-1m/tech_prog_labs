#include "headers/Groups.h"
#include <limits>

int main()
{
    GroupsList::Groups* groups = new GroupsList::Groups();

    bool exit = false;
    while (!exit)
    {
        std::cout
            << "\n1 - add a student to the group\n"
            << "2 - add a group to the list\n"
            << "3 - remove the first\\last student in the group\n"
            << "4 - remove the first\\last group in the list\n"
            << "5 - show all students for a current group\n"
            << "6 - show all students filtered by average grade for a current group\n"
            << "7 - show all students for all groups\n"
            << "8 - find students\n"
            << "0 - exit\n\n"
            << "Enter the command number: ";
            
        int key;
        std::cin >> key;
        std::cout << std::endl;

        switch (key)
        {
            case 1:
            {
                std::string grName;
                std::cout << "Enter the group name: ";
                std::cin >> grName;

                GroupNode::Group* g = groups->findGroup(grName);
                if (!g)
                {
                    std::cout << "There is no group with such name.\n";
                    break;
                }

                std::string fn;
                std::cout << "Enter the student's surname and initials: ";
                // std::cin >> fn;
                std::getline(std::cin >> std::ws, fn);

                bool act;
                std::cout
                    << "Whant to fill " << fn << "'s marks?\n0 - No\t1 - Yes\n"
                    << "Enter: ";
                
                while (!(std::cin >> act))
                {
                    std::cout << "Unknown command! Try again" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }

                std::vector<double> m;
                if (act)
                {
                    int size;
                    std::cout << "Enter the quantity of marks: ";
                    while (!(std::cin >> size) || size < 1)
                    {
                        std::cout << "Incorrect value! Try again" << std::endl;
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }

                    m.reserve(size);
                    for (int i = 0; i < size; ++ i)
                    {
                        std::cout
                            << "Enter " << i + 1 << " mark: ";
                        double mark;
                        while (!(std::cin >> mark) || (mark < 1 || mark > 5))
                            {
                            std::cout << "Incorrect value! Try again" << std::endl;
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        }
                        m.push_back(mark);
                    }
                }

                Students::Student* s = new Students::Student(fn, m);
                try
                {
                    (*g) += s;
                }
                catch(const std::exception& e)
                {
                    delete s;
                    std::cerr << e.what() << '\n';
                }
                
                std::cout
                    << "\nStudent " << fn << " is added!\n";

                break;
            }
            case 2:
            {
                std::string grName;
                std::cout << "Enter the group name: ";
                std::cin >> grName;

                bool act;
                std::cout
                    << "What to fill the " << grName << "'s subjects\n"
                    << "0 - No\t1 - Yes\n"
                    << "Enter: ";

                while (!(std::cin >> act))
                {
                    std::cout << "Unknown command! Try again" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }

                std::vector<std::string> sbj;
                if (act)
                {
                    int size;
                    std::cout << "Enter the quantity of subjects: ";
                    while (!(std::cin >> size) || size < 1)
                    {
                        std::cout << "Incorrect value! Try again" << std::endl;
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }

                    sbj.reserve(size);

                    for (int i = 0; i < size; ++ i)
                    {
                        std::string subject;
                        std::cout << "Enter " << i + 1 << " subject: ";
                        std::cin >> subject;

                        sbj.push_back(subject);
                    }
                }

                try
                {
                    groups->addGroup(grName, sbj);
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                }
                
                std::cout
                    << "\nGroup " << grName << " is added!\n";

                break;
            }
            case 3:
            {
                std::string grName;
                std::cout << "Enter the group name: ";
                std::cin >> grName;

                GroupNode::Group* g = groups->findGroup(grName);
                if (!g)
                {
                    std::cout << "There is no group with such name.\n";
                    break;
                }

                bool act;
                std::cout
                    << "0 - remove first\t1 - remove last\n"
                    << "Enter: ";
                while (!(std::cin >> act))
                {
                    std::cout << "Unknown command! Try again" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }

                try
                {
                    Students::Student* s;
                    if (act)
                    {
                        s = (*g) --;
                        s->show();
                    }
                    else
                    {
                        s = -- (*g);
                        s->show();
                    }
                    delete s;
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                }
                
                std::cout
                    << "\nStudent is removed!";

                break;
                    
            }
            case 4:
            {
                bool act;
                std::cout
                    << "0 - remove first\t1 - remove last\n"
                    << "Enter: ";
                while (!(std::cin >> act))
                {
                    std::cout << "Unknown command! Try again" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }

                try
                {
                    GroupNode::Group* g;
                    if (act)
                    {
                        g = (*groups) --;
                        g->showAll();
                    }
                    else
                    {
                        g = -- (*groups);
                        g->showAll();
                    }
                    delete g;
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                }

                std::cout
                    << "\nGroup is removed!\n";
                    
                break;
            }
            case 5:
            {
                std::string grName;
                std::cout << "Enter the group name: ";
                std::cin >> grName;

                GroupNode::Group* g = groups->findGroup(grName);
                if (!g)
                {
                    std::cout << "There is no group with such name.\n";
                    break;
                }

                try
                {
                    g->showAll();
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                }
                
                break;
            }
            case 6:
            {
                std::string grName;
                std::cout << "Enter the group name: ";
                std::cin >> grName;

                GroupNode::Group* g = groups->findGroup(grName);
                if (!g)
                {
                    std::cout << "There is no group with such name.\n";
                    break;
                }

                std::cout
                    << "Enter the average grade: ";
                double ag;
                while (!(std::cin >> ag) || (ag < 1 || ag > 5))
                {
                    std::cout << "Incorrect value! Try again" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }

                try
                {
                    g->showAvrGrdFiltered(ag);
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                }
                
                break;
            }
            case 7:
            {
                try
                {
                    groups->showAll();
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                }
                
                break;
            }
            case 8:
            {
                std::string grName;
                std::cout << "Enter the group name: ";
                std::cin >> grName;

                GroupNode::Group* g = groups->findGroup(grName);
                if (!g)
                {
                    std::cout << "There is no group with such name.\n";
                    break;
                }

                std::string fn;
                std::cout << "Enter the student's surname and initials: ";
                // std::cin >> fn;
                std::getline(std::cin >> std::ws, fn);

                try
                {
                    groups->findStudent(grName, fn);
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                }
                
                break;
            }
            case 0:
            {
                exit = true;
                break;
            }
            default:
            {
                std::cout << "Unknown command! Try again\n" << std::endl;

                if (!std::cin)
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }
        }
    }

    delete groups;
    return 0;
}