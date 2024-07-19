#include <iostream>
#include <string>

struct book {
    std::string title;
    std::string author;
    int isbn;
    std::string genre;
    int year;
    int bno;
    book *next;
};

struct user {
    std::string name;
    long int registration;
    short int no_of_bookorder;
    std::string book_list[3];
    user *next;
};

int index = 0;

using namespace std;

class lib_sys {
    book *first;
    book *last;
    user *ufirst;
    user *ulast;

public:
    lib_sys() {
        first = NULL;
        last = NULL;
        ufirst = NULL;
        ulast = NULL;
    }

    void add_new_book() {
        index++;
        book *temp = new book;
        cout << "\nENTER THE AUTHOR NAME\n :";
        cin.ignore();
        getline(cin, temp->author);
        cout << "\nENTER THE BOOK TITLE\n :";
        getline(cin, temp->title);
        cout << "\nENTER THE BOOK PUBLICATION YEAR\n:";
        cin >> temp->year;
        cin.ignore();
        cout << "\nENTER THE BOOK GENRE(TYPE) \n:";
        getline(cin, temp->genre);
        cout << "\nENTER THE BOOK ISBN NUMBER IF NOT PRESS 0\n :";
        cin >> temp->isbn;
        temp->bno = index;
        temp->next = NULL;
        if (first == NULL) {
            first = temp;
            last = temp;
        } else {
            last->next = temp;
            last = temp;
        }
    }

    void list_displaying() {
        cout << "\nTOTAL NO OF BOOK IN LIBRARY ARE::" << index << endl;
        book *temp = first;
        cout << "TITLE  \t AUTHOR  \tPUBLICATION YEAR" << endl;
        while (temp != NULL) {
            cout << temp->title << "\t" << temp->author << "\t" << temp->year << endl;
            temp = temp->next;
        }
    }

    void book_delete1() {
        string author, title;
        int year1;
        
        cout << "\nENTER YOUR BOOK TITLE(UPPERCASE)\n::";
        cin.ignore();
        getline(cin, title);
        cout << "\nENTER YOUR BOOK AUTHOR NAME\n::";
        getline(cin, author);
        cout << "\nENTER YEAR OF PUBLICATION\n::";
        cin >> year1;
        
        if (search_book(author, title, year1)) {
            book *temp = first;
            book *prev = NULL;

            while (temp != NULL) {
                if (temp->author == author && temp->title == title && temp->year == year1) {
                    if (prev == NULL) {
                        first = temp->next;
                    } else {
                        prev->next = temp->next;
                    }
                    if (temp == last) {
                        last = prev;
                    }
                    delete temp;
                    index--;
                    cout << "BOOK DELETED NOW\n";
                    return;
                }
                prev = temp;
                temp = temp->next;
            }
        } else {
            cout << "BOOK NOT FOUND:\n";
        }
    }

    void update_book1() {
        string author, title;
        int year1;
        
        cout << "\nENTER YOUR BOOK TITLE(UPPERCASE)\n::";
        cin.ignore();
        getline(cin, title);
        cout << "\nENTER YOUR BOOK AUTHOR NAME\n::";
        getline(cin, author);
        cout << "\nENTER YEAR OF PUBLICATION\n::";
        cin >> year1;

        if (search_book(author, title, year1)) {
            book *temp = first;
            while (temp != NULL) {
                if (temp->author == author && temp->title == title && temp->year == year1) {
                    short int choice = 0;
                    cout << "CHOICE WHAT YOU WANT TO UPDATE\n 1) ISBN \n 2) AUTHOR \n 3) TITLE \n 4) YEAR OF PUBLICATION \n::";
                    cin >> choice;
                    cin.ignore();
                    if (choice == 1) {
                        cout << "\nENTER NEW ISBN FOR BOOK TITLE ::" << temp->title << "\n::";
                        cin >> temp->isbn;
                    } else if (choice == 2) {
                        cout << "\nENTER NEW AUTHOR FOR BOOK TITLE ::" << temp->title << "\n::";
                        cin.ignore();
                        getline(cin, temp->author);
                    } else if (choice == 3) {
                        cout << "\nENTER NEW TITLE FOR BOOK TITLE ::" << temp->title << "\n::";
                        cin.ignore();
                        getline(cin, temp->title);
                    } else if (choice == 4) {
                        cout << "\nENTER NEW PUBLICATION YEAR FOR BOOK TITLE ::" << temp->title << "\n::";
                        cin >> temp->year;
                    } else {
                        cout << "\nINVALID CHOICE:\n";
                    }
                    break;
                }
                temp = temp->next;
            }
            cout << "BOOK UPDATED NOW\n";
        } else {
            cout << "BOOK NOT FOUND:\n";
        }
    }

