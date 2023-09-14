// LIBRARY MANAGEMENT SYSTEM
#include <iostream> // For operations like cout, cin, and cerr
#include <fstream> // For file handling
#include <string> // For functions like find which is used to search for a specific string within a file
#include <vector> // Similar to arrays but dynamic and automatically resiable
#include <cstdio>
#include <windows.h> // For foreground and background color
#include<conio.h> // Used in this code to take password as sterics
#include <sstream>
#include <ctime>
#include <iomanip>

using namespace std;

class Book {
protected:
    const string BOOK_FILE = "book_data.txt";
    vector<Book> bookVector;
    string title, author, genre, isbn, year;
    bool available; // Attribute to track availability status
public:
    Book() = default;
    // Parameterized Constructor to initialize the Book class members
    Book(const string& title, const string& author, const string& genre, const string& isbn, const string& year, bool available = true) :
        title(title), author(author), genre(genre), isbn(isbn), year(year), available(available) {}

    void loadBooks()
    {
        ifstream file(BOOK_FILE);
        if (file.is_open())
        {
            string line;
            while (getline(file, line))
            {
                istringstream iss(line);
                string title, author, genre, isbn, year, availability;
                // Extraction of Data from file, while accounting for delimters
                if (getline(iss, title, '|') && getline(iss, author, '|') && getline(iss, genre, '|') && getline(iss, isbn, '|') && getline(iss, year, '|') && getline(iss, availability))
                {
                    Book book{ title, author, genre, isbn, year };
                    book.available = (availability == "1");
                    bookVector.push_back(book);
                }
            }
            file.close();
        }
        else
            cout << "Error: Unable to open file for load book data." << endl;
    }

    void saveBooks()
    {
        ofstream file(BOOK_FILE);
        if (file.is_open())
        {
            // Insertion of Data into file as per the specified format
            for (const Book& book : bookVector)
            {
                file << book.title << '|' << book.author << '|' << book.genre << '|' << book.isbn << '|' << book.year << '|' << (book.available ? "1" : "0") << '\n';
            }
            file.close();
        }
        else
            cerr << "Error: Unable to open file for saving book data." << endl;
    }

    void addBook()
    {
        string title, author, genre, isbn, year;
        cout << endl;
        cout << "----- Add Book -----" << endl;
        cout << "Title: ";
        getline(cin, title);

        cout << "Author: ";
        getline(cin, author);

        cout << "Genre: ";
        getline(cin, genre);

        cout << "ISBN: ";
        getline(cin, isbn);

        cout << "Year: ";
        getline(cin, year);

        // Ask for availability status
        string availabilityChoice;
        cout << "Availability (1 = Available, 0 = Not Available): ";
        getline(cin, availabilityChoice);
        bool available = (availabilityChoice == "1");

        // Create a new Book object with the provided information
        Book newBook{ title, author, genre, isbn, year, available };
        bookVector.push_back(newBook);
        saveBooks();// Save the updated book data to book_data file

        cout << "Book added successfully!" << endl;
    }

    void displayBook(const Book& book)
    {
        cout << "Title: " << book.title << endl;
        cout << "Author: " << book.author << endl;
        cout << "Genre: " << book.genre << endl;
        cout << "ISBN: " << book.isbn << endl;
        cout << "Year: " << book.year << endl;
        cout << "Availability: " << (book.available ? "Available" : "Not Available") << endl;
        cout << endl;
    }
    bool validateBook(string s1, string s2)
    {
        bool found = false; // Intialized to false
        for (const Book& book : bookVector)
        { // Iterate through books vector
            if (book.title.find(s1) != string::npos && book.author.find(s2) != string::npos)
            {
                found = true; // Set bool found to true
            }
        }
        return found;
    }

    void searchBook()
    {
        string searchQuery;
        cout << "----- Search Book -----" << endl;
        cout << "Enter title or ISBN: ";
        getline(cin, searchQuery);

        bool found = false; // Initialized to false

        for (const Book& book : bookVector)
        {
            if (book.title.find(searchQuery) != string::npos ||
                book.isbn.find(searchQuery) != string::npos)
            {
                displayBook(book);
                found = true;
                break;
            }
        }

        if (!found)
        {
            cout << "No matching books found." << endl;
        }
    }

    void deleteBook()
    {
        string searchQuery;
        cout << "----- Delete Book -----" << endl;
        cout << "Enter title or ISBN of the book to delete: ";
        getline(cin, searchQuery);

        vector<Book> booksToKeep;
        bool found = false;

        for (const Book& book : bookVector) {
            if (book.title.find(searchQuery) != string::npos ||
                book.isbn.find(searchQuery) != string::npos)
            {
                found = true; // Mark that a book to delete has been found
            }
            else {
                booksToKeep.push_back(book); // Add the book to keep to the new vector
            }
        }
        bookVector.clear();
        if (found) {
            for (const Book& tempBook : booksToKeep)
            {
                bookVector.push_back(tempBook);
            }
            saveBooks();
            cout << "Book deleted successfully!" << endl;
        }
        else {
            cout << "No matching books found." << endl;
        }
    }

