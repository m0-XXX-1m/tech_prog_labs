#ifndef ADMIN_H
#define ADMIN_H

#include "keeper.h"

namespace Admin
{
    class Admin: public Person::Person
    {
        std::string post;
        std::string phone;
        std::string respArea;
        
    public:
        Admin(const std::string& s = "-", const std::string& n = "-", const std::string& p = "-",
            const std::string& pst = "-", const std::string& phn = "-", const std::string& ra = "-");
        ~Admin() = default;

        std::string& getPost() const;
        std::string& getPhone() const;
        std::string& getRespArea() const;

        void setPost(std::string&);
        void setPhone(std::string&);
        void setRespArea(std::string&);

        void saveToFile(std::ofstream&) const override;
        void readDataFromFile(std::ifstream&) override;
        void printData() const override;
    };
}

#endif