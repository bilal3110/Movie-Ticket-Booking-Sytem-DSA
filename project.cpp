#include <iostream>      // For Input/Output
#include <string>        // For String
#include <unordered_map> // Hash Tables
#include <vector>        // 2-D Array Vectors
#include <iomanip>       // For Table Spacing i.e stew
#include <regex>         // Email Authentication
#include <conio.h>       // Password Asteriks i.e getch_
#include <windows.h>     // Sleep Function
#include <cctype>        // For Cases in Alphabets
using namespace std;
class User
{
protected:
    unordered_map<string, pair<string, string>> user;

public:
    void clearConsole()
    {
#if defined(_WIN32) || defined(_WIN64)
        system("cls");
#else
        system("clear");
#endif
    }

    bool isValidEmail(const string &email)
    {
        const regex emailPattern(R"((^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$))");
        return regex_match(email, emailPattern);
    }

    string inputPassword()
    {
        string password;
        char ch;

        cout << "Enter Password (minimum 8 characters): ";
        while (true)
        {
            ch = _getch();

            if (ch == '\r')
            {
                break;
            }
            else if (ch == '\b')
            {
                if (!password.empty())
                {
                    password.pop_back();
                    cout << "\b \b";
                }
            }
            else
            {
                password.push_back(ch);
                cout << "*";
            }
        }

        cout << endl;

        if (password.length() < 8)
        {
            cout << "Error: Password must be at least 8 characters long. Please try again.\n";
            return inputPassword();
        }

        return password;
    }

    virtual string registerUser(const string &name, const string &phone, const string &email, const string &password)
    {
        if (user.find(email) != user.end())
        {
            return "Error: Email already registered.";
            string registerUser(const string &name, const string &phone, const string &email, const string &password);
        }
        user[email] = make_pair(name, password);
        return "Registration successful!";
    }

    bool loginUser(const string &email, const string &password)
    {
        auto it = user.find(email);
        if (it == user.end())
        {
            cout << "Error: Email not registered.\n";
            return false;
        }

        if (it->second.second == password)
        {
            cout << "Login successful! Welcome " << it->second.first << ".\n";
            return true;
        }
        else
        {
            return false;
        }
    }

    void handleRegistration()
    {
        cout << "-----------Register-----------" << endl;
        while (true)
        {
            string name, phone, email, password;
            cout << "Enter Name: ";
            cin.ignore();
            getline(cin, name);

            do
            {
                cout << "Enter Phone Number: ";
                cin >> phone;
                if (phone.length() != 11)
                {
                    cout << "Invalid Phone Number. Please enter a valid 11-digit phone number.\n";
                }
            } while (phone.length() != 11);

            do
            {
                cout << "Enter Email: ";
                cin >> email;
                for (char &c : email)
                {
                    c = tolower(c);
                }
                if (!isValidEmail(email))
                {
                    cout << "Error: Invalid email format. Please try again.\n";
                }
            } while (!isValidEmail(email));

            cin.ignore();
            password = inputPassword();
            cout << endl;

            string result = registerUser(name, phone, email, password);

            if (result == "Registration successful!")
            {
                cout << result << endl;
                break;
            }
            else
            {
                cout << result << " Please try again.\n";
            }
        }
    }

