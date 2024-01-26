//у таранухи мать здохла
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <cstring>
#include "Manager.h"
#include "Staff.h"

using namespace std;

int getSize(FILE* file){
    fseek(file, 0,SEEK_END);
    int size = ftell(file);
    return size;
}

bool isUniqueManager(Manager manager){
    FILE* file = fopen("manager.fl", "rb");
    int size=getSize(file);
    bool isInFile=false;
    for(int i=0; i<size/sizeof(Manager) ; i++){
        fseek(file, i * sizeof(Manager) , SEEK_SET);
        Manager manager_t;
        fread(&manager_t, sizeof(Manager), 1, file);
        if(manager_t.manager_id==manager.manager_id) {isInFile = true;}
    }
    return !isInFile;
}

void managerToString(Manager manager){
    cout<<"Manager id:"<<manager.manager_id<<" phone number:";
    cout<<manager.manager_phone_number;
    cout<<" manager age:";
    cout<<manager.manager_age;
    cout<<endl;
}

void staffToString(Staff staff){
    cout<<"Staff id:"<<staff.staff_id<<" manager id:"<<staff.manager_id<<" phone number:";
    cout<<staff.staff_phone_number;
    cout<<" staff age:";
    cout<<staff.staff_age;
    cout<<endl;
}

void deleteManagerStaff(int manager_id){
    FILE* staffFile = fopen("staff.fl", "rb+");
    int size= getSize(staffFile)/sizeof(Staff);
    for(int i=0; i<size; i++) {
        Staff staff;
        fseek(staffFile, i * sizeof(Staff), SEEK_SET);
        fread(&staff, sizeof(Staff), 1, staffFile);
        if (manager_id == staff.manager_id) {
            staff.staff_id = -10;
            fseek(staffFile, i * sizeof(Staff), SEEK_SET);
            fwrite(&staff, sizeof(Staff), 1, staffFile);
        }
    }
    fclose(staffFile);
}
void binReadManager(int id){
    FILE* manager_file = fopen("manager.fl", "rb");
    int size= getSize(manager_file) / sizeof(Manager);
    bool isInFile=false;
    for(int i=0; i<size/sizeof(Manager); i++){
        fseek(manager_file, i * sizeof(Manager) , SEEK_SET);
        Manager manager_t;
        fread(&manager_t, sizeof(Manager), 1, manager_file);
        if(manager_t.manager_id==id) { managerToString(manager_t); isInFile=true;}
    }
    if(!isInFile) cout<<"There is no manager with this id"<<endl;
}
void binReadStaffManager(int manager_id){
    FILE* staffFile = fopen("staff.fl", "rb+");
    int size= getSize(staffFile)/sizeof(Staff);
    int count=0;
    for(int i=0; i<size; i++) {
        Staff staff;
        fseek(staffFile, i * sizeof(Staff), SEEK_SET);
        fread(&staff, sizeof(Staff), 1, staffFile);
        if ((manager_id == staff.manager_id) and (staff.staff_id!=-10)) {
            staffToString(staff);
            count++;
        }
    }
    cout<<count<<" staff workers in general"<<endl;
    fclose(staffFile);
}

void deleteManager(int id){
    FILE* managerFile = fopen("manager.fl", "rb+");
    int size= getSize(managerFile) / sizeof(Manager);
    bool isInFile=false;
    for(int i=0; i<size; i++) {
        Manager manager;
        fseek(managerFile, i * sizeof(Manager), SEEK_SET);
        fread(&manager, sizeof(Manager), 1, managerFile);
        if (id == manager.manager_id) {
            manager.manager_id = -10;
            fseek(managerFile, i * sizeof(Manager), SEEK_SET);
            fwrite(&manager, sizeof(Manager), 1, managerFile);
            deleteManagerStaff(id);
            isInFile = true;
        }
    }
    fclose(managerFile);
    if(isInFile){
        cout<<"Deleted successfully"<<endl;
    }
    else {
        cout<<"There is no manager worker with such id"<<endl;
    }
}

void editManager(int id, Manager manager){
    FILE* managerFile = fopen("manager.fl", "rb+");
    int size= getSize(managerFile)/sizeof(Manager);
    for(int i=0; i<size; i++){
        Manager manager_t;
        fseek(managerFile, i * sizeof(Manager) , SEEK_SET);
        fread(&manager_t, sizeof(Manager), 1, managerFile);
        if(id==manager_t.manager_id){
            fseek(managerFile, i * sizeof(Manager) , SEEK_SET);
            fwrite(&manager, sizeof(Manager), 1, managerFile);
        }
    }
    fclose(managerFile);
}