    void updateBook()
    {
        string searchQuery;
        cout << "----- Update Book -----" << endl;
        cout << "Enter title or ISBN of the book to update: ";
        getline(cin, searchQuery);

        bool found = false;
        vector<Book>::iterator it;

        for (it = bookVector.begin(); it != bookVector.end(); ++it)
        {
            if (it->title.find(searchQuery) != string::npos ||
                it->isbn.find(searchQuery) != string::npos)
            {
                found = true;
                break;
            }
        }

        if (found)
        {
            string title, author, genre, isbn, year;

            cout << endl;
            cout << "Enter new information for the book. Leave blank to keep the existing information." << endl;
            cout << "Title: ";
            getline(cin, title);

            cout << "Author: ";
            getline(cin, author);

            cout << "Genre: ";
            getline(cin, genre);

            cout << "ISBN: ";
            getline(cin, isbn);

            cout << "Year: ";
            getline(cin, year);

            if (!title.empty())
            {
                it->title = title;
            }

            if (!author.empty())
            {
                it->author = author;
            }

            if (!genre.empty())
            {
                it->genre = genre;
            }

            if (!isbn.empty())
            {
                it->isbn = isbn;
            }

            if (!year.empty()) {
                it->year = year;
            }

            saveBooks();
            cout << "Book updated successfully!" << endl;
        }
        else
        {
            cout << "No matching books found." << endl;
        }

    }


    void handleSetAvailability()
    {
        string searchQuery;
        cout << "----- Set Availability Status -----" << endl;
        cout << "Enter title, author, genre, or ISBN of the book to update availability: ";
        getline(cin, searchQuery);

        bool found = false;
        vector<Book>::iterator it;

        for (it = bookVector.begin(); it != bookVector.end(); ++it)
        { // Iterates through the vector
            if (it->title.find(searchQuery) != string::npos ||
                it->author.find(searchQuery) != string::npos ||
                it->genre.find(searchQuery) != string::npos ||
                it->isbn.find(searchQuery) != string::npos)
            {
                found = true;
                break; // Exits the loop
            }
        }

        if (found)
        {// if a match is found
            string availabilityChoice;

            cout << endl;
            cout << "Availability: " << (it->available ? "Available" : "Not Available") << endl;
            cout << "Set availability (1 = Available, 0 = Not Available): ";
            getline(cin, availabilityChoice);

            if (availabilityChoice == "1") {
                it->available = true;
            }
            else if (availabilityChoice == "0") {
                it->available = false;
            }
            else {
                cout << "Invalid choice. Availability status remains unchanged." << endl;
            }

            saveBooks();
            cout << "Availability status updated successfully!" << endl;
        }
        else
        {
            cout << "No matching books found." << endl;
        }

    }

    void displayAllBooks()
    {
        cout << "----- All Books -----" << endl;

        if (bookVector.empty())
            cout << "No books available." << endl;
        else
        {
            for (const Book& book : bookVector)
            {
                displayBook(book);
            }
        }
    }
};
class BorrowedBook :public Book
{
private:
    const string BORROWEDBOOK_FILE = "borrowedbooks_data.txt";
    vector<BorrowedBook> borrowedBookVector;
    string borrowerId;
    string dueDate;
    string issueDate;
    string fines;
public:
    BorrowedBook() = default;
    void setVals(string s1, string s2, string s3, string s4, string s5, string f)
    {
        borrowerId = s1;
        title = s2;
        isbn = s3;
        issueDate = s4;
        dueDate = s5;
        fines = f;
    }

    void loadBorrowedBooks()
    {
        ifstream file(BORROWEDBOOK_FILE);
        if (file.is_open())
        {
            string line;
            while (getline(file, line))
            {
                istringstream iss(line);
                string tborrowerId, ttitle, tisbn, tissueDate, tdueDate, tfines;
                if (getline(iss, tborrowerId, '|') && getline(iss, ttitle, '|') && getline(iss, tisbn, '|') && getline(iss, tissueDate, '|') && getline(iss, tdueDate, '|') && getline(iss, tfines))
                {
                    BorrowedBook tempBorrowedBook;
                    tempBorrowedBook.setVals(tborrowerId, ttitle, tisbn, tissueDate, tdueDate, tfines);
                    borrowedBookVector.push_back(tempBorrowedBook);
                }
            }
            file.close();
        }
        else
            cerr << "Error: Unable to open file for loading book data." << endl;
    }

