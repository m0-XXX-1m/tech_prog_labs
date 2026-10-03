#include "classes.h"
#include <limits>

int main(int argc, char* argv[])
{
    std::string file = argc > 1 ? argv[1] : "records.txt";

    Keeper::University* uni = new Keeper::University;

    int key = -1;
    bool escape = false;

    while (!escape)
    {
        std::cout
            << "\n1 - read data from file\n"
            << "2 - find members\n"
            << "3 - create member\n"
            << "4 - delete member\n"
            << "5 - write data to file\n"
            << "6 - print data\n"
            << "7 - delete all\n"
            << "0 - exit\n" << std::endl;

        std::cin >> key;
        switch (key)
        {
            case 1:
            {
                std::ifstream rf(file, std::ios::in);
                try
                {
                    uni->readFromFile(rf);
                }
                catch (std::exception& err)
                {
                    std::cerr << err.what() << std::endl;
                }
                rf.close();

                break;
            }
            case 2:
            {
                std::cout << "Whom to find:\n"
                    << "1 - Admin\t2 - Teacher\t3 - Student\n" << std::endl;
                
                unsigned short role;
                while (!(std::cin >> role) || (!role || role > 3))
                {
                    std::cout << "Unknown role! Try again\n" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }

                std::cout << "Member's surname:\t";
                
                std::string surname;
                std::cin >> surname;

                std::string paramsNamesArr[] = {"name", "patronimic"};
                std::string paramsArr[2] = {};

                bool fill_flag = 1;
                for (int i = 0; i < 2; ++ i)
                {
                    if (!fill_flag) break;

                    std::cout << "\nWant to fill a " << paramsNamesArr[i] << "?"
                        << "\n1 - Yes\t0 - No" << std::endl;
                    unsigned short act;
                    while (!(std::cin >> act) || act > 1)
                    {
                        std::cout << "Unknown action! Try again\n" << std::endl;
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                    
                    if (act)
                    {
                        std::cin >> paramsArr[i];
                        std::cout << std::endl;
                    }
                    else fill_flag = 0;
                }

                std::vector<Nodes::Node*> res = uni->findRecords(role, surname,
                                                        paramsArr[0], paramsArr[1]);

                if (res.empty())
                {
                    std::cout << "\nThe storage is empty" << std::endl;
                    break;
                }

                std::cout << "\nFound records:" << std::endl;
                for (Nodes::Node* n : res) n->data->printData();

                break;
            }
            case 3:
            {
                std::cout << "Role:\n1 - Admin\t2 - Teacher\t3 - Student" << std::endl;

                unsigned short role;
                while (!(std::cin >> role) || (!role || role > 3))
                {
                    std::cout << "Unknown role! Try again\n" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }

                std::string st_fieldNames[] = {
                    "Surname:\t",
                    "Name:\t",
                    "Patronimic:\t"
                };
                std::string st_fieldVals[3] = {};
                for (int i = 0; i < 3; ++ i)
                {
                    std::cout << st_fieldNames[i];
                    std::cin >> st_fieldVals[i];
                }

                Persons::Person* nw;
                switch (role)
                {
                    case 1:
                    {
                        std::string fnl_fieldNames[] = {
                            "Post:\t",
                            "Phone:\t",
                            "Responsible area:\t"
                        };
                        std::string fnl_fieldVals[3] = {};
                        for (int i = 0; i < 3; ++ i)
                        {
                            std::cout << fnl_fieldNames[i];
                            std::cin >> fnl_fieldVals[i];
                        }

                        nw = new Admins::Admin(
                            st_fieldVals[0],
                            st_fieldVals[1],
                            st_fieldVals[2],
                            fnl_fieldVals[0],
                            fnl_fieldVals[1],
                            fnl_fieldVals[2]
                        );

                        break;
                    }
                    case 2:
                    {
                        std::string fnl_fieldNames[] = {
                            "groups:\t",
                            "subjects:\t"
                        };
                        std::vector<std::vector<std::string>> fnl_fieldVals;
                        for (int i = 0; i < 2; ++ i)
                        {
                            std::cout << "How many " << fnl_fieldNames[i];
                            unsigned int n;
                            while (!(std::cin >> n))
                            {
                                std::cout << "Invalid value! Try again\n" << std::endl;
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            }

                            std::vector<std::string> list;
                            for (int j = 0; j < n; ++ j)
                            {
                                std::string val;
                                std::cin >> val;
                                list.push_back(val);
                            }

                            fnl_fieldVals.push_back(list);
                        }

                        nw = new Teachers::Teacher(
                            st_fieldVals[0],
                            st_fieldVals[1],
                            st_fieldVals[2],
                            fnl_fieldVals[0],
                            fnl_fieldVals[1]
                        );

                        break;
                    }
                    case 3:
                    {
                        std::string fnl_fieldNames[] = {
                            "Group:\t",
                            "Speciality:\t"
                        };
                        std::string fnl_fieldVals[2] = {};
                        for (int i = 0; i < 2; ++ i)
                        {
                            std::cout << fnl_fieldNames[i];
                            std::cin >> fnl_fieldVals[i];
                        }
                        unsigned int course;
                        while (!(std::cin >> course) || (!course || course > 6))
                        {
                            std::cout << "Invalid value! Try again\n" << std::endl;
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        }

                        Students::Student* s = new Students::Student(
                            st_fieldVals[0],
                            st_fieldVals[1],
                            st_fieldVals[2],
                            fnl_fieldVals[0],
                            fnl_fieldVals[1],
                            course
                        );

                        std::cout << "\n0 - calculate with a list of grades\tother - fill average grade yourself"
                            << std::endl;
                        
                        bool act;
                        while(!(std::cin >> act))
                        {
                            std::cout << "Invalid value! Try again\n" << std::endl;
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        }

                        if (act)
                        {
                            double ag;
                            while (!(std::cin >> ag))
                            {
                                std::cout << "Invalid value! Try again\n" << std::endl;
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            }

                            s->setAvrGr(ag);
                        }
                        else
                        {
                            std::cout << "Enter quantity of grades" << std::endl;

                            size_t n;
                            while (!(std::cin >> n))
                            {
                                std::cout << "Invalid value! Try again\n" << std::endl;
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            }

                            int* arr = new int[n];
                            for (int i = 0; i < n; ++ i)
                            {
                                std::cout << "Enter " << i << " grade:\t";
                                while (!(std::cin >> arr[i]))
                                {
                                    std::cout << "Invalid value! Try again\n" << std::endl;
                                    std::cin.clear();
                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                }
                            }

                            s->setAvrGr(arr, n);

                            delete[] arr;
                        }

                        nw = s;

                        break;
                    }
                }
                uni->addRecord(*nw);

                break;
            }
            case 4:
            {
                std::cout << "Whom to delete:\n"
                    << "1 - Admin\t2 - Teacher\t3 - Student\n" << std::endl;
                
                unsigned short role;
                while (!(std::cin >> role) || (!role || role > 3))
                {
                    std::cout << "Unknown role! Try again\n" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }

                std::cout << "Member's surname:\t";
                
                std::string surname;
                std::cin >> surname;

                std::string paramsNamesArr[] = {"name", "patronimic"};
                std::string paramsArr[2] = {};

                bool fill_flag = 1;
                for (int i = 0; i < 2; ++ i)
                {
                    if (!fill_flag) break;

                    std::cout << "\nWant to fill a " << paramsNamesArr[i] << "?"
                        << "\n1 - Yes\t0 - No" << std::endl;
                    unsigned short act;
                    while (!(std::cin >> act) || act > 1)
                    {
                        std::cout << "Unknown action! Try again\n" << std::endl;
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                    
                    if (act)
                    {
                        std::cin >> paramsArr[i];
                        std::cout << std::endl;
                    }
                    else fill_flag = 0;
                }

                uni->removeRecords(role, surname, paramsArr[0], paramsArr[1]);

                break;
            }
            case 5:
            {
                std::ofstream wf(file, std::ios::out);
                uni->saveToFile(wf);

                break;
            }
            case 6:
            {
                try
                {
                    uni->printMembers();
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                }
                
                break;
            }
            case 7:
            {
                delete uni;
                uni = new Keeper::University;

                break;
            }
            case 0:
            {
                escape = 1;
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

    delete uni;

    return 0;
}

/* #include "classes.h"

int main()
{
    Keeper::University* uni = new Keeper::University;
    Persons::Person* a;
    
    a = new Students::Student(
        "test1",
        "test1",
        "test1",
        "test1",
        "test1",
        3,
        4.5
    );
    
    uni->addRecord(*a);

    for (int i = 0; i < 3; ++ i)
    {
        a = new Admins::Admin(
            "test",
            "test",
            "test",
            "test",
            "test",
            "test"
        );

        uni->addRecord(*a);
    }

    a = new Students::Student(
        "test2",
        "test1",
        "test1",
        "test1",
        "test1",
        3,
        4.5
    );

    uni->addRecord(*a);

    a = new Teachers::Teacher(
        "test2",
        "test1",
        "test1",
        {"g1, g2, g3"},
        {"s1, s2, s3"}
    );

    uni->addRecord(*a);

    a = new Admins::Admin(
        "test",
        "test",
        "test",
        "test",
        "test",
        "test"
    );

    uni->addRecord(*a);

    std::vector<Nodes::Node*> res = uni->findRecords(1, "test");
    for (Nodes::Node* n : res)
    {
        n->data->printData();
    }

    std::ofstream wf("records.txt", std::ios::out);
    uni->saveToFile(wf); 

    std::ifstream rf("records.txt", std::ios::in);
    uni->readFromFile(rf);

    // uni->printMembers();

    uni->removeRecords(1, "test");

    uni->printMembers();

    if (uni) delete uni;
    // if (a) delete a;

    rf.close();

    return 0;
} */