void binWriteManager(Manager manager) {
    //FILE* managerIndex = fopen("managerIndex.fl", "a+b");
    FILE* manager_file= fopen("manager.fl", "a+b");
    if(isUniqueManager(manager)){
        fwrite(&manager, sizeof(Manager), 1 , manager_file);
        cout<<"Added new manager"<<endl;
    }
    else cout<<"The manager with this unique id exists"<<endl;
    fclose(manager_file);
}


void binReadAllManagers(){
    FILE* manager_file = fopen("manager.fl", "rb");
    int size= getSize(manager_file) / sizeof (Manager);
    int count=0;
    for(int i=0; i<size; i++){
        fseek(manager_file, i * sizeof(Manager), SEEK_SET);
        Manager manager;
        fread(&manager, sizeof(Manager), 1, manager_file);
        if(manager.manager_id!=-10){
            managerToString(manager);
            count++;
        }
    }
    cout<<count<<" managers in general"<<endl;
    fclose(manager_file);
}

bool isUniqueStaff(Staff staff, char* filename){
    FILE* file = fopen(filename, "rb");
    int size= getSize(file);
    bool isInFile=false;
    for(int i=0; i<size/sizeof(Staff) ; i++){
        fseek(file, i * sizeof(Staff) , SEEK_SET);
        Staff staff_t;
        fread(&staff_t, sizeof(Staff), 1, file);
        if(staff_t.staff_id==staff.staff_id) {isInFile = true;}
    }
    return !isInFile;
}

void binReadStaff(int id) {
    FILE* staff_file = fopen("staff.fl", "rb");
    int size= getSize(staff_file)/sizeof(Staff);
    bool isInFile=false;
    for(int i=0; i<size/sizeof(Staff); i++){
        fseek(staff_file,i*sizeof(Staff) , SEEK_SET);
        Staff staff_t;
        fread(&staff_t, sizeof(Staff), 1, staff_file);
        if(staff_t.staff_id==id) { staffToString(staff_t); isInFile=true;}
    }
    if(!isInFile) cout<<"There is no staff worker with this id";
}

bool isManager(Staff staff){
    FILE* file = fopen("manager.fl", "rb");
    int size=getSize(file);
    bool isInFile=false;
    for(int i=0; i<size/sizeof(Manager) ; i++){
        fseek(file, i * sizeof(Manager) , SEEK_SET);
        Manager manager_t;
        fread(&manager_t, sizeof(Manager), 1, file);
        if(manager_t.manager_id==staff.manager_id) {isInFile = true;}
    }
    return isInFile;
}

void binWriteStaff(Staff staff, char* file) {
    FILE* staff_file= fopen(file, "a+b");
    if(isUniqueStaff(staff, file)){
        if(isManager(staff)){
            fwrite(&staff, sizeof(staff), 1 , staff_file);
            cout<<"Added new staff"<<endl;
        }
        else cout<<"There is no manager with this id";
    }
    else cout<<"The staff with this unique id exists"<<endl;
    fclose(staff_file);
}


void binReadAllStaff(){
    FILE* staff_file = fopen("staff.fl", "rb");
    int size= getSize(staff_file);
    int count=0;
    for(int i=0; i<size/sizeof (Staff); i++){
        fseek(staff_file,i*sizeof(Staff), SEEK_SET);
        Staff staff;
        fread(&staff, sizeof(Staff), 1, staff_file);
        if(staff.staff_id!=-10){
            staffToString(staff);
            count++;
        }
    }
    cout<<count<<" staff workers in general"<<endl;
    fclose(staff_file);
}
void deleteStaff(int id){
    FILE* staffFile = fopen("staff.fl", "rb+");
    int size= getSize(staffFile)/sizeof(Staff);
    bool isInFile=false;
    for(int i=0; i<size; i++) {
        Staff staff;
        fseek(staffFile, i * sizeof(Staff), SEEK_SET);
        fread(&staff, sizeof(Staff), 1, staffFile);
        if (id == staff.staff_id) {
            staff.staff_id = -10;
            fseek(staffFile, i * sizeof(Staff), SEEK_SET);
            fwrite(&staff, sizeof(Staff), 1, staffFile);
            isInFile = true;
        }
    }
    fclose(staffFile);
    if(isInFile){
        cout<<"Deleted successfully"<<endl;
    }
    else {
        cout<<"There is no staff worker with such id"<<endl;
    }

}

