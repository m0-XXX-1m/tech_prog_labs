#ifndef TEACHER_H
#define TEACHER_H

#include "keeper.h"

namespace Teacher
{
    class Teacher : public Person::Person
    {
        std::vector<std::string> groups;
        std::vector<std::string> subjects;

    public:
        Teacher(const std::string& s = "-", const std::string& n = "-", const std::string& p = "-",
            const std::vector<std::string>& grps = {}, const std::vector<std::string>& sbjs = {});
        ~Teacher() = default;

        std::vector<std::string>& getGrps() const;
        std::vector<std::string>& getSbjs() const;

        void setGrps(std::vector<std::string>&);
        void setSbjs(std::vector<std::string>&);

        void saveToFile(std::ofstream&) const override;
        void readDataFromFile(std::ifstream&) override;
        void printData() const override;
    };
}

#endif