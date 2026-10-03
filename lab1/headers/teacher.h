#ifndef TEACHER_H
#define TEACHER_H

#include "person.h"

namespace Teachers
{
    class Teacher : public Persons::Person
    {
        std::vector<std::string> groups;
        std::vector<std::string> subjects;

    public:
        Teacher(const std::string& = "-", const std::string& = "-", const std::string& = "-",
            const std::vector<std::string>& = {}, const std::vector<std::string>& = {});
        ~Teacher() = default;

        std::vector<std::string> getGrps() const;
        std::vector<std::string> getSbjs() const;
        int getRoleRank() const override;

        void setGrps(std::vector<std::string>&);
        void setSbjs(std::vector<std::string>&);

        void saveToFile(std::ofstream&) const override;
        void readDataFromFile(std::ifstream&) override;
        void printData() const override;
    };
}

#endif