void editStaff(int id, Staff staff){
    FILE* staffFile = fopen("staff.fl", "rb+");
    int size= getSize(staffFile)/sizeof(Staff);
    for(int i=0; i<size; i++){
        Staff staff_t;
        fseek(staffFile, i * sizeof(Staff) , SEEK_SET);
        fread(&staff_t, sizeof(Staff), 1, staffFile);
        if(id==staff_t.staff_id){
            fseek(staffFile, i * sizeof(Staff) , SEEK_SET);
            fwrite(&staff, sizeof(Staff), 1, staffFile);
        }
    }
    fclose(staffFile);
}

int main() {

    int choice  = 0;
    int manager_id, staff_id, staff_phone_number, manager_phone_number, manager_age, staff_age;

    do{
        cout << "What do you want to do next?" << endl;
        cout << "1 - Add manager" << endl;
        cout << "2 - Remove manager" << endl;
        cout << "3 - Edit manager" << endl;
        cout << "4 - Add staff worker" << endl;
        cout << "5 - Remove staff worker" << endl;
        cout << "6 - Edit staff worker" << endl;
        cout << "7 - Get info about manager" << endl;
        cout << "8 - Get info about staff worker" << endl;
        cout << "9 - Get list of all staff workers for specific manager" << endl;
        cout << "10 - Get list of all managers" << endl;
        cout << "11 - Get list of all staff workers" << endl;
        cout << "12 - Exit" << endl;

        cin >> choice;
        switch (choice) {
            case 1:{
                cout << "Enter manager id" << endl;
                cin >> manager_id;
                cout << "Enter manager phone number" << endl;
                cin >> manager_phone_number;
                cout << "Enter manager surname" << endl;
                cin >> manager_age;
                Manager manager(manager_id, manager_phone_number, manager_age);
                binWriteManager(manager);
                break;
            }
            case 2:{
                cout<<"Enter id"<<endl;
                int id;
                cin>>id;
                deleteManager(id);
                break;
            }
            case 3:{
                cout<<"Enter id"<<endl;
                cin>>manager_id;
                cout<<"Enter new data"<<endl;
                cout << "Enter manager phone number" << endl;
                cin>>manager_phone_number;
                cout << "Enter manager age" << endl;
                cin>>staff_age;
                Manager manager(manager_id, manager_phone_number, manager_age);
                editManager(manager_id, manager);
                break;
            }

            case 4: {
                cout << "Enter staff id" << endl;
                cin >> staff_id;
                cout << "Enter manager id" << endl;
                cin >> manager_id;
                cout << "Enter staff phone number" << endl;
                cin>>staff_phone_number;
                cout << "Enter staff age" << endl;
                cin>>staff_age;
                Staff staff(manager_id, staff_id, staff_phone_number, staff_age);
                binWriteStaff(staff, "staff.fl");
                break;
            }

            case 5:{
                cout<<"Enter staff id"<<endl;
                int id;
                cin>>id;
                deleteStaff(id);
                break;
            }

            case 6:{
                cout<<"Enter id"<<endl;
                cin>>staff_id;
                cout<<"Enter new data"<<endl;
                cout << "Enter manager id" << endl;
                cin >> manager_id;
                cout << "Enter staff phone number" << endl;
                cin>>staff_phone_number;
                cout << "Enter staff age" << endl;
                cin>>staff_age;
                Staff staff(manager_id, staff_id, staff_phone_number, staff_age);
                editStaff(staff_id, staff);
                break;
            }

            case 7: {
                cout<<"Enter manager id"<<endl;
                int id;
                cin>>id;
                binReadManager(id);
                break;
            }
            case 8: {
                cout<<"Enter staff id"<<endl;
                int id;
                cin>>id;
                binReadStaff(id);
                break;
            }
            case 9:{
                cout<<"Enter staff id"<<endl;
                int id;
                cin>>id;
                binReadStaffManager(id);
                break;
            }
            case 10:{
                binReadAllManagers();
                break;
            }
            case 11:{
                binReadAllStaff();
                break;
            }

        }

    }while(choice != 12);


    return 0;
}