#include <iostream>
#include <string>
using namespace std;

struct Node
{
    string judul;
    float rating;
    string deskripsi;
    Node *next;
    Node *prev;
};

struct Node *buatlist(const string &judul, const string &deskripsi, float rating = 0.0)
{
    Node *newNode = new Node;
    newNode->judul = judul;
    newNode->deskripsi = deskripsi;
    newNode->rating = rating;
    newNode->next = NULL;
    newNode->prev = NULL;
    if (newNode->judul.empty() || newNode->deskripsi.empty())
    {
        cout << "Title or description must not be empty!" << endl;
        delete newNode;
        return NULL;
    }
    return newNode;
}

void tambahlistdepan(Node **head, const string &judul, const string &deskripsi, float rating = 0.0)
{
    Node *newNode = buatlist(judul, deskripsi, rating);
    newNode->next = *head;
    if (*head != NULL)
    {
        (*head)->prev = newNode;
    }
    *head = newNode;
}

void searchItem(string key, string judul, Node *head) {
    Node* bantu = head;
    bool found = false;
    while (bantu != NULL) {
        if (bantu->judul == key) {
                cout << "Movie found!" << endl;
                cout << "Title\t\t\t\t: " << bantu->judul << endl;
                cout << "Description\t: " << bantu->deskripsi << endl;
                cout << "Rating\t\t\t: " << bantu->rating << endl;
            } 
            bantu = bantu->next;
        }
    if (!found) cout << "Movie with title '" << judul << "' not found." << endl;
}

Node *searching(Node *head, const string &key)
{
    Node *bantu = head;
    while (bantu != NULL)
    {
        if (bantu->judul == key)
        {
            return bantu;
        }
        bantu = bantu->next;
    }
    return NULL;
}

void deleteList(Node **head, const string &judul)
{
    Node *nodeToDelete = searching(*head, judul);
    if (nodeToDelete != NULL)
    {
        if (nodeToDelete->prev != NULL)
        {
            nodeToDelete->prev->next = nodeToDelete->next;
        }
        else
        {
            *head = nodeToDelete->next; // Jika node yang dihapus adalah head
        }
        if (nodeToDelete->next != NULL)
        {
            nodeToDelete->next->prev = nodeToDelete->prev;
        }
        delete nodeToDelete;
        cout << judul << " " << "has been successfully deleted." << endl;
    }
    else
    {
        cout << judul << " " << "not found" << endl;
    }
}

void sortListByRating(Node **head)
{
    if (*head == NULL || (*head)->next == NULL)
        return; // List kosong atau hanya satu elemen

    bool swapped;
    do
    {
        swapped = false;
        Node *bantu = *head;
        while (bantu->next != NULL)
        {
            if (bantu->rating < bantu->next->rating) // Urutkan dari rating tertinggi ke terendah
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
        cout << bantu->judul << "  " << endl;
        bantu = bantu->next;
    }
    cout << endl;
}

int pilihmenu;

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
    cin >> pilihmenu;
    cin.ignore();
}

int main()
{
    cout << "===== Welcome to YourWatchingLIST, Buddy! =====" << endl;
    cout << "Press ENTER to continue..." << endl;
    cin.ignore();
    menu();
    Node *head = NULL;
    while (pilihmenu != 6)
    {
        menu();
        switch (pilihmenu)
        {
        case 1:
        {
            string judul;
            string deskripsi;
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
        {
            tampilkandaridepan(head);
            break;
        }
        case 3:
        {
            string judul;
            cout << "Enter the title of the movie: ";
            getline(cin, judul);
            Node* hasil = searching(head, judul);
            if (hasil != NULL) {
                cout << "Movie found!" << endl;
                cout << "Title\t\t: " << hasil->judul << endl;
                cout << "Description\t: " << hasil->deskripsi << endl;
                cout << "Rating\t\t: " << hasil->rating << endl;
            } else {
                cout << "Movie with title '" << judul << "' not found." << endl;
            }
            break;
        }
        case 4:
        {
            sortListByRating(&head);
            cout << "Watch List sorted by rating (highest to lowest):" << endl;
            tampilkandaridepan(head);
            break;
        }
        case 5:
        {
            string judul;
            cout << "Enter the title of the movie to delete: ";
            getline(cin, judul);
            deleteList(&head, judul);
            break;
        }  
        default:
            cout << "! Invalid !" << endl;
        }
        cout << "Press ENTER to back to menu..." << endl;
        cin.get();
    }
    cout << "Thank You and Happy Watching!";
    return 0;
}
