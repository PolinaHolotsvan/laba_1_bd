#ifndef LABA_1_BD_STAFF_H
#define LABA_1_BD_STAFF_H


class Staff{
public:
    int manager_id;
    int staff_id;
    int staff_phone_number;
    int staff_age;

    Staff(int managerId, int staffPhoneNumber, int staffAge) : manager_id(managerId),
                                                               staff_phone_number(staffPhoneNumber),
                                                               staff_age(staffAge) {}

    Staff(int managerId, int staffId, int phoneNumber, int age) : manager_id(managerId), staff_id(staffId),
                                                                  staff_phone_number(phoneNumber), staff_age(age) {}


    Staff() {};
};

#endif //LABA_1_BD_STAFF_H