    bool handleLogin()
    {
        cout << "-----------Login-----------" << endl;
        string email, password;
        cout << "Enter Email: ";
        cin >> email;
        for (char &c : email)
        {
            c = tolower(c);
        }
        cin.ignore();
        password = inputPassword();
        cout << endl;

        cout << endl
             << loginUser(email, password) << endl;

        if (loginUser(email, password))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

class Admin : public User
{
protected:
    struct Movie
    {
        string name;
        string showTime[3];
        int price;
        int seats[3][5][5];
        Movie *next;

        Movie(string n, string s[], int p)
        {
            name = n;
            for (int i = 0; i < 3; i++)
            {
                showTime[i] = s[i];
                for (int row = 0; row < 5; row++)
                {
                    for (int col = 0; col < 5; col++)
                    {
                        seats[i][row][col] = 0;
                    }
                }
            }
            price = p;
            next = nullptr;
        }
    };

public:
    Admin()
    {
        user["bilal@email.com"] = make_pair("Bilal", "bilal123");
        user["amina@email.com"] = make_pair("Amina", "amina123");
    }

    Movie *head = NULL;
    Movie *tail = NULL;

    int insertMovie(string &name, string showTime[], int price)
    {
        Movie *newMovie = new Movie(name, showTime, price);
        if (head == NULL)
        {
            head = tail = newMovie;
        }
        else
        {
            tail->next = newMovie;
            tail = newMovie;
        }
    }

    void displaySeating(int seats[5][5])
    {
        cout << "\nSeat Layout (0 = Available, 1 = Booked):\n";
        for (int row = 0; row < 5; row++)
        {
            for (int col = 0; col < 5; col++)
            {
                cout << seats[row][col] << " ";
            }
            cout << endl;
        }
    }

    void generateTicket(const string &customerName, const string &movieName, const vector<pair<int, int>> &seats, int totalPrice, const string &showTime)
    {
        cout << "\n========== Movie Ticket ==========" << endl;
        cout << "Customer Name: " << customerName << endl;
        cout << "Movie Name: " << movieName << endl;
        cout << "Show Time: " << showTime << endl;
        cout << "Seats: ";
        for (const auto &seat : seats)
        {
            cout << "(" << seat.first + 1 << ", " << seat.second + 1 << ") ";
        }
        cout << "\nTotal Price: $" << totalPrice << endl;
        cout << "===================================\n";
    }

    void bookSeat(Movie *movie, int showTimeIndex, const string &customerName)
    {
        vector<pair<int, int>> bookSeats;
        int row, col, numberofSeats;

        cout << "Enter the Number Of Seats You Want Reserved: ";
        cin >> numberofSeats;

        for (int i = 0; i < numberofSeats; i++)
        {
            displaySeating(movie->seats[showTimeIndex]);

            cout << "Enter seat row (1-5): ";
            cin >> row;

            cout << "Enter seat column (1-5): ";
            cin >> col;

            int adjustedRow = row - 1;
            int adjustedCol = col - 1;

            if (row < 1 || row > 5 || col < 1 || col > 5 || movie->seats[showTimeIndex][adjustedRow][adjustedCol] == 1)
            {
                cout << "Invalid or already booked seat. Try again.\n";
                --i;
            }
            else
            {
                movie->seats[showTimeIndex][adjustedRow][adjustedCol] = 1;
                bookSeats.emplace_back(adjustedRow, adjustedCol);
                cout << "Seat (" << row << ", " << col << ") booked successfully.\n";
            }
        }

        int totalPrice = numberofSeats * movie->price;
        clearConsole();
        generateTicket(customerName, movie->name, bookSeats, totalPrice, movie->showTime[showTimeIndex]);
    }

    void selectMovieAndTime(const string &customerName)
    {
        displayMovies();
        int movieChoice, showTimeChoice;

        cout << "Enter the Sr No of the movie: ";
        cin >> movieChoice;

        Movie *selectedMovie = head;
        for (int i = 1; i < movieChoice && selectedMovie != NULL; i++)
        {
            selectedMovie = selectedMovie->next;
        }

        if (!selectedMovie)
        {
            cout << "Invalid movie choice.\n";
            return;
        }

        cout << "Select a show time:\n";
        for (int i = 0; i < 3; i++)
        {
            cout << i + 1 << ". " << selectedMovie->showTime[i] << endl;
        }
        cout << "Enter your choice: ";
        cin.ignore();
        cin >> showTimeChoice;

        if (showTimeChoice < 1 || showTimeChoice > 3)
        {
            cout << "Invalid show time choice.\n";
            return;
        }

        bookSeat(selectedMovie, showTimeChoice - 1, customerName);
    }

    void deleteMovie(int n)
    {
        if (head == NULL)
        {
            cout << "No movies to delete." << endl;
            return;
        }

        if (n <= 0)
        {
            cout << "Invalid position." << endl;
            return;
        }

        if (n == 1)
        {
            Movie *temp = head;
            head = head->next;

            if (head == NULL)
            {
                tail = NULL;
            }

            delete temp;
            return;
        }

        Movie *temp = head;
        for (int i = 1; i < n - 1; i++)
        {
            if (temp->next == NULL)
            {
                cout << "Position out of range." << endl;
                return;
            }
            temp = temp->next;
        }

        if (temp->next == NULL)
        {
            cout << "Position out of range." << endl;
            return;
        }

        Movie *toDelete = temp->next;
        temp->next = toDelete->next;

        if (toDelete == tail)
        {
            tail = temp;
        }

        delete toDelete;
    }

    void insert()
    {
        int choice;
        string name;
        string showTime[3];
        int price;

        do
        {
            cout << "1. Add a movie\n2. Display movies\n3. Delete Movie\n4. Add Admin\n5. Log Out\n";
            cout << "Enter your choice: ";
            cin >> choice;
            cin.ignore();

            switch (choice)
            {
            case 1:
                clearConsole();
                cout << "Enter movie name: ";
                getline(cin, name);

                for (int i = 0; i < 3; ++i)
                {
                    bool isDuplicate;
                    do
                    {
                        isDuplicate = false;
                        cout << "Enter Show Time " << i + 1 << " : ";
                        getline(cin, showTime[i]);

                        for (int j = 0; j < i; ++j)
                        {
                            if (showTime[i] == showTime[j])
                            {
                                isDuplicate = true;
                                cout << "Duplicate show time entered. Please enter a different time.\n";
                                break;
                            }
                        }
                    } while (isDuplicate);
                    cout << endl;
                }

                cout << "Enter ticket price: ";
                cin >> price;
                insertMovie(name, showTime, price);
                clearConsole();
                cout << "Movie added successfully.\n";
                break;

            case 2:
                clearConsole();
                cout << "Movie List:\n";
                displayMovies();
                break;

            case 3:
                clearConsole();
                cout << "Movie List:\n";
                displayMovies();
                int n;
                cout << endl
                     << "Enter Movie To Delete: ";
                cin >> n;
                deleteMovie(n);
                break;

            case 4:
                clearConsole();
                handleRegistration();
                break;

            case 5:
                clearConsole();
                cout << "Logging Out\n";
                break;

            default:
                cout << "Invalid choice! Try again.\n";
            }
        } while (choice != 5);
    }

    bool displayMovies()
    {
        Movie *temp = head;
        if (temp == NULL)
        {
            cout << "No movies in the list.\n";
            cout << "Press 1 to go back: ";
            int backChoice;
            cin >> backChoice;
            while (backChoice != 1)
            {
                cout << "Invalid input. Press 1 to go back: ";
                cin >> backChoice;
            }
            return false;
        }

        int srNo = 1;
        cout << left << setw(20) << "Sr No"
             << setw(20) << "Movie Name"
             << setw(15) << "Show Time 1"
             << setw(15) << "Show Time 2"
             << setw(15) << "Show Time 3"
             << setw(10) << "Price/USD" << endl;
        cout << string(95, '-') << endl;

        while (temp != NULL)
        {
            cout << left << setw(20) << srNo
                 << setw(20) << temp->name
                 << setw(15) << temp->showTime[0]
                 << setw(15) << temp->showTime[1]
                 << setw(15) << temp->showTime[2]
                 << setw(10) << temp->price << endl;
            temp = temp->next;
            srNo++;
        }
    }

    string registerUser(const string &name, const string &phone, const string &email, const string &password)
    {
        return User::registerUser(name, phone, email, password);
    }
};

class Customer : public User
{
public:
    string customerName;
    string registerUser(const string &name, const string &phone, const string &email, const string &password)
    {
        cout << "[Customer Registration]" << endl;
        customerName = name;
        return User::registerUser(name, phone, email, password);
    }

    string customerList()
    {
        cout << "[Customer List]" << endl;
        for (auto &it : user)
        {
            cout << it.first << " " << it.second.first << " " << it.second.second << endl;
        }
    }

    void userChoice(Admin &admin)
    {
        clearConsole();
        cout << "-----------Customer Menu-----------" << endl;
        int choice;
        do
        {
            cout << "1. View Movies\n2. Book Movie\n3. Back\n";
            cin >> choice;
            switch (choice)
            {
            case 1:
                clearConsole();
                admin.displayMovies();
                break;
            case 2:
                clearConsole();
                admin.selectMovieAndTime(customerName);
                break;
            case 3:
                clearConsole();
                cout << "Exit....";
                break;
            default:
                cout << "Invalid choice. Please choose a valid option.\n";
                break;
            }
        } while (choice != 3);
    }
};

int main()
{
    Customer customer;
    Admin admin;
    admin.clearConsole();
    cout << endl
         << endl
         << endl
         << endl
         << endl;
    cout << "\t\t\t\t\t WELCOME TO MOVIE TICKECT BOOKING SYSTEM!\n\n\n";
    Sleep(300);
    cout << "\n\n\t\t\t\t\t\tProject Prepared by:";
    Sleep(400);
    cout << "\n\n\t\t\t\t\t\t--------------------";
    Sleep(500);
    cout << "\n\n\t\t\t\t     Bilal Aqeel       2023-BS-SE-033";
    Sleep(1000);
    cout << "\n\n\t\t\t\t     Amina Ejaz        2023-BS-SE-076";
    Sleep(2000);
    cout << endl;
    system("cls");
    int choice;
    do
    {
        cout << "\n=== MOVIE TICKECT BOOKING SYSTEM ===" << endl;
        cout << "1. Customer\n2. Admin\n3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            customer.clearConsole();
            int customerChoice;
        CustomerSignup:
            customer.clearConsole();
            cout << "1. LogIn! If you already have an account\n2. Register! If you don't have an account\n";

            while (!(cin >> customerChoice) || (customerChoice != 1 && customerChoice != 2))
            {
                cin.clear();
                cin.ignore();
                cout << "Invalid choice. Please enter 1 to LogIn or 2 to Register: ";
            }

            if (customerChoice == 1)
            {
                while (true)
                {
                    if (customer.handleLogin())
                    {
                        customer.userChoice(admin);
                        break;
                    }
                    else
                    {
                        cout << "Invalid username or password. Try again.\n";
                    }
                }
            }
            else if (customerChoice == 2)
            {
                customer.handleRegistration();
                while (true)
                {
                    goto CustomerSignup;
                    break;
                }
            }
            break;

        case 2:
            admin.clearConsole();
            cout << "Please log in.\n";
            while (true)
            {
                if (admin.handleLogin())
                {   
                    admin.clearConsole();
                    admin.insert();
                    break;
                }
                else
                {
                    cout << "Invalid username or password. Try again.\n";
                }
            }
            break;
        case 3:
            admin.clearConsole();
            cout << "Exiting system. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 3);

    return 0;
}