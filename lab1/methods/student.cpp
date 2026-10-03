#include "../headers/student.h"

using namespace Students;

Student::Student(const std::string& s, const std::string& n, const std::string& p,
    const std::string& g, const std::string& sp, unsigned int c, double ag):
    Persons::Person(s, n, p), group(g), spec(sp), course(c), averageGrade(ag) {}

std::string Student::getGroup() const
{
    return group;
}

std::string Student::getSpec() const
{
    return spec;
}

unsigned int Student::getCourse() const
{
    return course;
}

double Student::getAvrGr() const
{
    return averageGrade;
}

int Student::getRoleRank() const
{
    return 3;
}

void Student::setGroup(std::string& g)
{
    group = g;
}

void Student::setSpec(std::string& sp)
{
    spec = sp;
}

void Student::setCourse(unsigned int c)
{
    course = c;
}

void Student::setAvrGr(double ag)
{
    averageGrade = ag;
}

void Student::setAvrGr(int* grades, size_t n)
{
    if (!n)
    {
        averageGrade = 0;
        return;
    }

    if (!grades)
    {
        throw std::invalid_argument("Grades array cannot be NULL");
    }


    try
    {
        int sum;
        for (int i = 0; i < n; ++ i)
        {
            sum += grades[i];
        }

        averageGrade = static_cast<double>(sum) / n;
    }
    catch (std::exception& err)
    {
        throw err;
    }
}

void Student::saveToFile(std::ofstream& f) const
{
    if (!f.is_open())
    {
        throw std::runtime_error("Error while opening a file for writing");
    }

    f << "#STUDENT\n"
        << getName() << '\n'
        << getSurname() << '\n'
        << getPatronimic() << '\n'
        << group << '\n'
        << spec << '\n'
        << course << '\n'
        << averageGrade << '\n' << std::endl;
}

void Student::readDataFromFile(std::ifstream& f)
{
    if (!f.is_open())
    {
        throw std::runtime_error("Error while opening a file for reading");
    }

    enum fields
    {
        surname,
        name,
        patronimic,
        group,
        spec,
        course,
        avrgGrade
    } flds = fields::surname;
    short st_flag = /* 0 */1;
    short escape = 0;

    std::string line;
    while (std::getline(f, line) && !escape)
    {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        /* if (line[0] == '#' &&
            line.substr(1) == "STUDENT" &&
            !st_flag)
        {
            st_flag = 1;
            continue;
        } */
        if (line.empty()) continue;

        if (st_flag)
        {
            switch (flds)
            {
                case fields::surname:
                {
                    setSurname(line);
                    flds = fields::name;

                    break;
                }
                case fields::name:
                {
                    setName(line);
                    flds = fields::patronimic;

                    break;
                }
                case fields::patronimic:
                {
                    setPatronimic(line);
                    flds = fields::group;

                    break;
                }
                case fields::group:
                {
                    this->group = line;
                    flds = fields::spec;

                    break;
                }
                case fields::spec:
                {
                    this->spec = line;
                    flds = fields::course;

                    break;
                }
                case fields::course:
                {
                    this->course = std::stoi(line);
                    flds = fields::avrgGrade;

                    break;
                }
                case fields::avrgGrade:
                {
                    averageGrade = std::stod(line);
                    escape = 1;

                    break;
                }
            }
        }
    }
}

void Student::printData() const
{
    std::cout << "\nRole:\tStudent\n"
        << "Surname:\t" << getSurname() << '\n'
        << "Name:\t" << getName() << '\n'
        << "Patronimic:\t" << getPatronimic() << '\n'
        << "Group:\t" << group << '\n'
        << "Speciality:\t" << spec << '\n'
        << "Course:\t" << course << '\n'
        << "Average grade:\t" << averageGrade << '\n' << std::endl;
}