    void saveBorrowedBooks()
    {
        ofstream file(BORROWEDBOOK_FILE);
        if (file.is_open())
        {
            for (const BorrowedBook& newBorrowedBook : borrowedBookVector)
            {
                file << newBorrowedBook.borrowerId << '|' << newBorrowedBook.title << '|' << newBorrowedBook.isbn << '|' <<
                    newBorrowedBook.issueDate << '|' << newBorrowedBook.dueDate << '|' << newBorrowedBook.fines << '\n';
            }
            file.close();
        }
        else
            cerr << "Error: Unable to open file for saving book data." << endl;
    }
    bool validateBorrowedBook(string s1, string s2)
    {
        bool found = false;
        for (const BorrowedBook& borrowedbook : borrowedBookVector)
        { // Iterate through books vector
            if (borrowedbook.borrowerId.find(s1) != string::npos &&
                borrowedbook.title.find(s2) != string::npos)
            {
                found = true;
            }
        }
        return found;
    }

    string getCurrentDate()
    {
        time_t now = time(0);
        struct tm tstruct;
        char buf[80];
        tstruct = *localtime(&now);
        strftime(buf, sizeof(buf), "%d/%m/%Y", &tstruct);
        return string(buf);
    }

    string getDueDate()
    {
        time_t currentTime = time(nullptr);

        // Add 30 days (30 * 24 * 60 * 60 seconds) to the current time
        time_t futureTime = currentTime + (30 * 24 * 60 * 60);

        // Convert the future time to a string
        std::tm* futureTm = std::localtime(&futureTime);
        char buffer[80];
        strftime(buffer, sizeof(buffer), "%d/%m/%Y", futureTm);
        return string(buffer);
    }

    std::string calculateFine()
    {
        const int secondsPerDay = 24 * 60 * 60;
        const double baseFine = 20.0;
        const double finePerDay = 10.0;

        std::string currentDate = getCurrentDate();
        std::string dueDate = getDueDate();

        // Perform the fine calculation based on the current date and due date
        std::tm currentTm = {};
        std::tm dueTm = {};

        std::istringstream(currentDate) >> std::get_time(&currentTm, "%d/%m/%Y");
        std::istringstream(dueDate) >> std::get_time(&dueTm, "%d/%m/%Y");

        std::time_t currentTime = std::mktime(&currentTm);
        std::time_t dueTime = std::mktime(&dueTm);

        double secondsPassed = std::difftime(currentTime, dueTime);
        double daysPassed = secondsPassed / secondsPerDay;
        double additionalFine = daysPassed * finePerDay;
        double totalFine = baseFine + additionalFine;

        std::string fine = std::to_string(totalFine);
        return fine;
    }


    void addBorrowBook(string s1, string s2, string s3)
    {
        if (s1 != "" && s2 != "" && s3 != "")
        {
            BorrowedBook newBook;
            string borrowedDate = getCurrentDate();
            string dueDate = getDueDate();
            newBook.setVals(s1, s2, s3, borrowedDate, dueDate, "0.00");
            borrowedBookVector.push_back(newBook);
            saveBorrowedBooks();// Save the updated book data to book_data file
            system("CLS");
            cout << "Book borrowed successfully!" << endl;
        }
        else
        {
            system("CLS");
            cout << "No field should be left empty!" << endl;
        }


    }

    void displayBorrowedBook(const BorrowedBook& b)
    {
        ;
    }
    bool displayBorrowedBooks(string s)
    {
        cout << "----- Borrowed Books of " << s << " -----" << endl;
        bool found = false;

        for (const BorrowedBook& borrowedbook : borrowedBookVector)
        {
            if (borrowedbook.borrowerId.find(s) != string::npos)
            {
                cout << "Borrower's Id: " << borrowedbook.borrowerId << endl
                    << "Borrowed Book Title: " << borrowedbook.title << endl
                    << "Date of Issue: " << borrowedbook.issueDate << endl
                    << "Due Date: " << borrowedbook.dueDate << endl
                    << "Fine: " << borrowedbook.fines << endl << endl;
                found = true;
            }
        }

        if (!found)
        {
            cout << "No books are borrowed by this Id." << endl;
        }
        return found;
    }
    void renewBook(string s1, string s2)
    {
        bool found = false;
        vector<BorrowedBook>::iterator it;

        for (it = borrowedBookVector.begin(); it != borrowedBookVector.end(); ++it)
        {
            if (it->borrowerId.find(s1) != string::npos &&
                it->title.find(s2) != string::npos)
            {
                found = true;
                break;
            }
        }

        if (found)
        {
            it->issueDate = getCurrentDate();
            it->dueDate = getDueDate();
            it->fines = "0.00";
            saveBorrowedBooks();
        }
        else
        {
            cout << "There was some problem in renewing the book." << endl;
        }
    }
    void returnBook(string s1, string s2)
    {
        vector<BorrowedBook> booksToKeep;
        bool found = false;

        for (const BorrowedBook& borrowedbook : borrowedBookVector) {
            if (borrowedbook.borrowerId.find(s1) != string::npos &&
                borrowedbook.title.find(s2) != string::npos)
            {
                found = true; // Mark that a book to delete has been found
            }
            else {
                booksToKeep.push_back(borrowedbook); // Add the book to keep to the new vector
            }
        }
        borrowedBookVector.clear();
        if (found) {
            for (const BorrowedBook& tempBook : booksToKeep)
            {
                borrowedBookVector.push_back(tempBook);
            }
            saveBorrowedBooks();
        }
        else
        {
            cout << "No matching books found." << endl;
        }
    }
};

