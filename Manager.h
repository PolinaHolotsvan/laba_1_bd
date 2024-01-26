#ifndef LABA_1_BD_MANAGER_H
#define LABA_1_BD_MANAGER_H

#include <string>

using namespace std;

class Manager{
public:
    int manager_id;
    int manager_phone_number;
    int manager_age;

    Manager(int managerId, int managerPhoneNumber, int managerAge) : manager_id(managerId),
                                                                     manager_phone_number(managerPhoneNumber),
                                                                     manager_age(managerAge) {}

    Manager() {}
};

#endif //LABA_1_BD_MANAGER_H
