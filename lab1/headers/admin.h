#ifndef ADMIN_H
#define ADMIN_H

// #include "keeper.h"
#include "person.h"

namespace Admins
{
    class Admin: public Persons::Person
    {
        std::string post;
        std::string phone;
        std::string respArea;
        
    public:
        Admin(const std::string& = "-", const std::string& = "-", const std::string& = "-",
            const std::string& = "-", const std::string& = "-", const std::string& = "-");
        ~Admin() = default;

        std::string getPost() const;
        std::string getPhone() const;
        std::string getRespArea() const;
        int getRoleRank() const override;

        void setPost(std::string&);
        void setPhone(std::string&);
        void setRespArea(std::string&);

        void saveToFile(std::ofstream&) const override;
        void readDataFromFile(std::ifstream&) override;
        void printData() const override;
    };
}

#endif