class Student
{
private:
    const string STUDENT_FILE = "student_data.txt";
    vector<Student> stuVector;
    string name;
    string id;
    string email;
    string password;
    string rollNo;
public:
    Student() = default; // Default Constructor

    // Set Function
    void setVals(string& Name, string& ID, string& Email, string& Password, string& RollNo)
    {
        name = Name;
        id = ID;
        email = Email;
        password = Password;
        rollNo = RollNo;
    }
    void loadStudents()
    {
        ifstream file(STUDENT_FILE);
        if (file.is_open())
        {
            string line;
            while (getline(file, line))
            {
                istringstream iss(line);
                string name, id, email, password, rollNo;
                if (getline(iss, name, '|') && getline(iss, id, '|') && getline(iss, email, '|')
                    && getline(iss, password, '|') && getline(iss, rollNo))
                {
                    Student tempStudent;
                    tempStudent.setVals(name, id, email, password, rollNo);
                    stuVector.push_back(tempStudent);
                }
            }
            file.close();
        }
        else
            cerr << "Error: Unable to open file for loading student data." << endl;
    }

    void saveStudents()
    {
        ofstream file(STUDENT_FILE);
        if (file.is_open())
        {
            for (const Student& tempStudent : stuVector)
            {
                file << tempStudent.name << '|' << tempStudent.id << '|' << tempStudent.email << '|' << tempStudent.password << '|' << tempStudent.rollNo << '\n';
            }
            file.close();
        }
        else
            cerr << "Error: Unable to open file for saving student data." << endl;
    }

    string handleStuLogin()
    {
        string checker = "";
        string tempId, tempPassword;
        cout << "----- Student Login -----" << endl;
        cout << "Enter ID: ";
        getline(cin, tempId);

        cout << "Enter Password: ";

        // Hide the password input with asterisks
        char ch;
        while ((ch = _getch()) != '\r')
        { // Read characters until Enter is pressed
            if (ch == '\b')
            { // Handle backspace
                if (!tempPassword.empty())
                {
                    cout << "\b \b"; // Move cursor back, erase character, move cursor back again
                    tempPassword.pop_back(); // Remove the last character from the password string
                }
            }
            else
            {
                cout << '*'; // Print asterisk for each character
                tempPassword.push_back(ch); // Add the character to the password string
            }
        }
        cout << endl; // Move to the next line

        for (const Student& student : stuVector)
        { // Iterates over librarian vector
            if (student.id == tempId && student.password == tempPassword)
            {
                checker = student.id;
                break;
            }

        }
        return checker;
    }
    bool validateStudent(string s1)
    {
        bool found = false;
        for (const Student& student : stuVector)
        { // Iterate through student vector
            if (student.id.find(s1) != string::npos)
            {
                found = true;
            }
        }
        return found;
    }
    void registerNewStudent()
    {
        string name, id, email, password, rollNo;
        cout << "----- Registration -----" << endl;
        cout << "Name: ";
        getline(cin, name);

        cout << "ID: ";
        getline(cin, id);

        cout << "Email: ";
        getline(cin, email);

        cout << "Password: ";
        getline(cin, password);

        cout << "rollNo: ";
        getline(cin, rollNo);

        Student newStudent;
        newStudent.setVals(name, id, email, password, rollNo);
        stuVector.push_back(newStudent);// Add the new Librarian object to the librarians vector
        saveStudents(); // Save the updated librarian data to file
        system("CLS");
        cout << "New Student registered successfully!" << endl;
    }


