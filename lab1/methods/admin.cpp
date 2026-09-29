#include "../headers/admin.h"

using namespace Admins;

Admin::Admin(const std::string& s, const std::string& n, const std::string& p,
    const std::string& pst, const std::string& phn, const std::string& ra):
    Persons::Person(s, n, p), post(pst), phone(phn), respArea(ra) {}

std::string Admin::getPost() const
{
    return post;
}

std::string Admin::getPhone() const
{
    return phone;
}

std::string Admin::getRespArea() const
{
    return respArea;
}

void Admin::setPost(std::string& pst)
{
    post = pst;
}

void Admin::setPhone(std::string& phn)
{
    phone = phn;
}

void Admin::setRespArea(std::string& ra)
{
    respArea = ra;
}

void Admin::saveToFile(std::ofstream& f) const
{
    if (!f.is_open())
    {
        throw std::runtime_error("Error while openning a file to write");
    }

    /* f << "#ADMIN\n"
        << "SURNAME=" << getSurname() << "\n"
        << "NAME=" << getName() << "\n"
        << "PATRONIMIC=" << getPatronimic()<< "\n"
        << "POST=" << post << "\n"
        << "PHONE=" << phone << "\n"
        << "PESP_AREA" << respArea << "\n"; */

    f << "#ADMIN\n"
        << getSurname() << '\n'
        << getName() << '\n'
        << getPatronimic()<< '\n'
        << post << '\n'
        << phone << '\n'
        << respArea << '\n' << std::endl;
}

void Admin::readDataFromFile(std::ifstream& f)
{
    if (!f.is_open())
    {
        throw std::runtime_error("Error while openning a file to read");
    }

    enum fields{
        surname,
        name,
        patronimic,
        post,
        phone,
        respArea
    } flds = fields::surname;
    short st_flag = 0;
    short escape = 0;

    std::string line;
    while (std::getline(f, line) && !escape)
    {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (line[0] == '#' && line.substr(1) == "ADMIN"
            && !st_flag)
        {
            st_flag = 1;
            continue;
        }
        
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
                    flds = fields::post;

                    break;
                }
                case fields::post:
                {
                    this->post = line;
                    flds = fields::phone;

                    break;
                }
                case fields::phone:
                {
                    this->phone = line;
                    flds = fields::respArea;

                    break;
                }
                case fields::respArea:
                {
                    this->respArea = line;
                    escape = 1; 
                }
            }
        }
    }
}

void Admin::printData() const
{
    std::cout << "\nRole:\tAdmin\n"
        << "Surname:\t" << getSurname() << '\n'
        << "Name:\t" << getName() << '\n'
        << "Patronimic:\t" << getPatronimic() << '\n'
        << "Post:\t" << post << '\n'
        << "Phone:\t" << phone << '\n'
        << "Responsible area:\t" << respArea << '\n' << std::endl;
}