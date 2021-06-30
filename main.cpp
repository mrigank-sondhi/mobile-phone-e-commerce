#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <string.h>
#include <conio.h>
#include <vector>
#include <windows.h>

using namespace std;

void main_menu();
void customer_menu();
void admin_menu();
void modify_mobile();
void display();
void createcdll();
void deletecdll();
void filter_display(int);
void filter_menu();
void filter_company(int);
void filter_os(int);
void filter_rom(int);
void filter_ram(int);
void filter_battery(int);
void filter_camera(int);
void filter_price(int);
void addtocart();
void viewcart();
void initcartcdllfromfile();
void writecartcdlltofile();

//helper gotoxy function to output to a specific position
void gotoxy(int x, int y)
{
    static HANDLE handle = NULL;
    if (handle == NULL)
    {
        handle = GetStdHandle(STD_OUTPUT_HANDLE);
    }
    COORD position = {x, y};
    SetConsoleCursorPosition(handle, position);
}

//this is the password class
class Password_Validator
{
private:
    string *password;

public:
    //default constructor
    Password_Validator();

    //parameterized constructor
    Password_Validator(const string &inputStr);

    //destructor
    ~Password_Validator();

    //member functions
    void showPass();
    int *checkPass();
    int recom(int *resultArr);

    //getter function
    string *getpass()
    {
        return password;
    }

    //setter function
    void setpass(string *s)
    {
        *password = *s;
    }
} pass1("C++@proj1");

//password class constructors
Password_Validator::Password_Validator()
{
    password = NULL;
}

Password_Validator::Password_Validator(const string &inputStr)
{
    password = new string();
    *password = inputStr;
}

//password class destructor
Password_Validator::~Password_Validator()
{
    delete password;
}

//password class member functions
void Password_Validator::showPass()
{
    cout << "\nInput: \"" << *password << "\"";
    cout << endl;
}

int *Password_Validator::checkPass()
{
    int *resultArr = new int[7];
    for (int i = 0; i < 7; i++)
        resultArr[i] = 0;

    if (password->length() < 5)
        resultArr[0] = 1;
    if (password->length() > 10)
        resultArr[1] = 1;

    for (int i = 0; i < password->length(); i++)
    {
        if (isalpha(password->at(i)))
        {
            resultArr[2] = 1;
            if (isupper(password->at(i)))
                resultArr[3] = 1;
        }
        if (isdigit(password->at(i)))
            resultArr[4] = 1;
        if (ispunct(password->at(i)))
            resultArr[5] = 1;
        if (isspace(password->at(i)))
            resultArr[6] = 1;
    }
    return resultArr;
}

int Password_Validator::recom(int *resultArr)
{
    bool valid = true;
    if (resultArr[0])
    {
        cout << "\n- Minimum length should be 5";
        valid = false;
    }
    if (resultArr[1])
    {
        cout << "\n- Maximum length should be 10";
        valid = false;
    }
    if (!resultArr[2])
    {
        cout << "\n- Should contain at least one letter";
        valid = false;
    }
    if (!resultArr[3])
    {
        cout << "\n- Should contain at least one UPPERCASE letter";
        valid = false;
    }
    if (!resultArr[4])
    {
        cout << "\n- Should contain at least one digit";
        valid = false;
    }
    if (!resultArr[5])
    {
        cout << "\n- Should contain at least one special character";
        valid = false;
    }
    if (resultArr[6])
    {
        cout << "\n- Should not contain spaces";
        valid = false;
    }

    cout << endl;
    cout << "\nOutput: password ";
    if (valid)
    {
        cout << "is valid!";
        return 1;
    }
    else
    {
        cout << "is not valid!";
        cout << endl;
        return 0;
    }

    delete resultArr;
}

//this is the mobile phone class
class MobilePhone
{
private:
    //mobile attributes
    char name[50];
    unsigned int id;
    char company[50];
    char os[50];
    struct Memory
    {
        int rom;
        int ram;
    } memory;
    float price;
    int battery;
    int camera;
    char network[100];
    int num_available;

public:
    //pointers
    MobilePhone *prev, *next;
    MobilePhone *f1_prev, *f1_next;
    MobilePhone *f2_prev, *f2_next;

    MobilePhone();                  //default constructor
    MobilePhone(MobilePhone &temp); //copy constructor

    //getter functions
    char *getname()
    {
        char *s = name;
        return s;
    }
    char *getcompany()
    {
        char *s = company;
        return s;
    }
    char *getos()
    {
        char *s = os;
        return s;
    }
    Memory getmemory()
    {
        return memory;
    }
    float getprice()
    {
        return price;
    }
    int getbattery()
    {
        return battery;
    }
    int getcamera()
    {
        return camera;
    }
    unsigned int getid()
    {
        return id;
    }

    //void mobile_input(); //input mobile data from screen
    //void mobile_output();      //output mobile data to screen
    void mobile_file_output(); //output mobile data to file

    //overloading the output and input operator
    friend ostream &operator<<(ostream &out, MobilePhone &obj);
    friend istream &operator>>(istream &in, MobilePhone &obj);
} temp, *head = NULL, *tail = NULL, *f1_head = NULL, *f2_head = NULL, *cart_head = NULL, *cart_tail = NULL;

MobilePhone::MobilePhone() //default constructor
{
    //mobile attributes
    strcpy(name, "null");
    id = 0;
    strcpy(company, "null");
    strcpy(os, "null");
    memory.rom = 0;
    memory.ram = 0;
    price = 0;
    battery = 0;
    camera = 0;
    strcpy(network, "null");
    num_available = 0;

    //pointers
    prev = next = f1_prev = f1_next = f2_prev = f2_next = NULL;
}

MobilePhone::MobilePhone(MobilePhone &obj) //copy constructor
{
    strcpy(name, obj.name);
    id = obj.id;
    strcpy(company, obj.company);
    strcpy(os, obj.os);
    memory.rom = obj.memory.rom;
    memory.ram = obj.memory.ram;
    price = obj.price;
    battery = obj.battery;
    camera = obj.camera;
    strcpy(network, obj.network);
    num_available = obj.num_available;
};

//overloading the output operator
ostream &operator<<(ostream &out, MobilePhone &obj)
{
    out << "Mobile details:\n";
    out << "Mobile Name: ";
    puts(obj.name);
    out << "Mobile ID: ";
    out << obj.id;
    out << "\nCompany Name: ";
    puts(obj.company);
    out << "Operating System: ";
    puts(obj.os);
    out << "Memory Details: \n";
    out << "ROM: ";
    out << obj.memory.rom << " GB" << endl;
    out << "RAM: ";
    out << obj.memory.ram << " GB" << endl;
    out << "Price: ";
    out << obj.price << " Rs" << endl;
    out << "Battery capacity: ";
    out << obj.battery << " mAH" << endl;
    out << "Camera: ";
    out << obj.camera << " MP" << endl;
    out << "Network:";
    puts(obj.network);
    out << "Quantity Of Mobiles Available: ";
    out << obj.num_available << endl;
    return out;
}