    void viewStudentProfile()
    {
        string searchQuery;
        cout << "----- View Students profiles -----" << endl;
        cout << "Enter student ID: ";
        getline(cin, searchQuery);
        bool found = false;

        for (const Student& student : stuVector)
        {
            if (student.id == searchQuery)
            {
                cout << "Student Name: " << student.name << endl
                    << "Student Id: " << student.id << endl
                    << "Student Email: " << student.email << endl
                    << "Student Roll No.: " << student.rollNo << endl;
                found = true;
                break;
            }
        }

        if (!found)
            cout << "No matching students found." << endl;
    }
    void viewStudentProfile(string userId) {

        cout << "----- Your profile -----" << endl;
        bool found = false;

        for (const Student& student : stuVector)
        {
            if (student.name == userId)
            {
                cout << "Your Name: " << student.name << endl
                    << "Your Id: " << student.id << endl
                    << "Your Email: " << student.email << endl
                    << "Your Roll No.: " << student.rollNo << endl;
                found = true;
                break;
            }
        }

        if (!found)
            cout << "No matching student found." << endl;
    }

    void updateStudent()
    {
        string searchQuery;

        cout << endl;
        cout << "----- Update Student -----" << endl;
        cout << "Enter ID of the student to update the profile: ";
        getline(cin, searchQuery);

        bool found = false;
        vector<Student>::iterator it;

        for (it = stuVector.begin(); it != stuVector.end(); ++it)
        {
            if (it->id.find(searchQuery) != string::npos)
            {
                found = true;
                break;
            }
        }

        if (found)
        {
            string name, id, email, rollNo;

            cout << endl;
            cout << "Enter new information for the Student. Leave blank to keep the existing information." << endl;
            cout << "Name: ";
            getline(cin, name);

            cout << "ID: ";
            getline(cin, id);

            cout << "Email: ";
            getline(cin, email);

            cout << "Roll No.: ";
            getline(cin, rollNo);

            // If 'not empty', assign value to variable
            if (!name.empty())
            {
                it->name = name;
            }

            if (!id.empty())
            {
                it->id = id;
            }

            if (!email.empty())
            {
                it->email = email;
            }

            if (!rollNo.empty())
            {
                it->rollNo = rollNo;
            }
            saveStudents();
            cout << "Student Profile updated successfully!" << endl;
        }
        else
        {
            cout << "No matching student found." << endl;
        }

    }
    void deleteStudent()
    {
        string searchQuery;
        cout << "----- Delete Student -----" << endl;
        cout << "Enter id of student to delete the profile: ";
        getline(cin, searchQuery);

        vector<Student> studentsToKeep;
        bool found = false;

        for (const Student& student : stuVector) {
            if (student.id.find(searchQuery) != string::npos)
            {
                found = true; // Mark that a book to delete has been found
            }
            else {
                studentsToKeep.push_back(student); // Add the book to keep to the new vector
            }
        }
        stuVector.clear();
        if (found) {
            for (const Student& tempStudent : studentsToKeep)
            {
                stuVector.push_back(tempStudent);
            }
            saveStudents();
            cout << "Student Profile deleted successfully!" << endl;
        }
        else {
            cout << "No matching student found." << endl;
        }
    }
};


class Librarian
{
private:
    const string LIBRARIAN_FILE = "librarian_data.txt";
    vector<Librarian> libVector;
    string name, id, email, password, accessPassword;
public:
    Librarian() = default; // Default Constructor

    void setVals(string& Name, string& ID, string& Email, string& Password)
    {
        name = Name;
        id = ID;
        email = Email;
        password = Password;
    }
    void loadLibrarians()
    {
        ifstream file(LIBRARIAN_FILE);
        if (file.is_open())
        {
            string line;
            while (getline(file, line))
            {
                istringstream iss(line);
                string name, id, email, password;
                if (getline(iss, name, '|') && getline(iss, id, '|') && getline(iss, email, '|') && getline(iss, password))
                {
                    Librarian templibrarian;
                    templibrarian.setVals(name, id, email, password);
                    libVector.push_back(templibrarian);
                }
            }
            file.close();
        }
        else
            cerr << "Error: Unable to open file for loading librarian data." << endl;
    }

    void saveLibrarians()
    {
        ofstream file(LIBRARIAN_FILE);
        if (file.is_open())
        {
            for (const Librarian& templibrarian : libVector)
            {
                file << templibrarian.name << '|' << templibrarian.id << '|' << templibrarian.email << '|' << templibrarian.password << '\n';
            }
            file.close();
        }
        else
            cerr << "Error: Unable to open file for saving librarian data." << endl;
    }

    string validateAccess()
    {
        string checker = "0";
        cout << "Enter the verification key to access the Librarian Portal: ";
        getline(cin, accessPassword);
        if (accessPassword == "NED123")
            checker = "1";
        system("CLS");
        return checker;
    }

