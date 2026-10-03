#include "../headers/teacher.h"

using namespace Teachers;

Teacher::Teacher(const std::string& s, const std::string& n, const std::string& p,
    const std::vector<std::string>& grs, const std::vector<std::string>& sbjs):
    Persons::Person(s, n, p), groups(grs), subjects(sbjs) {}

std::vector<std::string> Teacher::getGrps() const
{
    return groups;
}

std::vector<std::string> Teacher::getSbjs() const
{
    return subjects;
}

int Teacher::getRoleRank() const
{
    return 2;
}

void Teacher::setGrps(std::vector<std::string>& grs)
{
    groups = grs;
}

void Teacher::setSbjs(std::vector<std::string>& sbjs)
{
    subjects = sbjs;
}

void Teacher::saveToFile(std::ofstream& f) const
{
    if (!f.is_open())
    {
        throw std::runtime_error("Error while opening a file to write");
    }

    f << "#TEACHER\n"
        << getName() << '\n'
        << getSurname() << '\n'
        << getPatronimic() << '\n';
        
    for (auto it = groups.begin(); it != groups.end(); ++ it)
    {
        std::string gr = *it;
        if (it + 1 != groups.end()) gr += ",";
        f << gr;
    }
    f << '\n';

    for (auto it = subjects.begin(); it != subjects.end(); ++ it)
    {
        std::string sbj = *it;
        if (it + 1 != subjects.end()) sbj += ",";
        f << sbj;
    }
    f << '\n' << std::endl;
}

void Teacher::readDataFromFile(std::ifstream& f)
{
    if (!f.is_open())
    {
        throw std::runtime_error("Error while opening a file to read");
    }

    enum fields
    {
        surname,
        name,
        patronimic,
        groups,
        subjects
    } flds = fields::surname;
    short st_flag = /* 0 */1;
    short escape = 0;

    std::string line;
    while (std::getline(f, line) && !escape)
    {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        /* if (line[0] == '#' &&
            line.substr(1) == "TEACHER" &&
            !st_flag)
        {
            st_flag = 1;
            continue;
        } */
        if (line.empty()) continue;

        if (st_flag)
        {
            switch(flds)
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
                    flds = fields::groups;

                    break;
                }
                case fields::groups:
                {
                    auto start = line.begin();
                    auto end = line.end();
                    short not_end_flag = 0;

                    if (line.back() == ',') not_end_flag = 1;

                    size_t cur_pos = line.find(',');
                    size_t prev_pos = 0;
                    while (cur_pos != std::string::npos)
                    {
                        this->groups.push_back(line.substr(prev_pos, cur_pos - prev_pos));
                        prev_pos = cur_pos + 1;

                        cur_pos = line.find(',', cur_pos + 1);
                    }

                    if (prev_pos < line.length()) this->groups.push_back(line.substr(prev_pos));

                    if (not_end_flag) continue;

                    flds = fields::subjects;
                    break;
                }
                case fields::subjects:
                {
                    auto start = line.begin();
                    auto end = line.end();
                    short not_end_flag = 0;

                    if (line.back() == ',') not_end_flag = 1;

                    size_t cur_pos = line.find(',');
                    size_t prev_pos = 0;
                    while (cur_pos != std::string::npos)
                    {
                        this->subjects.push_back(line.substr(prev_pos, cur_pos - prev_pos));
                        prev_pos = cur_pos + 1;

                        cur_pos = line.find(',', cur_pos + 1);
                    }

                    if (prev_pos < line.length()) this->subjects.push_back(line.substr(prev_pos));

                    if (not_end_flag) continue;

                    escape = 1;
                    break;
                }
            }
        }
    }
}

void Teacher::printData() const
{
    std::cout << "\nRole:\tTeacher\n"
        << "Surname:\t" << getSurname() << '\n'
        << "Name:\t" << getName() << '\n'
        << "Patronimic:\t" << getPatronimic() << '\n';
    
    std::cout << "Groups:\t";
    for (auto it = groups.begin(); it != groups.end(); ++ it)
    {
        if (it + 1 != groups.end()) std::cout << *it << ", ";
        else std::cout << *it;
    }

    std::cout << "\nSubjects:\t";
    for (auto it = subjects.begin(); it != subjects.end(); ++ it)
    {
        if (it + 1 != subjects.end()) std::cout << *it << ", ";
        else std::cout << *it;
    }
    std::cout << '\n' << std::endl;
}