//overloading the input operator
istream &operator>>(istream &in, MobilePhone &obj)
{
    system("cls");
    fflush(stdin);

    cout << "Enter the details:\n";
    cout << "Enter Mobile Name: ";
    in.getline(obj.name, 49);
    //cin >> name;
    cout << "Enter Mobile ID: ";
    in >> obj.id;
    cout << "Enter Company Name: ";
    in.ignore(); //to ignore the enter key
    in.getline(obj.company, 49);
    //cin >> company;
    cout << "Enter Operating System: ";
    in.getline(obj.os, 49);
    //cin >> os;
    cout << "Enter Memory Details: \n";
    cout << "Enter ROM: ";
    in >> obj.memory.rom;
    cout << "Enter RAM: ";
    in >> obj.memory.ram;
    cout << "Enter Price Of Mobile: ";
    in >> obj.price;
    cout << "Enter battery capacity: ";
    in >> obj.battery;
    cout << "Enter camera: ";
    in >> obj.camera;
    cout << "Enter Network: ";
    in.ignore();
    in.getline(obj.network, 99);
    //cin >> network;
    cout << "Enter The Quantity Of Mobiles Available: ";
    in >> obj.num_available;
    system("cls");
    return in;
}

/*void MobilePhone::mobile_input()
{
    system("cls");
    fflush(stdin);

    cout << "Enter the details:\n";
    cout << "Enter Mobile Name: ";
    cin.getline(name, 49);
    //cin >> name;
    cout << "Enter Mobile ID: ";
    cin >> id;
    cout << "Enter Company Name: ";
    cin.ignore();
    cin.getline(company, 49);
    //cin >> company;
    cout << "Enter Operating System:";
    cin.ignore();
    cin.getline(os, 49);
    //cin >> os;
    cout << "Enter Memory Details: \n";
    cout << "Enter ROM: ";
    cin >> memory.rom;
    cout << "Enter RAM: ";
    cin >> memory.ram;
    cout << "Enter Price Of Mobile: ";
    cin >> price;
    cout << "Enter battery capacity: ";
    cin >> battery;
    cout << "Enter camera: ";
    cin >> camera;
    cout << "Enter Network:";
    cin.ignore();
    cin.getline(network, 99);
    //cin >> network;
    cout << "Enter The Quantity Of Mobiles Available: ";
    cin >> num_available;
    system("cls");
    //mobile_file_output();
}*/

/*void MobilePhone::mobile_output()
{
    cout << "Mobile details:\n";
    cout << "Mobile Name: ";
    puts(name);
    cout << "Mobile ID: ";
    cout << id;
    cout << "\nCompany Name: ";
    puts(company);
    cout << "Operating System:";
    puts(os);
    cout << "Memory Details: \n";
    cout << "ROM: ";
    cout << memory.rom << endl;
    cout << "RAM: ";
    cout << memory.ram << endl;
    cout << "Price: ";
    cout << price << endl;
    cout << "Battery capacity: ";
    cout << battery << "mAh" << endl;
    cout << "Camera: ";
    cout << camera << "MP" << endl;
    cout << "Network:";
    puts(network);
    cout << "Quantity Of Mobiles Available: ";
    cout << num_available << endl;
}*/

void MobilePhone::mobile_file_output()
{
    system("cls");
    ofstream fout("mobiles.dat", ios::out | ios::app);
    fout.write((char *)&temp, sizeof(temp));
    fout.close();
    cout << "\nMobile added Successfully!\n";
}