    string libPortalMenu()
    {
        string checker;
        cout << "----- Librarian's Portal Menu -----" << endl;
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        cout << "Enter your choice: ";

        getline(cin, checker);
        system("CLS");
        return checker;

    }
    string handleLibLogin()
    {
        string checker = "";
        string tempId, tempPassword;
        cout << "----- Librarian Login -----" << endl;
        cout << "Enter Librarian ID: ";
        getline(cin, tempId);

        cout << "Enter Password: ";

        // Hide the password input with asterisks
        char ch;
        while ((ch = _getch()) != '\r')
        { // Read characters until Enter is pressed
            if (ch == '\b')
            { // Handle backspace
                if (!tempPassword.empty())
                {
                    cout << "\b \b"; // Move cursor back, erase character, move cursor back again
                    tempPassword.pop_back(); // Remove the last character from the password string
                }
            }
            else
            {
                cout << '*'; // Print asterisk for each character
                tempPassword.push_back(ch); // Add the character to the password string
            }
        }
        cout << endl; // Move to the next line

        for (const Librarian& librarian : libVector)
        { // Iterates over librarian vector
            if (librarian.id == tempId && librarian.password == tempPassword)
            {
                checker = librarian.id;
                break;
            }

        }
        system("CLS");
        return checker;
    }
    void handleRegistration()
    {
        string name, id, email, password;
        cout << "----- Registration -----" << endl;
        cout << "Name: ";
        getline(cin, name);

        cout << "ID: ";
        getline(cin, id);

        cout << "Email: ";
        getline(cin, email);

        cout << "Password: ";
        getline(cin, password);

        Librarian newLibrarian;
        newLibrarian.setVals(name, id, email, password);
        libVector.push_back(newLibrarian);// Add the new Librarian object to the librarians vector
        saveLibrarians(); // Save the updated librarian data to file
        system("CLS");
        cout << "New Librarian registered successfully!" << endl;
    }

};

class LMS
{
private:
    string userId, role;
    Librarian librarianObj; // Aggregation with class Librarian
    Book bookObj; // Aggregation with class Book
    BorrowedBook borrowedBookObj; // Aggregation with class BorrowedBook
    Student studentObj; // Aggregation with class Student

public:
    void loadData()
    { // Loading vectors with data
        librarianObj.loadLibrarians();
        bookObj.loadBooks();
        borrowedBookObj.loadBorrowedBooks();
        studentObj.loadStudents();
    }
    void manageBooks()
    {
        cout << "----- Manage Books -----" << endl;
        cout << "1. Add New Book" << endl;
        cout << "2. Search Book" << endl;
        cout << "3. Display All Books" << endl;
        cout << "4. Delete Book" << endl;
        cout << "5. Update Book" << endl;
        cout << "6. Set Availability Status" << endl;
        cout << "7. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        string choice;
        getline(cin, choice);
        system("CLS");
        string loopCondition = "";
        if (choice == "1")
        {
            while (loopCondition == "")
            {
                bookObj.addBook();
                cout << "For adding another book, press ENTER key, otherwise, type BACK: ";
                getline(cin, loopCondition);
            }
            system("CLS");
            manageBooks();
        }
        else if (choice == "2")
        {
            while (loopCondition == "")
            {
                bookObj.searchBook();
                cout << "For searching/borrowing another book, press ENTER key, otherwise, type BACK: ";
                getline(cin, loopCondition);
            }
            system("CLS");
            manageBooks();
        }
        else if (choice == "3")
        {
            while (loopCondition == "")
            {
                bookObj.displayAllBooks();
                cout << "For again displaying all books, press ENTER key, otherwise, type BACK: ";
                getline(cin, loopCondition);
                system("CLS");
            }
            system("CLS");
            manageBooks();
        }
        else if (choice == "4")
        {
            while (loopCondition == "")
            {
                bookObj.deleteBook();
                cout << "For deleting another book, press ENTER key, otherwise, type BACK: ";
                getline(cin, loopCondition);
            }
            system("CLS");
            manageBooks();
        }
        else if (choice == "5")
        {
            while (loopCondition == "")
            {
                bookObj.updateBook();
                cout << "For updating another book, press ENTER key, otherwise, type BACK: ";
                getline(cin, loopCondition);
            }
            system("CLS");
            manageBooks();
        }
        else if (choice == "6")
        {
            while (loopCondition == "")
            {
                bookObj.handleSetAvailability();
                cout << "For updating availability of another book, press ENTER key, otherwise, type BACK: ";
                getline(cin, loopCondition);
            }
            system("CLS");
            manageBooks();
        }

        else if (choice == "7")
            openLibrarianPortal();
        else
        {
            cout << "Invalid choice. Please try again." << endl;
            manageBooks();
        }
    }