    bool search_book(string author, string title, int year) {
        book *temp = first;
        while (temp != NULL) {
            if (temp->author == author && temp->title == title && temp->year == year) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    void check_book() {
        string author, title;
        int year1;
        
        cout << "\nENTER YOUR BOOK TITLE(UPPERCASE)\n::";
        cin.ignore();
        getline(cin, title);
        cout << "\nENTER YOUR BOOK AUTHOR NAME\n::";
        getline(cin, author);
        cout << "\nENTER YEAR OF PUBLICATION\n::";
        cin >> year1;
        if (search_book(author, title, year1)) {
            cout << "\nBOOK IS AVAILABLE:\n";
        } else {
            cout << "\nBOOK NOT AVAILABLE:\n";
        }
    }

    void register_user() {
        user *temp = new user;
        cout << "\n::ENTER YOUR REGISTRATION NUMBER::";
        cin >> temp->registration;
        cout << "\n::ENTER USER NAME::";
        cin.ignore();
        getline(cin, temp->name);
        temp->no_of_bookorder = 0;
        temp->next = NULL;
        if (ufirst == NULL) {
            ufirst = temp;
            ulast = temp;
        } else {
            ulast->next = temp;
            ulast = temp;
        }
        cout << "\nTHANKS FOR REGISTRATION:";
    }

    user* find_user(long int registration) {
        user *temp = ufirst;
        while (temp != NULL) {
            if (temp->registration == registration) {
                return temp;
            }
            temp = temp->next;
        }
        return NULL;
    }

    void borrow_book() {
        long int registration;
        cout << "\nENTER YOUR REGISTRATION NUMBER\n::";
        cin >> registration;
        user *current_user = find_user(registration);

        if (current_user == NULL) {
            cout << "\nUSER NOT REGISTERED. PLEASE REGISTER FIRST.\n";
            return;
        }

        string author, title;
        int year1;
        cout << "\nENTER YOUR BOOK TITLE(UPPERCASE)\n::";
        cin.ignore();
        getline(cin, title);
        cout << "\nENTER YOUR BOOK AUTHOR NAME\n::";
        getline(cin, author);
        cout << "\nENTER YEAR OF PUBLICATION\n::";
        cin >> year1;

        if (search_book(author, title, year1)) {
            if (current_user->no_of_bookorder < 3) {
                current_user->book_list[current_user->no_of_bookorder] = title;
                current_user->no_of_bookorder++;
                cout << "\nBOOK BORROWED SUCCESSFULLY\n";
            } else {
                cout << "\nYOU CAN ONLY BORROW UP TO 3 BOOKS.\n";
            }
        } else {
            cout << "\nBOOK NOT FOUND\n";
        }
    }
};

int main() {
    cout << "\t WELCOME TO LIBRARY MANAGEMENT SYSTEM" << endl;
    bool check = true;
    cout << "\033[1m\033[4m:::PLEASE USE UPPERCASE:::\033[0m" << endl;
    lib_sys S1;
    while (check) {
        short int role;
        cout << "\n SELECT YOUR ROLE \n 1) ADMIN \n 2) STUDENT \n 3) EXIT ::" << endl;
        cin >> role;
        if (role == 1) {
            cout << "\t WELCOME TO ADMIN DASHBOARD \n";
            int passkey;
            for (int i = 0; i < 3; i++) {
                cout << "ENTER YOUR PASSKEY:\n";
                cin >> passkey;
                if (passkey == 54321) {
                    break;
                }
            }
            if (passkey == 54321) {
                bool loopchoice = true;
                while (loopchoice) {
                    short int choice;
                    cout << " 1) ADD NEW BOOKS \n 2) UPDATE NEW BOOK INFORMATION  \n 3) DELETE BOOK \n 4) DISPLAY LIST OF BOOK \n 5) EXIT \n:";
                    cin >> choice;
                    if (choice == 1) {
                        S1.add_new_book();
                    } else if (choice == 2) {
                        S1.update_book1();
                    } else if (choice == 3) {
                        S1.book_delete1();
                    } else if (choice == 4) {
                        S1.list_displaying();
                    } else if (choice == 5) {
                        loopchoice = false;
                    } else {
                        cout << "INVALID CHOICE YOU SELECT AS ADMIN \n";
                    }
                }
            }
        } else if (role == 2) {
            cout << "\t WELCOME TO USER DASHBOARD: \n";
            bool choiceuser = true;
            while (choiceuser) {
                short int check;
                cout << "choice  \n 1) CHECK BOOK AVAILABILITY  \n 2) BORROW BOOK \n 3) REGISTRATION \n 4) EXIT \n:";
                cin >> check;
                if (check == 1) {
                    S1.check_book();
                } else if (check == 2) {
                    S1.borrow_book();
                } else if (check == 3) {
                    S1.register_user();
                } else if (check == 4) {
                    choiceuser = false;
                }
            }
        } else {
            check = false;
        }
    }
    return 0;
}