//function to modify mobiles
void modify_mobile()
{
    char ch, choice;
    long int pos = 0;
    int flag = 0;
    unsigned int find_id = 0;
    system("cls");
    cout << "Please choose an option: \n";
    cout << "1. Change information of existing mobile" << endl;
    cout << "2. Delete a mobile " << endl;
    cout << "3. Go to previous menu" << endl;
    cout << "\n\n\t\tEnter your choice : ";
    cin >> choice;
    if (choice == '1')
    {
        system("cls");
        cout << "Enter the ID of mobile to be modified:";
        cin >> find_id;
        fstream fio("mobiles.dat", ios::in | ios::out);
        if (!fio)
        {
            cout << "\nFile Not Found!\n";
            cout << "Press any key to continue.";
            getch();
            system("cls");
            admin_menu();
        }
        fio.seekp(ios::beg);
        while (!fio.eof())
        {
            pos = fio.tellp();
            fio.read((char *)&temp, sizeof(temp));
            if (temp.getid() == find_id)
            {
                cout << "\nMobile found!\n";
                cout << "Do you want to modify the details(Y/N)?";
                cin >> ch;
                if (ch == 'y' || ch == 'Y')
                    cin >> temp;
                flag = 1;

                fio.seekp(pos);
                fio.write((char *)&temp, sizeof(temp));
                system("cls");
                break;
            }
        }
        if (flag == 0)
        {
            cout << "Invalid Mobile ID!\n";
            cout << "Press any key to continue.";
            getch();
            system("cls");
            modify_mobile();
        }
        else
        {
            cout << "Update Successful!\n";
        }
    }
    else if (choice == '2')
    {
        system("cls");
        flag = 0;
        cout << "Enter the ID of the mobile to be deleted:";
        cin >> find_id;
        ifstream fin("mobiles.dat", ios::in);
        if (!fin)
        {
            cout << "File Not Found!\n";
            cout << "Press any key to continue.";
            getch();
            fin.close();
            system("cls");
            admin_menu();
        }
        ofstream fout("temp.dat", ios::out);
        fout.seekp(ios::beg);
        while (fin.read((char *)&temp, sizeof(temp)))
        {

            if (temp.getid() == find_id)
            {
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            cout << "Mobile not found!\n";
            cout << "Press any key to continue.";
            getch();
            system("cls");
            modify_mobile();
        }
        else
        {
            fin.seekg(ios::beg);
            while (fin.read((char *)&temp, sizeof(temp)))
            {
                if (temp.getid() == find_id)
                {
                    cout << "Mobile found!" << endl;
                    cout << "Press any key to display mobile" << endl;
                    getch();
                    cout << temp;
                    getch();
                    //temp.mobile_output();
                    system("cls");
                    cout << "Do you want to delete it(Y/N)?";
                    cin >> ch;
                    if (ch == 'n' || ch == 'N')
                    {
                        fout.write((char *)&temp, sizeof(temp));
                    }
                } //if
                else
                {
                    fout.write((char *)&temp, sizeof(temp));
                }
            } //while
            cout << "Process completed!\n";
            fin.close();
            fout.close();
            remove("mobiles.dat");
            rename("temp.dat", "mobiles.dat");
        } //else
        cout << "Press any key to continue";
        getch();
        fin.close();
        fout.close();
        modify_mobile();
    }
    else if (choice == '3')
    {
        system("cls");
        admin_menu();
    }
    else
    {
        cout << "\nWrong Input.\n";
        cout << "Press any key to continue.";
        getch();
        system("cls");
        modify_mobile();
    }
    cout << "Press any key to continue..";
    getch();
    system("cls");
    admin_menu();
}

//function to print main menu
void main_menu()
{
    system("cls");
    char choice;
    gotoxy(0, 1);
    cout << "********************************************************************************";
    gotoxy(30, 2);
    cout << "MOBILE PHONE E-COMMERCE \n"
         << endl;
    cout << "********************************************************************************";
    gotoxy(30, 6);
    cout << "Please Choose Any Option: " << endl;
    gotoxy(18, 8);
    cout << "1. Customer" << endl;
    gotoxy(18, 9);
    cout << "2. Administrator" << endl;
    gotoxy(50, 8);
    cout << "3. Mobile Information" << endl;
    gotoxy(50, 9);
    cout << "4. About Us" << endl;
    gotoxy(35, 11);
    cout << "5. Exit Store\n"
         << endl;
    cout << "Enter your choice:";
    cin >> choice;

    if (choice == '1')
    {
        system("cls");
        customer_menu();
    }
    else if (choice == '2')
    {
        system("cls");
        char choice;
        int wrong_count = 0;
        gotoxy(0, 1);
        cout << "********************************************************************************";
        gotoxy(30, 2);
        cout << "PASSWORD\n"
             << endl;
        cout << "********************************************************************************";
        gotoxy(25, 6);
        cout << "Please Choose Any Option " << endl;
        gotoxy(15, 8);
        cout << "1.Input Password";
        gotoxy(40, 8);
        cout << "2.Change Password\n\n";
        cout << "Enter your choice:";
        cin >> choice;
        if (choice == '1')
        {
            wrong_count = 0;
            string s;
            while (wrong_count < 5)
            {
                fflush(stdin);
                cout << "\nInput password:";
                getline(cin, s);
                string *pass = pass1.getpass();
                if ((*pass).compare(s) == 0)
                {
                    cout << "\nValid password!\n\n";
                    getch();
                    system("cls");
                    admin_menu();
                }
                else
                {
                    wrong_count++;
                }
            }
            cout << "\nYou have entered the wrong password 5 times!";
            cout << "\nExiting!";
            getch();
            exit(0);
        }
        else
        {
            wrong_count = 0;
            string s;
            while (wrong_count < 5)
            {
                fflush(stdin);
                cout << "\nInput old password:";
                getline(cin, s);
                string *pass = pass1.getpass();
                if ((*pass).compare(s) == 0)
                {
                    cout << "\nValid password!\n\n";
                    getch();
                    wrong_count = 0;
                    while (wrong_count < 5)
                    {
                        int g;
                        system("cls");
                        cout << "Enter new password:" << endl;
                        string *inputStr = new string();
                        getline(cin, *inputStr);
                        if (!inputStr->length())
                        {
                            cout << "\nEmpty string was entered! Try one more time!";
                            cout << endl;
                            delete inputStr;
                        }
                        Password_Validator *v = new Password_Validator(*inputStr);
                        v->showPass();
                        g = v->recom(v->checkPass());
                        getch();
                        delete v;
                        if (g == 1)
                        {
                            pass1.setpass(inputStr);
                            delete inputStr;
                            cout << "\nPassword changed successfully!\n";
                            admin_menu();
                        }
                        else
                        {
                            wrong_count++;
                        }
                    }
                    cout << "\nYou have reached maximum number of trials!" << endl;
                    main_menu();
                }
                else
                {
                    wrong_count++;
                }
            }
            cout << "\nYou have entered the wrong password 5 times!";
            cout << "\nExiting!";
            getch();
            exit(0);
        }
    }

    else if (choice == '3')
    {
        system("cls");
        char a[136];
        ifstream fin("mobileinformation.txt");
        while (fin)
        {
            fin.getline(a, 136);
            cout << a << endl;
        }
        cout << "\nPress any key to continue.";
        fin.close();
        getch();
        main_menu();
    }
    else if (choice == '4')
    {
        system("cls");
        char a[136];
        ifstream fin("aboutus.txt");
        while (fin)
        {
            fin.getline(a, 136);
            cout << a << endl;
        }
        cout << "\nPress any key to continue.";
        fin.close();
        getch();
        main_menu();
    }
    else if (choice == '5')
    {
        exit(0);
    }
    else
    {
        cout << "\nPlease enter correct option!";
        getch();
        system("cls");
        main_menu();
    }
}

//function to print customer menu
void customer_menu()
{
    char choice;
    system("cls");
    gotoxy(0, 1);
    cout << "********************************************************************************";
    gotoxy(30, 2);
    cout << "Customer's Menu\n"
         << endl;
    cout << "********************************************************************************";
    gotoxy(30, 6);
    cout << "Please Choose Any Option " << endl;
    gotoxy(12, 8);
    cout << "1. Display Mobile Stock" << endl;
    gotoxy(12, 9);
    cout << "2. Search and Filter Mobiles" << endl;
    gotoxy(50, 8);
    cout << "3. View Cart" << endl;
    gotoxy(50, 9);
    cout << "4. Previous Menu\n"
         << endl;
    cout << "Enter your choice:";
    cin >> choice;

    if (choice == '1')
    {
        display();
    }
    else if (choice == '2')
    {
        filter_menu();
    }
    else if (choice == '3')
    {
        viewcart();
    }
    else if (choice == '4')
    {
        system("cls");
        main_menu();
    }
    else
    {
        cout << "Please enter correct option";
        getch();
        system("cls");
        customer_menu();
    }
}

//function to print admin menu
void admin_menu()
{
    system("cls");
    char choice;

    gotoxy(0, 1);
    cout << "********************************************************************************";
    gotoxy(30, 2);
    cout << "Administrator's Menu \n"
         << endl;
    cout << "********************************************************************************";
    gotoxy(30, 6);
    cout << "Please Choose Any Option " << endl;
    gotoxy(12, 8);
    cout << "1. Add Mobile" << endl;
    gotoxy(12, 9);
    cout << "2. Modify Existing Mobile" << endl;
    gotoxy(50, 8);
    cout << "3. View Cart" << endl;
    gotoxy(50, 9);
    cout << "4. Previous Menu\n"
         << endl;
    cout << "Enter your choice:";
    cin >> choice;
    cout << "********************************************************************************";
    gotoxy(30, 2);

    if (choice == '1')
    {
        char ch;
        do
        {
            system("cls");
            //temp.mobile_input();
            cin >> temp;
            temp.mobile_file_output();
            cout << "\nDo you want to enter again(Y/N)?";
            cin >> ch;
        } while (ch == 'Y' || ch == 'y');
        admin_menu();
    }
    else if (choice == '2')
    {
        modify_mobile();
    }
    else if (choice == '3')
    {
        viewcart();
    }
    else if (choice == '4')
    {
        system("cls");
        main_menu();
    }
    else
    {
        cout << "Please enter correct option";
        getch();
        system("cls");
        admin_menu();
    }
}

//function to display mobiles by reading from file
void display()
{
    unsigned int find_id = 0, flag = 0;
    char choice, ch;
    do
    {
        system("cls");
        cout << "\nChoose the required option";
        cout << "\n1.Display a specific mobile by ID";
        cout << "\n2.Display all mobiles";
        cout << "\n3.Back\n";
        cin >> choice;
        if (choice == '1')
            do
            {
                flag = 0;
                ifstream fin("mobiles.dat", ios::in);
                system("cls");
                cout << "\nEnter the ID of the phone:";
                cin >> find_id;
                while (fin.read((char *)&temp, sizeof(temp)))
                {

                    if (temp.getid() == find_id)
                    {
                        flag = 1;
                        //temp.mobile_output();
                        cout << temp;
                        cout << "\nPress any key to continue!";
                        getch();
                        break;
                    }
                } //while
                fin.close();
                if (flag == 0)
                {
                    cout << "ID not found,do you want to enter again(Y/N)?";
                    cin >> ch;
                }
                else
                {
                    display();
                }
            } while (ch == 'y' || ch == 'Y');
        else if (choice == '2')
        {
            system("cls");
            ifstream fin("mobiles.dat", ios::in);
            while (fin.read((char *)&temp, sizeof(temp)))
            {
                //temp.mobile_output();
                cout << temp << endl;
                cout << "\nPress any key to continue!\n\n";
                getch();
            }
            fin.close();
        }
        else if (choice == '3')
        {
            customer_menu();
        }
        else
        {
            cout << "\nInvalid input please enter again!";
        }
    } while (choice != '1' && choice != '2' && choice != '3');
    display();
}

//function to display mobiles stored in cdll after filtering
void filter_display(int filtercount)
{

    char choice = 'N';
    if (filtercount == 1)
    {
        MobilePhone *ptr = head;
        while (choice != 'e' and choice != 'E')
        {
            if (choice == 'n' or choice == 'N')
            {
                system("cls");
                ptr = ptr->next;
                cout << *ptr;
                //ptr->mobile_output();
            }
            else if (choice == 'p' or choice == 'P')
            {
                system("cls");
                ptr = ptr->prev;
                cout << *ptr;
                //ptr->mobile_output();
            }
            else if (choice == 'c' or choice == 'C')
            {
                char ch = 'Y';
                cout << "\n\nDo you want to add this phone to the cart?(Y/N)\n";
                cin >> ch;
                if (ch == 'y' or ch == 'Y')
                {
                    temp = *ptr;
                    temp.next = temp.prev = NULL;
                    addtocart();
                }
                cout << "\n1. Press 'P' for previous mobile\n2. Press 'N' for next mobile\n3. Press 'E' to exit\n";
                choice = getche();
                continue;
                //cin >> choice;
            }
            else
            {
                break;
            }
            cout << "\n1. Press 'P' for previous mobile\n2. Press 'N' for next mobile\n3. Press 'C' to add to cart\n4. Press 'E' to exit\n";
            choice = getche();
            //cin >> choice;
        }
        return;
    }
    else if (filtercount == 2)
    {
        MobilePhone *ptr = f1_head;
        while (choice != 'e' and choice != 'E')
        {
            if (choice == 'n' or choice == 'N')
            {
                system("cls");
                ptr = ptr->f1_next;
                cout << *ptr;
                //ptr->mobile_output();
            }
            else if (choice == 'p' or choice == 'P')
            {
                system("cls");
                ptr = ptr->f1_prev;
                cout << *ptr;
                //ptr->mobile_output();
            }
            else if (choice == 'c' or choice == 'C')
            {
                char ch = 'Y';
                cout << "\n\nDo you want to add this phone to the cart?(Y/N)\n";
                cin >> ch;
                if (ch == 'y' or ch == 'Y')
                {
                    temp = *ptr;
                    temp.next = temp.prev = NULL;
                    addtocart();
                }
                cout << "\n1. Press 'P' for previous mobile\n2. Press 'N' for next mobile\n3. Press 'E' to exit\n";
                choice = getche();
                continue;
                //cin >> choice;
            }
            else
            {
                break;
            }
            cout << "\n1. Press 'P' for previous mobile\n2. Press 'N' for next mobile\n3. Press 'C' to add to cart\n4. Press 'E' to exit\n";
            choice = getche();
            //cin >> choice;
        }
        return;
    }
    else if (filtercount == 3)
    {
        MobilePhone *ptr = f2_head;
        while (choice != 'e' and choice != 'E')
        {
            if (choice == 'n' or choice == 'N')
            {
                system("cls");
                ptr = ptr->f2_next;
                cout << *ptr;
                //ptr->mobile_output();
            }
            else if (choice == 'p' or choice == 'P')
            {
                system("cls");
                ptr = ptr->f2_prev;
                cout << *ptr;
                //ptr->mobile_output();
            }
            else if (choice == 'c' or choice == 'C')
            {
                char ch = 'Y';
                cout << "\n\nDo you want to add this phone to the cart?(Y/N)\n";
                cin >> ch;
                if (ch == 'y' or ch == 'Y')
                {
                    temp = *ptr;
                    temp.next = temp.prev = NULL;
                    addtocart();
                }
                cout << "\n1. Press 'P' for previous mobile\n2. Press 'N' for next mobile\n3. Press 'E' to exit\n";
                choice = getche();
                continue;
                //cin >> choice;
            }
            else
            {
                break;
            }
            cout << "\n1. Press 'P' for previous mobile\n2. Press 'N' for next mobile\n3. Press 'C' to add to cart\n4. Press 'E' to exit\n";
            choice = getche();
            //cin >> choice;
        }
        return;
    }
    else
    {
        cout << "\nIt is not possible to reach here!";
    }
}

//function to print filter menu
void filter_menu()
{
    system("cls");
    vector<string> filters = {"Company", "Operating System", "ROM", "RAM", "Battery", "Camera", "Price"};
    vector<string>::iterator it;
    int choice = 0, i = 0, filtercount = 0;
    char ch;

    do
    {
        if (filtercount == 3)
        {
            cout << "\nNo more filters allowed!\n";
            cout << "\nChoose display option:\n1.First filter\n2.Second filter\n3.Third filter\n4.Previous Menu\n";
            cin >> ch;
            if (ch == '1')
            {
                filter_display(1);
                break;
            }
            else if (ch == '2')
            {
                filter_display(2);
                break;
            }
            else if (ch == '3')
            {
                filter_display(3);
                break;
            }
            else
            {
                break;
            }
        }
        system("cls");
        cout << "********************************************************************************";
        gotoxy(30, 2);
        cout << "Filter Phones\n"
             << endl;
        cout << "********************************************************************************";
        cout << "\n\nPlease choose an option:" << endl;
        i = 0;
        for (it = filters.begin(); it != filters.end(); it++)
        {
            cout << i + 1 << ". " << *it << endl;
            i++;
        }
        cout << i + 1 << ". Previous Menu" << endl;
        cout << "\nEnter your choice: ";
        cin >> choice;
        it = filters.begin();
        if (filters[choice - 1] == "Company")
        {
            cout << "\nFiltering by company!\n";
            filters.erase(it + (choice - 1));
            filtercount++;
            filter_company(filtercount);
        }
        else if (filters[choice - 1] == "Operating System")
        {
            cout << "\nFiltering by Operating System!\n";
            filters.erase(it + (choice - 1));
            filtercount++;
            filter_os(filtercount);
        }
        else if (filters[choice - 1] == "ROM")
        {
            cout << "\nFiltering by ROM!\n";
            filters.erase(it + (choice - 1));
            filtercount++;
            filter_rom(filtercount);
        }
        else if (filters[choice - 1] == "RAM")
        {
            cout << "\nFiltering by RAM!\n";
            filters.erase(it + (choice - 1));
            filtercount++;
            filter_ram(filtercount);
        }
        else if (filters[choice - 1] == "Battery")
        {
            cout << "\nFiltering by Battery!\n";
            filters.erase(it + (choice - 1));
            filtercount++;
            filter_battery(filtercount);
        }
        else if (filters[choice - 1] == "Camera")
        {
            cout << "\nFiltering by Camera!\n";
            filters.erase(it + (choice - 1));
            filtercount++;
            filter_camera(filtercount);
        }
        else if (filters[choice - 1] == "Price")
        {
            cout << "\nFiltering by Price!\n";
            filters.erase(it + (choice - 1));
            filtercount++;
            filter_price(filtercount);
        }
    } while (choice != (i + 1));
    cout << "Deleting filters!";
    getch();
    deletecdll();
    customer_menu();
}

//function to filter according to company
void filter_company(int filtercount)
{
    char find_company[50], choice;
    cout << "Which company do you want to filter for?\n";
    cin >> find_company;
    if (filtercount == 1)
    {
        ifstream fin("mobiles.dat", ios::in);
        while (fin.read((char *)&temp, sizeof(temp)))
        {
            if (strcmpi(temp.getcompany(), find_company) == 0)
            {
                createcdll();
            }
            else
            {
                continue;
            }
        }
        fin.close();
        cout << "\nChoose option:\n1. Display\n2. Filter further\n";
        cin >> choice;
        if (choice == '1')
        {
            filter_display(filtercount);
            return;
        }
        else
        {
            return;
        }
    }
    else if (filtercount == 2)
    {
        //change f1_head,f1_prev and f1_next
        MobilePhone *ptr = head, *trailptr = head;

        do
        {
            if (strcmpi(ptr->getcompany(), find_company) == 0)
            {
                if (f1_head == NULL) //first phone in filter
                {
                    f1_head = ptr;
                    ptr->f1_prev = ptr->f1_next = ptr;
                }
                else
                {
                    trailptr->f1_next = ptr;
                    ptr->f1_prev = trailptr;
                    ptr->f1_next = f1_head;
                    f1_head->f1_prev = ptr;
                }
                trailptr = ptr;
            }
            ptr = ptr->next;
        } while (ptr != head);
        cout << "\nChoose option:\n1. Display\n2. Filter further\n";
        cin >> choice;
        if (choice == '1')
        {
            filter_display(filtercount);
            return;
        }
        else
        {
            return;
        }
    }
    else if (filtercount == 3)
    {
        //change f2_head,f2_prev and f2_next
        MobilePhone *ptr = f1_head, *trailptr = f1_head;

        do
        {
            if (strcmpi(ptr->getcompany(), find_company) == 0)
            {
                if (f2_head == NULL) //first phone in filter
                {
                    f2_head = ptr;
                    ptr->f2_prev = ptr->f2_next = ptr;
                }
                else
                {
                    trailptr->f2_next = ptr;
                    ptr->f2_prev = trailptr;
                    ptr->f2_next = f2_head;
                    f2_head->f2_prev = ptr;
                }
                trailptr = ptr;
            }
            ptr = ptr->f1_next;
        } while (ptr != f1_head);
        cout << "\nChoose option:\n1. Display\n2. Filter further\n";
        cin >> choice;
        if (choice == '1')
        {
            filter_display(filtercount);
            return;
        }
        else
        {
            return;
        }
    }
    else
    {
        cout << "It is not possible to reach here!";
    }
}

//function to filter according to os
void filter_os(int filtercount)
{
    char find_os[50], choice;
    cout << "Which Operating System do you want to filter for?\n";
    fflush(stdin);
    cin.getline(find_os, 49);
    if (filtercount == 1)
    {
        ifstream fin("mobiles.dat", ios::in);
        while (fin.read((char *)&temp, sizeof(temp)))
        {
            if (strcmpi(temp.getos(), find_os) == 0)
            {
                createcdll();
            }
            else
            {
                continue;
            }
        }
        fin.close();
        cout << "\nChoose option:\n1. Display\n2. Filter further\n";
        cin >> choice;
        if (choice == '1')
        {
            filter_display(filtercount);
            return;
        }
        else
        {
            return;
        }
    }
    else if (filtercount == 2)
    {
        //change f1_head,f1_prev and f1_next
        MobilePhone *ptr = head, *trailptr = head;

        do
        {
            if (strcmpi(ptr->getos(), find_os) == 0)
            {
                if (f1_head == NULL) //first phone in filter
                {
                    f1_head = ptr;
                    ptr->f1_prev = ptr->f1_next = ptr;
                }
                else
                {
                    trailptr->f1_next = ptr;
                    ptr->f1_prev = trailptr;
                    ptr->f1_next = f1_head;
                    f1_head->f1_prev = ptr;
                }
                trailptr = ptr;
            }
            ptr = ptr->next;
        } while (ptr != head);
        cout << "\nChoose option:\n1. Display\n2. Filter further\n";
        cin >> choice;
        if (choice == '1')
        {
            filter_display(filtercount);
            return;
        }
        else
        {
            return;
        }
    }
    else if (filtercount == 3)
    {
        //change f2_head,f2_prev and f2_next
        MobilePhone *ptr = f1_head, *trailptr = f1_head;

        do
        {
            if (strcmpi(ptr->getos(), find_os) == 0)
            {
                if (f2_head == NULL) //first phone in filter
                {
                    f2_head = ptr;
                    ptr->f2_prev = ptr->f2_next = ptr;
                }
                else
                {
                    trailptr->f2_next = ptr;
                    ptr->f2_prev = trailptr;
                    ptr->f2_next = f2_head;
                    f2_head->f2_prev = ptr;
                }
                trailptr = ptr;
            }
            ptr = ptr->f1_next;
        } while (ptr != f1_head);
        cout << "\nChoose option:\n1. Display\n2. Filter further\n";
        cin >> choice;
        if (choice == '1')
        {
            filter_display(filtercount);
            return;
        }
        else
        {
            return;
        }
    }
    else
    {
        cout << "It is not possible to reach here!";
    }
}

//function to filter according to rom
void filter_rom(int filtercount)
{
    int find_rom_min, find_rom_max;
    char choice;
    cout << "Enter minimum ROM:";
    cin >> find_rom_min;
    cout << "Enter maximum ROM:";
    cin >> find_rom_max;
    if (filtercount == 1)
    {
        ifstream fin("mobiles.dat", ios::in);
        while (fin.read((char *)&temp, sizeof(temp)))
        {
            if ((temp.getmemory().rom >= find_rom_min) and (temp.getmemory().rom <= find_rom_max))
            {
                createcdll();
            }
            else
            {
                continue;
            }
        }
        fin.close();
        cout << "\nChoose option:\n1. Display\n2. Filter further\n";
        cin >> choice;
        if (choice == '1')
        {
            filter_display(filtercount);
            return;
        }
        else
        {
            return;
        }
    }
    else if (filtercount == 2)
    {
        //change f1_head,f1_prev and f1_next
        MobilePhone *ptr = head, *trailptr = head;

        do
        {
            if ((ptr->getmemory().rom >= find_rom_min) and (ptr->getmemory().rom <= find_rom_max))
            {
                if (f1_head == NULL) //first phone in filter
                {
                    f1_head = ptr;
                    ptr->f1_prev = ptr->f1_next = ptr;
                }
                else
                {
                    trailptr->f1_next = ptr;
                    ptr->f1_prev = trailptr;
                    ptr->f1_next = f1_head;
                    f1_head->f1_prev = ptr;
                }
                trailptr = ptr;
            }
            ptr = ptr->next;
        } while (ptr != head);
        cout << "\nChoose option:\n1. Display\n2. Filter further\n";
        cin >> choice;
        if (choice == '1')
        {
            filter_display(filtercount);
            return;
        }
        else
        {
            return;
        }
    }
    else if (filtercount == 3)
    {
        //change f2_head,f2_prev and f2_next
        MobilePhone *ptr = f1_head, *trailptr = f1_head;

        do
        {
            if ((ptr->getmemory().rom >= find_rom_min) and (ptr->getmemory().rom <= find_rom_max))
            {
                if (f2_head == NULL) //first phone in filter
                {
                    f2_head = ptr;
                    ptr->f2_prev = ptr->f2_next = ptr;
                }
                else
                {
                    trailptr->f2_next = ptr;
                    ptr->f2_prev = trailptr;
                    ptr->f2_next = f2_head;
                    f2_head->f2_prev = ptr;
                }
                trailptr = ptr;
            }
            ptr = ptr->f1_next;
        } while (ptr != f1_head);
        cout << "\nChoose option:\n1. Display\n2. Filter further\n";
        cin >> choice;
        if (choice == '1')
        {
            filter_display(filtercount);
            return;
        }
        else
        {
            return;
        }
    }
    else
    {
        cout << "It is not possible to reach here!";
    }
}

//function to filter according to ram
void filter_ram(int filtercount)
{
    int find_ram_min, find_ram_max;
    char choice;
    cout << "Enter minimum RAM:";
    cin >> find_ram_min;
    cout << "Enter maximum RAM:";
    cin >> find_ram_max;
    if (filtercount == 1)
    {
        ifstream fin("mobiles.dat", ios::in);
        while (fin.read((char *)&temp, sizeof(temp)))
        {
            if ((temp.getmemory().ram >= find_ram_min) and (temp.getmemory().ram <= find_ram_max))
            {
                createcdll();
            }
            else
            {
                continue;
            }
        }
        fin.close();
        cout << "\nChoose option:\n1. Display\n2. Filter further\n";
        cin >> choice;
        if (choice == '1')
        {
            filter_display(filtercount);
            return;
        }
        else
        {
            return;
        }
    }
    else if (filtercount == 2)
    {
        //change f1_head,f1_prev and f1_next
        MobilePhone *ptr = head, *trailptr = head;

        do
        {
            if ((ptr->getmemory().ram >= find_ram_min) and (ptr->getmemory().ram <= find_ram_max))
            {
                if (f1_head == NULL) //first phone in filter
                {
                    f1_head = ptr;
                    ptr->f1_prev = ptr->f1_next = ptr;
                }
                else
                {
                    trailptr->f1_next = ptr;
                    ptr->f1_prev = trailptr;
                    ptr->f1_next = f1_head;
                    f1_head->f1_prev = ptr;
                }
                trailptr = ptr;
            }
            ptr = ptr->next;
        } while (ptr != head);
        cout << "\nChoose option:\n1. Display\n2. Filter further\n";
        cin >> choice;
        if (choice == '1')
        {
            filter_display(filtercount);
            return;
        }
        else
        {
            return;
        }
    }
    else if (filtercount == 3)
    {
        //change f2_head,f2_prev and f2_next
        MobilePhone *ptr = f1_head, *trailptr = f1_head;

        do
        {
            if ((ptr->getmemory().ram >= find_ram_min) and (ptr->getmemory().ram <= find_ram_max))
            {
                if (f2_head == NULL) //first phone in filter
                {
                    f2_head = ptr;
                    ptr->f2_prev = ptr->f2_next = ptr;
                }
                else
                {
                    trailptr->f2_next = ptr;
                    ptr->f2_prev = trailptr;
                    ptr->f2_next = f2_head;
                    f2_head->f2_prev = ptr;
                }
                trailptr = ptr;
            }
            ptr = ptr->f1_next;
        } while (ptr != f1_head);
        cout << "\nChoose option:\n1. Display\n2. Filter further\n";
        cin >> choice;
        if (choice == '1')
        {
            filter_display(filtercount);
            return;
        }
        else
        {
            return;
        }
    }
    else
    {
        cout << "It is not possible to reach here!";
    }
}

//function to filter according to battery
void filter_battery(int filtercount)
{
    int find_battery_min, find_battery_max;
    char choice;
    cout << "Enter minimum battery capacity:";
    cin >> find_battery_min;
    cout << "Enter maximum battery capacity:";
    cin >> find_battery_max;
    if (filtercount == 1)
    {
        ifstream fin("mobiles.dat", ios::in);
        while (fin.read((char *)&temp, sizeof(temp)))
        {
            if ((temp.getbattery() >= find_battery_min) and (temp.getbattery() <= find_battery_max))
            {
                createcdll();
            }
            else
            {
                continue;
            }
        }
        fin.close();
        cout << "\nChoose option:\n1. Display\n2. Filter further\n";
        cin >> choice;
        if (choice == '1')
        {
            filter_display(filtercount);
            return;
        }
        else
        {
            return;
        }
    }
    else if (filtercount == 2)
    {
        //change f1_head,f1_prev and f1_next
        MobilePhone *ptr = head, *trailptr = head;

        do
        {
            if ((ptr->getbattery() >= find_battery_min) and (ptr->getbattery() <= find_battery_max))
            {
                if (f1_head == NULL) //first phone in filter
                {
                    f1_head = ptr;
                    ptr->f1_prev = ptr->f1_next = ptr;
                }
                else
                {
                    trailptr->f1_next = ptr;
                    ptr->f1_prev = trailptr;
                    ptr->f1_next = f1_head;
                    f1_head->f1_prev = ptr;
                }
                trailptr = ptr;
            }
            ptr = ptr->next;
        } while (ptr != head);
        cout << "\nChoose option:\n1. Display\n2. Filter further\n";
        cin >> choice;
        if (choice == '1')
        {
            filter_display(filtercount);
            return;
        }
        else
        {
            return;
        }
    }
    else if (filtercount == 3)
    {
        //change f2_head,f2_prev and f2_next
        MobilePhone *ptr = f1_head, *trailptr = f1_head;

        do
        {
            if ((ptr->getbattery() >= find_battery_min) and (ptr->getbattery() <= find_battery_max))
            {
                if (f2_head == NULL) //first phone in filter
                {
                    f2_head = ptr;
                    ptr->f2_prev = ptr->f2_next = ptr;
                }
                else
                {
                    trailptr->f2_next = ptr;
                    ptr->f2_prev = trailptr;
                    ptr->f2_next = f2_head;
                    f2_head->f2_prev = ptr;
                }
                trailptr = ptr;
            }
            ptr = ptr->f1_next;
        } while (ptr != f1_head);
        cout << "\nChoose option:\n1. Display\n2. Filter further\n";
        cin >> choice;
        if (choice == '1')
        {
            filter_display(filtercount);
            return;
        }
        else
        {
            return;
        }
    }
    else
    {
        cout << "It is not possible to reach here!";
    }
}

//function to filter according to camera
void filter_camera(int filtercount)
{
    int find_camera_min, find_camera_max;
    char choice;
    cout << "Enter minimum camera pixels:";
    cin >> find_camera_min;
    cout << "Enter maximum camera pixels:";
    cin >> find_camera_max;
    if (filtercount == 1)
    {
        ifstream fin("mobiles.dat", ios::in);
        while (fin.read((char *)&temp, sizeof(temp)))
        {
            if ((temp.getcamera() >= find_camera_min) and (temp.getcamera() <= find_camera_max))
            {
                createcdll();
            }
            else
            {
                continue;
            }
        }
        fin.close();
        cout << "\nChoose option:\n1. Display\n2. Filter further\n";
        cin >> choice;
        if (choice == '1')
        {
            filter_display(filtercount);
            return;
        }
        else
        {
            return;
        }
    }
    else if (filtercount == 2)
    {
        //change f1_head,f1_prev and f1_next
        MobilePhone *ptr = head, *trailptr = head;

        do
        {
            if ((ptr->getcamera() >= find_camera_min) and (ptr->getcamera() <= find_camera_max))
            {
                if (f1_head == NULL) //first phone in filter
                {
                    f1_head = ptr;
                    ptr->f1_prev = ptr->f1_next = ptr;
                }
                else
                {
                    trailptr->f1_next = ptr;
                    ptr->f1_prev = trailptr;
                    ptr->f1_next = f1_head;
                    f1_head->f1_prev = ptr;
                }
                trailptr = ptr;
            }
            ptr = ptr->next;
        } while (ptr != head);
        cout << "\nChoose option:\n1. Display\n2. Filter further\n";
        cin >> choice;
        if (choice == '1')
        {
            filter_display(filtercount);
            return;
        }
        else
        {
            return;
        }
    }
    else if (filtercount == 3)
    {
        //change f2_head,f2_prev and f2_next
        MobilePhone *ptr = f1_head, *trailptr = f1_head;

        do
        {
            if ((ptr->getcamera() >= find_camera_min) and (ptr->getcamera() <= find_camera_max))
            {
                if (f2_head == NULL) //first phone in filter
                {
                    f2_head = ptr;
                    ptr->f2_prev = ptr->f2_next = ptr;
                }
                else
                {
                    trailptr->f2_next = ptr;
                    ptr->f2_prev = trailptr;
                    ptr->f2_next = f2_head;
                    f2_head->f2_prev = ptr;
                }
                trailptr = ptr;
            }
            ptr = ptr->f1_next;
        } while (ptr != f1_head);
        cout << "\nChoose option:\n1. Display\n2. Filter further\n";
        cin >> choice;
        if (choice == '1')
        {
            filter_display(filtercount);
            return;
        }
        else
        {
            return;
        }
    }
    else
    {
        cout << "It is not possible to reach here!";
    }
}

//function to filter according to price
void filter_price(int filtercount)
{
    float find_price_min, find_price_max;
    char choice;
    cout << "\nEnter minimum price:";
    cin >> find_price_min;
    cout << "\nEnter maximum price:";
    cin >> find_price_max;
    if (filtercount == 1)
    {
        ifstream fin("mobiles.dat", ios::in);
        while (fin.read((char *)&temp, sizeof(temp)))
        {
            if ((temp.getprice() >= find_price_min) and (temp.getprice() <= find_price_max))
            {
                createcdll();
            }
            else
            {
                continue;
            }
        }
        fin.close();
        cout << "\nChoose option:\n1. Display\n2. Filter further\n";
        cin >> choice;
        if (choice == '1')
        {
            filter_display(filtercount);
            return;
        }
        else
        {
            return;
        }
    }
    else if (filtercount == 2)
    {
        //change f1_head,f1_prev and f1_next
        MobilePhone *ptr = head, *trailptr = head;

        do
        {
            if ((ptr->getprice() >= find_price_min) and (ptr->getprice() <= find_price_max))
            {
                if (f1_head == NULL) //first phone in filter
                {
                    f1_head = ptr;
                    ptr->f1_prev = ptr->f1_next = ptr;
                }
                else
                {
                    trailptr->f1_next = ptr;
                    ptr->f1_prev = trailptr;
                    ptr->f1_next = f1_head;
                    f1_head->f1_prev = ptr;
                }
                trailptr = ptr;
            }
            ptr = ptr->next;
        } while (ptr != head);
        cout << "\nChoose option:\n1. Display\n2. Filter further\n";
        cin >> choice;
        if (choice == '1')
        {
            filter_display(filtercount);
            return;
        }
        else
        {
            return;
        }
    }
    else if (filtercount == 3)
    {
        //change f2_head,f2_prev and f2_next
        MobilePhone *ptr = f1_head, *trailptr = f1_head;

        do
        {
            if ((ptr->getprice() >= find_price_min) and (ptr->getprice() <= find_price_max))
            {
                if (f2_head == NULL) //first phone in filter
                {
                    f2_head = ptr;
                    ptr->f2_prev = ptr->f2_next = ptr;
                }
                else
                {
                    trailptr->f2_next = ptr;
                    ptr->f2_prev = trailptr;
                    ptr->f2_next = f2_head;
                    f2_head->f2_prev = ptr;
                }
                trailptr = ptr;
            }
            ptr = ptr->f1_next;
        } while (ptr != f1_head);
        cout << "\nChoose option:\n1. Display\n2. Filter further\n";
        cin >> choice;
        if (choice == '1')
        {
            filter_display(filtercount);
            return;
        }
        else
        {
            return;
        }
    }
    else
    {
        cout << "It is not possible to reach here!";
    }
}

//function to create cdll according to filter
void createcdll()
{
    MobilePhone *newnode = new MobilePhone(temp);
    if (head == NULL)
    {
        head = tail = newnode;
        newnode->next = newnode->prev = newnode;
    }
    else
    {
        tail->next = newnode;
        newnode->prev = tail;
        newnode->next = head;
        tail = newnode;
        head->prev = newnode;
    }
}

//function to delete cdll after user has completed filtering
void deletecdll()
{
    MobilePhone *ptr = head, *temp;
    while (ptr->next != head)
    {
        temp = ptr;
        ptr = ptr->next;
        delete temp;
    }
    delete tail;
    head = tail = f1_head = f2_head = NULL;
}

void addtocart()
{

    if (cart_head == NULL)
    {
        MobilePhone *newnode = new MobilePhone(temp);
        cart_head = cart_tail = newnode;
        newnode->next = newnode->prev = newnode;
        cout << "Phone successfully added to cart!\n";
    }
    else
    {
        //if mobile phone already exists in cart, don't add it as duplicates are not allowed
        int flag = 0;
        //checking if duplicate
        MobilePhone *ptr = cart_head;
        do
        {
            if (strcmpi(temp.getname(), ptr->getname()) == 0)
            {
                flag = 1;
                break;
            }
            else
            {
                ptr = ptr->next;
            }
        } while (ptr != cart_head);
        if (flag == 0) //if phone to be added is not duplicate
        {
            MobilePhone *newnode = new MobilePhone(temp);
            cart_tail->next = newnode;
            newnode->prev = cart_tail;
            newnode->next = cart_head;
            cart_tail = newnode;
            cart_head->prev = newnode;
            cout << "Phone successfully added to cart!\n";
        }
        else //if phone to be added is duplicate
        {
            cout << "Duplicates not allowed!\n";
        }
    }
}

void viewcart()
{
    char choice = 'N';
    MobilePhone *ptr = cart_head;
    while (choice != 'e' and choice != 'E')
    {
        if (cart_head == NULL)
        {
            cout << "\nCart is empty!";
            getch();
            break;
        }

        if (choice == 'n' or choice == 'N')
        {
            system("cls");
            ptr = ptr->next;
            cout << *ptr;
            //ptr->mobile_output();
        }

        else if (choice == 'p' or choice == 'P')
        {
            system("cls");
            ptr = ptr->prev;
            cout << *ptr;
            //ptr->mobile_output();
        }

        else if (choice == 'd' or choice == 'D')
        {
            char ch = 'Y';
            cout << "\n\nDo you want to delete this phone from the cart?(Y/N)\n";
            cin >> ch;
            if (ch == 'y' or ch == 'Y')
            {

                if (cart_head == cart_tail)
                {
                    delete ptr;
                    cart_head = cart_tail = NULL;
                    cout << "Phone successfully deleted!\n";
                    continue;
                }

                else if (ptr == cart_head)
                {
                    ptr->prev->next = ptr->next;
                    ptr->next->prev = ptr->prev;
                    MobilePhone *tempptr = ptr;
                    ptr = ptr->next;
                    cart_head = ptr;
                    delete tempptr;
                    cout << "Phone successfully deleted!\n";
                }

                else if (ptr == cart_tail)
                {
                    ptr->prev->next = ptr->next;
                    ptr->next->prev = ptr->prev;
                    MobilePhone *tempptr = ptr;
                    cart_tail = ptr->prev;
                    ptr = ptr->next;
                    delete tempptr;
                    cout << "Phone successfully deleted!\n";
                }

                else
                {
                    ptr->prev->next = ptr->next;
                    ptr->next->prev = ptr->prev;
                    MobilePhone *tempptr = ptr;
                    ptr = ptr->next;
                    delete tempptr;
                    cout << "Phone successfully deleted!\n";
                }
            }
            cout << "\n1. Press 'P' for previous mobile\n2. Press 'N' for next mobile\n3. Press 'E' to exit\n";
            choice = getche();
            continue;
            //cin >> choice;
        }

        else
        {
            break;
        }
        cout << "\n1. Press 'P' for previous mobile\n2. Press 'N' for next mobile\n3. Press 'D' to delete from cart\n4. Press 'E' to exit\n";
        choice = getche();
        //cin >> choice;
    }
    customer_menu();
}

void initcartcdllfromfile()
{
    ifstream fin("cart.dat", ios::in);
    if (!fin)
    {
        return;
    }
    while (fin.read((char *)&temp, sizeof(temp)))
    {
        addtocart();
    }
    fin.close();
}

void writecartcdlltofile()
{
    ofstream fout("cart.dat", ios::out | ios::trunc);
    if (cart_head == NULL)
    {
        fout.close();
        return;
    }
    else
    {
        MobilePhone *ptr = cart_head;
        do
        {
            fout.write((char *)&(*ptr), sizeof(*ptr));
            ptr = ptr->next;
        } while (ptr != cart_head);
        fout.close();
    }
}

//main function
int main()
{
    initcartcdllfromfile();
    main_menu();
    writecartcdlltofile();
    getch();
    return 0;
}