    void manageStudents()
    {
        //system("CLS");
        cout << "----- Manage Students -----" << endl;
        cout << "1. Register New Student" << endl;
        cout << "2. Search Student" << endl;
        cout << "3. Delete Student Profile" << endl;
        cout << "4. Update Student Profile" << endl;
        cout << "5. View/Update Status of Borrowed Books" << endl;
        cout << "6. Borrow a Book for Student" << endl;
        cout << "7. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        string choice;
        getline(cin, choice);
        system("CLS");
        string loopCondition = "";
        if (choice == "1")
        {
            while (loopCondition == "")
            {
                studentObj.registerNewStudent();
                cout << "For registering another student, press ENTER key, otherwise, type BACK: ";
                getline(cin, loopCondition);
            }
            system("CLS");
            manageStudents();
        }
        else if (choice == "2")
        {
            while (loopCondition == "")
            {
                studentObj.viewStudentProfile();
                cout << "For searching another student, press ENTER key, otherwise, type BACK: ";
                getline(cin, loopCondition);
            }
            system("CLS");
            manageStudents();
        }
        else if (choice == "3")
        {
            while (loopCondition == "")
            {
                studentObj.deleteStudent();
                cout << "For deleting another student, press ENTER key, otherwise, type BACK: ";
                getline(cin, loopCondition);
                system("CLS");
            }
            system("CLS");
            manageStudents();
        }
        else if (choice == "4")
        {
            while (loopCondition == "")
            {
                studentObj.updateStudent();
                cout << "For updating another student, press ENTER key, otherwise, type BACK: ";
                getline(cin, loopCondition);
            }
            system("CLS");
            manageStudents();
        }
        else if (choice == "5")
        {
            string id;
            cout << "Enter the ID of Borrower (Student): ";
            getline(cin, id);
            if (borrowedBookObj.displayBorrowedBooks(id))
            {
                string bname;
                cout << "For renewing/returning book, enter the book name from the above mentioned list :";
                getline(cin, bname);
                if (borrowedBookObj.validateBorrowedBook(id, bname))
                {
                    cout << "Enter 1 for Renewal of the Book" << endl << "Enter 2 for Returning the Book" << endl
                        << "Type ENTER key to go back" << endl;
                    cout << "Enter your Option: ";
                    string option;
                    getline(cin, option);
                    if (option == "1")
                    {
                        borrowedBookObj.renewBook(id, bname);
                        system("CLS");
                        cout << "Book Renewal Successful!" << endl;
                        manageStudents();
                    }
                    else if (option == "2")
                    {
                        borrowedBookObj.returnBook(id, bname);
                        system("CLS");
                        cout << "Book Return Successful!" << endl;
                        manageStudents();
                    }
                }
                else
                {
                    system("CLS");
                    cout << "Invalid Book Name!";
                    manageStudents();
                }
            }
            else
            {
                system("CLS");
                manageStudents();
            }
            system("CLS");
            manageStudents();
        }

        else if (choice == "6")
        {
            string bookName, bookAuthor;
            cout << "Enter Book Name: ";
            getline(cin, bookName);
            cout << "Enter Author Name: ";
            getline(cin, bookAuthor);
            if (bookObj.validateBook(bookName, bookAuthor))
            {
                string borrowerId;
                cout << "Enter ID of Borrower: ";
                getline(cin, borrowerId);
                if (studentObj.validateStudent(borrowerId))
                {
                    borrowedBookObj.addBorrowBook(borrowerId, bookName, bookAuthor);
                    manageStudents();
                }
                else
                {
                    system("CLS");
                    cout << "Invalid student Id!";
                    manageStudents();
                }
            }
            else
            {
                system("CLS");
                cout << "Invalid book name or author!" << endl;
                manageStudents();
            }
        }

        else if (choice == "7")
            openLibrarianPortal();
        else
        {
            system("CLS");
            manageStudents();
        }
    }
    // Code related to Student class and its management
    void openLibrarianPortal()
    {
        system("COLOR 5F");
        string heading = "LIBRARIAN PORTAL MAIN MENU";
        int consoleWidth = 120;
        string asterisks(consoleWidth, '*');

        int spaces = (consoleWidth - heading.length()) / 2;
        cout << std::setw(consoleWidth) << asterisks << std::endl;
        cout << std::setw(spaces + heading.length()) << heading << std::endl;
        cout << std::setw(consoleWidth) << asterisks << std::endl;
        cout << "1. Manage Books" << endl << "2. Manage Students" << endl << "3. Log Out" << endl
            << "Enter your choice: ";
        string choice;
        getline(cin, choice);
        system("CLS");
        if (choice == "1")
            manageBooks();
        else if (choice == "2")
            manageStudents();
        else if (choice == "3")
        {
            cout << "Successfully Logged Out!" << endl;
            chooseRole();
        }
        else
        {
            system("CLS");
            cout << "Invalid option! Please try again." << endl;
            openLibrarianPortal();
        }
    }
    void openStudentPortal()
    {
        system("COLOR E4");
        string heading = "STUDENT PORTAL MAIN MENU";
        int consoleWidth = 120;
        string asterisks(consoleWidth, '*');

        int spaces = (consoleWidth - heading.length()) / 2;
        cout << std::setw(consoleWidth) << asterisks << std::endl;
        cout << std::setw(spaces + heading.length()) << heading << std::endl;
        cout << std::setw(consoleWidth) << asterisks << std::endl;
        cout << "1. View Book Catalog" << endl;
        cout << "2. Search Book" << endl;
        cout << "3. View Your Profile" << endl;
        cout << "4. View/Update Borrowed Books Status" << endl;
        cout << "5. Log Out" << endl;
        cout << "Enter your choice: ";
        string choice;
        getline(cin, choice);
        system("CLS");
        string loopCondition = "";
        if (choice == "1")
        {
            while (loopCondition == "")
            {
                bookObj.displayAllBooks();
                cout << "For displaying again, press ENTER key, otherwise, type BACK: ";
                getline(cin, loopCondition);
            }
            system("CLS");
            openStudentPortal();
        }
        else if (choice == "2")
        {
            while (loopCondition == "")
            {
                //bookObj.searchBook();
                cout << "For searching another book, press ENTER key, otherwise, type BACK: ";
                getline(cin, loopCondition);
            }
            system("CLS");
            openStudentPortal();
        }
        else if (choice == "3")
        {
            while (loopCondition == "")
            {
                studentObj.viewStudentProfile(userId);
                cout << "For viewing it again, press ENTER key, otherwise, type BACK: ";
                getline(cin, loopCondition);
            }
            system("CLS");
            openStudentPortal();
        }
        else if (choice == "4")
        {
            borrowedBookObj.displayBorrowedBooks(userId);
            cout << "Enter the name of book from the above list to renew it: " << endl
                << "(Press enter key to return back to the portal)" << endl;
            getline(cin, loopCondition);
            if (loopCondition != "")
            {
                borrowedBookObj.renewBook(userId, loopCondition);
                system("CLS");
                cout << "Book successfully Renewed!" << endl;
            }
            system("CLS");
            openStudentPortal();
        }
        else if (choice == "5")
        {
            system("CLS");
            chooseRole();
        }
        else
        {
            system("CLS");
            cout << "Invalid choice. Please try again." << endl;
            openStudentPortal();
        }
    }
    void chooseRole()
    {
        system("COLOR CF");
        string heading = "LIBRARY MANAGEMENT SYSTEM";
        int consoleWidth = 120;
        string asterisks(consoleWidth, '*');

        int spaces = (consoleWidth - heading.length()) / 2;
        cout << std::setw(consoleWidth) << asterisks << std::endl;
        cout << std::setw(spaces + heading.length()) << heading << std::endl;
        cout << std::setw(consoleWidth) << asterisks << std::endl;
        cout << "1. Librarian" << endl << "2. Student" << endl << "3. Exit" << endl
            << "Enter your choice: ";
        string option;
        getline(cin, option);
        if (option == "1")
        {
            system("CLS");
            role = "Librarian";
            string key = librarianObj.validateAccess();
            if (key == "1")
            {
                string option = librarianObj.libPortalMenu();
                if (option == "1")
                {
                    string userId = librarianObj.handleLibLogin();
                    if (userId == "")
                    {
                        cout << "Login Failed! Invalid Id or Password." << endl;
                        chooseRole();
                    }
                    else
                    {
                        system("CLS");
                        cout << "Login Successful!" << endl;
                        openLibrarianPortal();
                    }

                }
                else if (option == "2")
                {
                    librarianObj.handleRegistration();
                    chooseRole();
                }
                else
                {
                    cout << "Invalid option! Please try again." << endl;
                    chooseRole();
                }
            }
            else
            {
                cout << "Access Denied! Wrong key." << endl;
                chooseRole();
            }
        }
        else if (option == "2")
        {
            system("CLS");
            role = "Student";
            string stdId;
            stdId = studentObj.handleStuLogin();
            if (stdId == "")
            {
                system("CLS");
                cout << "Login Failed! Invalid Id or Password." << endl;
                chooseRole();

            }
            else
            {
                system("CLS");
                cout << "Login Successful!" << endl;
                openStudentPortal();
            }
        }
        else if (option == "3")
            exit(0);
        else
        {
            system("CLS");
            cout << "Invalid option. Please try again!" << endl;
            chooseRole();
        }
    }

};


int main()
{
    LMS library;
    library.loadData();
    library.chooseRole();
    return 0;
}
