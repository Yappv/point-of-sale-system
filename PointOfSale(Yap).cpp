#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class user {
private:
    string firstName;
    string lastName;
    string username;
    string password;
    string role;

public:
    string getFirstName(){
        return firstName;
    }
    string getLastName(){
        return lastName;
    }
    string getUsername(){
        return username;
    }
    string getPassword(){
        return password;
    }
    string getRole(){
        return role;
    }

    void setFirstName(string f){
        firstName = f;
    }
    void setLastName(string l){
        lastName = l;
    }
    void setUsername(string u){
        username = u;
    }
    void setPassword(string pw){
        password = pw;
    }
    void setRole(string r){
        role = r;
    }
};

class product{
private:
    string productName;
    int amount;
    float price;

public:
    string getProductName(){
        return productName;
    }
    int getAmount(){
        return amount;
    }
    float getPrice(){
        return price;
    }

    void setProductName(string pn){
        productName = pn;
    }
    void setAmount(int a){
        amount = a;
    }
    void setPrice(float pr){
        price = pr;
    }
};

int main()
{
    user authorization;
    product item;

    int choice, value, amount;
    float price, totalPrice, payment;
    char cashierOptions, adminOptions, itemOptions, userOptions, confirmation;
    string username, password, product, firstName, lastName, role, container, status;
    bool main, cashierMain, adminMain, optionsMain, paymentMain, login = false;

    main = true;
    while(main == true)
    {
        cout << "================================================" << endl;
        cout << " SELECT POSITION" << endl;
        cout << "================================================" << endl;
        cout << "(1) Cashier" << endl;
        cout << "(2) Administrator" << endl;
        cout << "(3) Terminate Program" << endl;
        cout << "================================================" << endl;
        cout << "> ";
        cin >> choice;

        switch(choice)
        {
            case 1:
            {
                login = false;
                cashierMain = true;
                while(cashierMain == true)
                {
                    while(login == false)
                    {
                        cout << "================================================" << endl;
                        cout << " CASHIER LOG-IN" << endl;
                        cout << "================================================" << endl;
                        cout << "Input Username: ";
                        cin >> username;
                        authorization.setUsername(username);
                        cout << "Input Password: ";
                        cin >> password;
                        authorization.setPassword(password);

                        ifstream readFile("userCashier_" + authorization.getUsername() + ".txt");
                        if(readFile.is_open())
                        {
                            string tempPassword;
                            getline(readFile, tempPassword);
                            if(authorization.getPassword() != tempPassword)
                            {
                                cout << "Incorrect Password" << endl;
                                readFile.close();
                                break;
                            }
                        }
                        readFile.close();
                        login = true;
                        cout << "User logged in" << endl;
                    }

                    cout << "================================================" << endl;
                    cout << " CASHIER OPTIONS" << endl;
                    cout << "================================================" << endl;
                    cout << "(S) Start a Sale" << endl;
                    cout << "(C) Check Item" << endl;
                    cout << "(X) Exit Cashier Options" << endl;
                    cout << "================================================" << endl;
                    cout << "> ";
                    cin >> cashierOptions;

                    switch(cashierOptions)
                    {
                        case 'S':
                        case 's':
                        {
                            cout << "================================================" << endl;
                            cout << "How many products to purchase?" << endl;
                            cout << "> ";
                            cin >> value;
                            cout << "================================================" << endl;

                            totalPrice = 0;
                            for (int i = 1; i <= value; i++)
                            {
                                cout << "Input Product #" << i << ": ";
                                cin >> product;
                                item.setProductName(product);

                                ifstream readFile("product_" + item.getProductName() + ".txt");
                                if(readFile.is_open())
                                {
                                    int tempAmount;
                                    getline(readFile, container);
                                    tempAmount = stof(container);
                                    float tempPrice;
                                    getline(readFile, container);
                                    tempPrice = stof(container);

                                    if(tempAmount > 0)
                                    {
                                        tempAmount = tempAmount - 1;
                                        totalPrice = totalPrice + tempPrice;
                                        ofstream writeFile("product_" + item.getProductName() + ".txt");
                                        writeFile << tempAmount << "\n";
                                        writeFile << tempPrice << "\n";
                                        writeFile.close();
                                    }
                                    else
                                    {
                                        cout << item.getProductName() << " is out of stock. Please purchase another product" << endl;
                                        i--;
                                    }
                                }
                                else
                                {
                                    cout << "Product does not exist" << endl;
                                    i--;
                                }
                                readFile.close();
                            }

                            cout << "================================================" << endl;
                            cout << "Number of Items: " << value << endl;
                            cout << "Total Price: P" << totalPrice << endl;
                            paymentMain = false;
                            while(paymentMain == false)
                            {
                                cout << "================================================" << endl;
                                cout << "Enter Payment: P";
                                cin >> payment;
                                if(payment >= totalPrice)
                                {
                                    cout << "Change: P" << payment - totalPrice << endl;
                                    paymentMain = true;
                                }
                                else
                                {
                                    cout << "Please Enter Appropriate Payment" << endl;
                                }
                            }
                            break;
                        }

                        case 'C':
                        case 'c':
                        {
                            cout << "================================================" << endl;
                            cout << "Input Product: ";
                            cin >> product;
                            item.setProductName(product);

                            ifstream readFile("product_" + item.getProductName() + ".txt");
                            if(readFile.is_open())
                            {
                                cout << "Displaying Information:" << endl;
                                int tempAmount;
                                getline(readFile, container);
                                tempAmount = stof(container);
                                float tempPrice;
                                getline(readFile, container);
                                tempPrice = stof(container);

                                cout << "Product: " << item.getProductName() << endl;
                                if(item.getAmount() > 0)
                                {
                                    cout << "Status: AVAILABLE" << endl;
                                }
                                else
                                {
                                    cout << "Status: NOT AVAILABLE" << endl;
                                }
                                cout << "Amount: " << tempAmount << endl;
                                cout << "Price: P" << tempPrice << endl;
                                readFile.close();
                            }
                            break;
                        }

                        case 'X':
                        case 'x':
                        {
                            cout << "================================================" << endl;
                            cout << "LOGGED OFF" << endl;
                            cashierMain = false;
                            break;
                        }

                        default:
                        {
                            cout << "Select a valid option" << endl;
                            break;
                        }
                    }
                }
                break;
            }

            case 2:
            {
                login = false;
                adminMain = true;
                while(adminMain == true)
                {
                    while(login == false)
                    {
                        cout << "================================================" << endl;
                        cout << "ADMINISTRATOR LOG-IN" << endl;
                        cout << "================================================" << endl;
                        cout << "Input Username: ";
                        cin >> username;
                        authorization.setUsername(username);
                        cout << "Input Password: ";
                        cin >> password;
                        authorization.setPassword(password);

                        ifstream readFile("userAdmin_" + authorization.getUsername() + ".txt");
                        if(readFile.is_open())
                        {
                            string tempPassword;
                            getline(readFile, tempPassword);
                            if(password != tempPassword)
                            {
                                cout << "Incorrect Password" << endl;
                                readFile.close();
                                break;
                            }
                        }
                        readFile.close();
                        login = true;
                        cout << "User logged in" << endl;
                    }

                    cout << "================================================" << endl;
                    cout << "ADMINISTRATOR OPTIONS" << endl;
                    cout << "================================================" << endl;
                    cout << "(I) Manage Items" << endl;
                    cout << "(U) Manage Users" << endl;
                    cout << "(X) Exit Administrator Options" << endl;
                    cout << "================================================" << endl;
                    cout << "> ";
                    cin >> adminOptions;

                    switch(adminOptions)
                    {
                        case 'I':
                        case 'i':
                        {
                            optionsMain = true;
                            while(optionsMain == true)
                            {
                                cout << "================================================" << endl;
                                cout << "ITEM OPTIONS" << endl;
                                cout << "================================================" << endl;
                                cout << "(A) Add Item" << endl;
                                cout << "(M) Modify Item" << endl;
                                cout << "(R) Remove Item" << endl;
                                cout << "(E) Exit Items Options" << endl;
                                cout << "================================================" << endl;
                                cout << "> ";
                                cin >> itemOptions;

                                switch(itemOptions)
                                {
                                    case 'A':
                                    case 'a':
                                    {
                                        cout << "================================================" << endl;
                                        cout << "New Product: ";
                                        cin >> product;
                                        item.setProductName(product);

                                        ifstream readFile("product_" + item.getProductName() + ".txt");
                                        if(readFile.is_open())
                                        {
                                            cout << "Product exists. Create another product" << endl;
                                            readFile.close();
                                            break;
                                        }
                                        cout << "Input Amount: ";
                                        cin >> amount;
                                        item.setAmount(amount);
                                        cout << "Input Price: ";
                                        cin >> price;
                                        item.setPrice(price);

                                        ofstream writeFile("product_" + item.getProductName() + ".txt");
                                        writeFile << item.getAmount() << "\n";
                                        writeFile << item.getPrice() << "\n";
                                        writeFile.close();
                                        cout << "Product successfully created" << endl;
                                        break;
                                    }

                                    case 'M':
                                    case 'm':
                                    {
                                        cout << "================================================" << endl;
                                        cout << "Input Product: ";
                                        cin >> product;
                                        item.setProductName(product);

                                        ifstream readFile("product_" + item.getProductName() + ".txt");
                                        if(readFile.is_open())
                                        {
                                            readFile.close();

                                            cout << "Modified Amount: ";
                                            cin >> amount;
                                            item.setAmount(amount);
                                            cout << "Modified Price: ";
                                            cin >> price;
                                            item.setPrice(price);

                                            ofstream writeFile("product_" + item.getProductName() + ".txt");
                                            writeFile << item.getAmount() << "\n";
                                            writeFile << item.getAmount() << "\n";
                                            writeFile.close();
                                            cout << "Product modified" << endl;
                                        }
                                        else
                                        {
                                            cout << "Product does not exist" << endl;
                                        }
                                        break;
                                    }

                                    case 'R':
                                    case 'r':
                                    {
                                        cout << "================================================" << endl;
                                        cout << "Input Product: ";
                                        cin >> product;
                                        item.setProductName(product);

                                        ifstream readFile("product_" + item.getProductName() + ".txt");
                                        if(readFile.is_open())
                                        {
                                            readFile.close();
                                            cout << "Deleted file cannot be restored. Continue (Y)? ";
                                            cin >> confirmation;
                                            if (confirmation == 'Y' || confirmation == 'y')
                                            {
                                                string tempProduct = "product_" + item.getProductName() + ".txt";
                                                const char* deleteProduct = tempProduct.c_str();
                                                remove(deleteProduct);
                                                cout << "Product deleted" << endl;
                                            }
                                            else
                                            {
                                                cout << "Product has not been deleted" << endl;
                                            }
                                        }
                                        else
                                        {
                                            cout << "Product does not exist" << endl;
                                        }
                                        break;
                                    }

                                    case 'E':
                                    case 'e':
                                    {
                                        cout << "RETURNING TO ADMINISTRATOR OPTIONS" << endl;
                                        optionsMain = false;
                                        break;
                                    }
                                    default:
                                    {
                                        cout << "Select a valid option" << endl;
                                        break;
                                    }
                                }
                            }
                            break;
                        }

                        case 'U':
                        case 'u':
                        {
                            optionsMain = true;
                            while(optionsMain == true)
                            {
                                cout << "================================================" << endl;
                                cout << "USER OPTIONS" << endl;
                                cout << "================================================" << endl;
                                cout << "(A) Add User" << endl;
                                cout << "(M) Modify User" << endl;
                                cout << "(R) Remove User" << endl;
                                cout << "(E) Exit User Options" << endl;
                                cout << "================================================" << endl;
                                cout << "> ";
                                cin >> userOptions;

                                switch(userOptions)
                                {
                                    case 'A':
                                    case 'a':
                                    {
                                        cout << "================================================" << endl;
                                        cout << "Assign Role (Cashier/Admin): ";
                                        cin >> role;
                                        authorization.setRole(role);
                                        cout << "New Username: ";
                                        cin >> username;
                                        cin.ignore();
                                        authorization.setUsername(username);
                                        ifstream readFile("user" + authorization.getRole() + "_" + authorization.getUsername() + ".txt");
                                        if(readFile.is_open())
                                        {
                                            cout << "File exists. Create another username" << endl;
                                            readFile.close();
                                            break;
                                        }
                                        cout << "New Password: ";
                                        cin >> password;
                                        cin.ignore();
                                        authorization.setPassword(password);
                                        cout << "New First Name: ";
                                        getline(cin, firstName);
                                        authorization.setFirstName(firstName);
                                        cout << "New Last Name: ";
                                        getline(cin, lastName);
                                        authorization.setLastName(lastName);

                                        ofstream writeFile("user" + authorization.getRole() + "_" + authorization.getUsername() + ".txt");
                                        writeFile << authorization.getPassword() << "\n";
                                        writeFile << authorization.getFirstName() << "\n";
                                        writeFile << authorization.getLastName() << "\n";
                                        writeFile.close();
                                        cout << "User successfully created" << endl;
                                        break;
                                    }

                                    case 'M':
                                    case 'm':
                                    {
                                        cout << "================================================" << endl;
                                        cout << "Input Username: ";
                                        cin >> username;
                                        cin.ignore();
                                        authorization.setUsername(username);

                                        ifstream readFile("user" + authorization.getRole() + "_" + authorization.getUsername() + ".txt");
                                        if(readFile.is_open())
                                        {
                                            readFile.close();

                                            cout << "Modify Password: ";
                                            cin >> password;
                                            cin.ignore();
                                            authorization.setPassword(password);
                                            cout << "Modify First Name: ";
                                            getline(cin, firstName);
                                            authorization.setFirstName(firstName);
                                            cout << "Modify Last Name: ";
                                            getline(cin, lastName);
                                            authorization.setLastName(lastName);

                                            ofstream writeFile("user" + authorization.getRole() + "_" + authorization.getUsername() + ".txt");
                                            writeFile << authorization.getPassword() << "\n";
                                            writeFile << authorization.getFirstName() << "\n";
                                            writeFile << authorization.getLastName() << "\n";
                                            writeFile.close();
                                            cout << "Data Modified" << endl;
                                        }
                                        else
                                        {
                                            cout << "User does not exist" << endl;
                                        }
                                        break;
                                    }

                                    case 'R':
                                    case 'r':
                                    {
                                        cout << "================================================" << endl;
                                        cout << "Input Username: ";
                                        cin >> username;
                                        cin.ignore();
                                        authorization.setUsername(username);
                                        cout << "Input Role: ";
                                        cin >> role;
                                        cin.ignore();
                                        authorization.setRole(role);

                                        ifstream readFile("user" + authorization.getRole()  + "_" + authorization.getUsername() + ".txt");
                                        if(readFile.is_open())
                                        {
                                            readFile.close();
                                            cout << "Deleted file cannot be restored. Continue (Y)? ";
                                            cin >> confirmation;
                                            if (confirmation == 'Y' || confirmation == 'y')
                                            {
                                                string tempUsername = "user" + authorization.getRole() + "_" + authorization.getUsername() + ".txt";
                                                const char* deleteUsername = tempUsername.c_str();
                                                remove(deleteUsername);
                                                cout << "User deleted" << endl;
                                            }
                                            else
                                            {
                                                cout << "User has not been deleted" << endl;
                                            }
                                        }
                                        else
                                        {
                                            cout << "File does not exist" << endl;
                                        }
                                        break;
                                    }

                                    case 'E':
                                    case 'e':
                                    {
                                        cout << "================================================" << endl;
                                        cout << "RETURNING TO ADMINISTRATOR OPTIONS" << endl;
                                        optionsMain = false;
                                        break;
                                    }

                                    default:
                                    {
                                        cout << "Select a valid option" << endl;
                                        break;
                                    }
                                }
                            }
                            break;
                        }

                        case 'X':
                        case 'x':
                        {
                            cout << "================================================" << endl;
                            cout << "LOGGED OFF" << endl;
                            adminMain = false;
                            break;
                        }

                        default:
                        {
                            cout << "Select a valid option" << endl;
                            break;
                        }
                    }
                }
                break;
            }

            case 3:
            {
                cout << "================================================" << endl;
                cout << "Program Terminated" << endl;
                cout << "================================================";
                main = false;
                break;
            }

            default:
            {
                cout << "Select a valid option" << endl;
                break;
            }
        }
    }
    return 0;
}
