#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib> // untuk system("cls")
using namespace std;

struct Node
{
    string judul;
    float rating;
    string deskripsi;
    Node *next;
    Node *prev;
};

Node *buatlist(const string &judul, const string &deskripsi, float rating = 0.0)
{
    if (judul.empty() || deskripsi.empty())
    {
        cout << "Title or description must not be empty!" << endl;
        return NULL;
    }
    Node *newNode = new Node{judul, rating, deskripsi, NULL, NULL};
    return newNode;
}

void tambahlistdepan(Node **head, const string &judul, const string &deskripsi, float rating = 0.0)
{
    Node *newNode = buatlist(judul, deskripsi, rating);
    if (newNode == NULL) return;
    newNode->next = *head;
    if (*head != NULL)
        (*head)->prev = newNode;
    *head = newNode;
}

Node *searching(Node *head, const string &key)
{
    Node *bantu = head;
    while (bantu != NULL)
    {
        if (bantu->judul == key)
            return bantu;
        bantu = bantu->next;
    }
    return NULL;
}

void deleteList(Node **head, const string &judul)
{
    Node *nodeToDelete = searching(*head, judul);
    if (nodeToDelete)
    {
        if (nodeToDelete->prev)
            nodeToDelete->prev->next = nodeToDelete->next;
        else
            *head = nodeToDelete->next;
        if (nodeToDelete->next)
            nodeToDelete->next->prev = nodeToDelete->prev;
        delete nodeToDelete;
        cout << judul << " has been successfully deleted." << endl;
    }
    else
    {
        cout << judul << " not found" << endl;
    }
}

void sortListByRating(Node **head)
{
    if (*head == NULL || (*head)->next == NULL)
        return;
    bool swapped;
    do
    {
        swapped = false;
        Node *bantu = *head;
        while (bantu->next)
        {
            if (bantu->rating < bantu->next->rating)
            {
                swap(bantu->judul, bantu->next->judul);
                swap(bantu->deskripsi, bantu->next->deskripsi);
                swap(bantu->rating, bantu->next->rating);
                swapped = true;
            }
            bantu = bantu->next;
        }
    } while (swapped);
}

void tampilkandaridepan(Node *head)
{
    if (head == NULL)
    {
        cout << "There is no Watch List!" << endl;
        return;
    }
    Node *bantu = head;
    cout << "Here's your Watch Lists: " << endl;
    while (bantu != NULL)
    {
        cout << "Title: " << bantu->judul << endl;
        cout << "Description: " << bantu->deskripsi << endl;
        cout << "Rating: " << bantu->rating << endl;
        cout << "-----------------------------" << endl;
        bantu = bantu->next;
    }
}

void simpanKeFile(Node *head)
{
    ofstream file("watchlist.txt");
    Node *bantu = head;
    while (bantu != NULL)
    {
        file << bantu->judul << "|" << bantu->deskripsi << "|" << bantu->rating << endl;
        bantu = bantu->next;
    }
    file.close();
}

void bacaDariFile(Node **head)
{
    ifstream file("watchlist.txt");
    string line;
    while (getline(file, line))
    {
        size_t pos1 = line.find('|');
        size_t pos2 = line.rfind('|');
        if (pos1 != string::npos && pos2 != string::npos && pos1 != pos2)
        {
            string judul = line.substr(0, pos1);
            string deskripsi = line.substr(pos1 + 1, pos2 - pos1 - 1);
            float rating = stof(line.substr(pos2 + 1));
            tambahlistdepan(head, judul, deskripsi, rating);
        }
    }
    file.close();
}

bool login()
{
    string user, pass;
    cout << "=== Login to YourWatchingLIST ===" << endl;
    cout << "Username: ";
    getline(cin, user);
    cout << "Password: ";
    getline(cin, pass);
    // Dummy username & password
    return (user == "admin" && pass == "1234");
}

void menu()
{
    cout << "========================================" << endl;
    cout << "         YourWatchingLIST Menu          " << endl;
    cout << "========================================" << endl;
    cout << "1. Add Movie to Watch List" << endl;
    cout << "2. Show Your Watch Lists" << endl;
    cout << "3. Search for the Movie" << endl;
    cout << "4. Sort the List by Rating" << endl;
    cout << "5. Delete the List" << endl;
    cout << "6. Exit" << endl;
    cout << "========================================" << endl;
    cout << "Select Menu: ";
}

int main()
{
    system("cls");
    if (!login())
    {
        cout << "Login failed. Exiting..." << endl;
        return 0;
    }

    Node *head = NULL;
    bacaDariFile(&head);
    int pilihmenu;

    do
    {
        system("cls");
        menu();
        cin >> pilihmenu;
        cin.ignore();
        system("cls");

        switch (pilihmenu)
        {
        case 1:
        {
            string judul, deskripsi;
            float rating;
            cout << "Title: ";
            getline(cin, judul);
            cout << "Movie Description: ";
            getline(cin, deskripsi);
            cout << "Rating (0.0 - 5.0): ";
            cin >> rating;
            cin.ignore();
            tambahlistdepan(&head, judul, deskripsi, rating);
            cout << judul << " added to your WatchList!" << endl;
            break;
        }
        case 2:
            tampilkandaridepan(head);
            break;
        case 3:
        {
            string judul;
            cout << "Enter the title of the movie: ";
            getline(cin, judul);
            Node *hasil = searching(head, judul);
            if (hasil != NULL)
            {
                cout << "Movie found!" << endl;
                cout << "Title\t\t: " << hasil->judul << endl;
                cout << "Description\t: " << hasil->deskripsi << endl;
                cout << "Rating\t\t: " << hasil->rating << endl;
            }
            else
            {
                cout << "Movie with title '" << judul << "' not found." << endl;
            }
            break;
        }
        case 4:
            sortListByRating(&head);
            cout << "Watch List sorted by rating (highest to lowest):" << endl;
            tampilkandaridepan(head);
            break;
        case 5:
        {
            string judul;
            cout << "Enter the title of the movie to delete: ";
            getline(cin, judul);
            deleteList(&head, judul);
            break;
        }
        case 6:
            simpanKeFile(head);
            cout << "Thank You and Happy Watching!" << endl;
            break;
        default:
            cout << "Invalid menu choice." << endl;
        }
        if (pilihmenu != 6)
        {
            cout << "\nPress ENTER to go back to menu..." << endl;
            cin.get();
        }

    } while (pilihmenu != 6);

    return 0;
}
