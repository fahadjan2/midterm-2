// COMSC-210 | Midterm #2 | Fahad Fawad Ahmad 
// IDE used: Visual Studio
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private:
    struct Node {
        string data;
        Node* prev;
        Node* next;
        Node(string val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void insert_after(string value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode;
        temp->next = newNode;
    }

    void delete_val(string value) {
        if (!head) return;

        Node* temp = head;
        
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; 

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next; 

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; 

        delete temp;
    }

    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) {
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(string v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(string v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << "\t\t" << current->data << endl;
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << endl;
            current = current->prev;
        }
        cout << endl;
    }

    int get_Size() { //Gets the size of line
        int count = 0;
        Node* current = head;
        if (!current) { 
            cout << "List is empty." << endl;
            return 1;
        }
        while (current) {
            count++;
            current = current->next;
        }
        return count;
    }

    string get_Name(int pos) { //gets name at position
        int count = 0;
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return "Empty";
        }
        while (current) {
            count++;
            if (count == pos) {
                return current->data;
            }
            current = current->next;
        }
    }
};

//Add 5 new at the beginning
//Output the line
//Chances for each event
int main() {
    cout << "test4" << endl;
    //File Opening
	ifstream file;
	file.open("names.txt");
	if (!file.is_open()) {
	    cout << "Failed to open file" << endl;
	    return 1;
	}

    //Populates a vector with the names
    vector<string> names;
    string name;
    while (getline(file, name)) {
        names.push_back(name);
    }
    file.close();

    DoublyLinkedList * Coffeeline = new DoublyLinkedList;
    cout << "Store Opens:" << endl;
    for (int minute = 0; minute < 20; minute++) {
        if (minute == 0) { //At the start, adds 5 people to the line
            for (int i = 0; i < 5; i++) {
                int nameprob = rand() % 100;        
                string name = names[nameprob];
                Coffeeline->push_back(name);
            }
        }
        else {
            cout << "Time Step #" << minute + 1 << ":" << endl; 
            int prob = rand() % 100 + 1; //1-100 chance
            if (prob <= 60) { //New customer joining end of line
                //Event A     
                int nameprob = rand() % 100; //0-99 names 
                string name = names[nameprob];
                Coffeeline->push_back(name);
                cout << "\t" << name << " joins the line" << endl;
            }
            prob = rand() % 100 + 1;
            if (prob <= 40) { //Customer being served
                //Event B
                string name = Coffeeline->get_Name(1);
                Coffeeline->pop_front();
                cout << "\t" << name << " is served" << endl;
            }
            prob = rand() % 100 + 1;
            if (prob <= 20) { //Customer at the end of line leaving
                //Event C
                int lineSize = Coffeeline->get_Size();
                string name = Coffeeline->get_Name(lineSize);
                Coffeeline->pop_back();
                cout << "\t" << name << " (at the rear) left the line" << endl;
            }
            prob = rand() % 100 + 1;
            if (prob <= 10) { //Any customer leaving
                //Event D
                int lineSize = Coffeeline->get_Size();
                int randCount = rand() % lineSize;
                string name = Coffeeline->get_Name(randCount);
                Coffeeline->delete_pos(randCount);
                cout << "\t" << name << " left the line" << endl;
            }
            prob = rand() % 100 + 1;
            if (prob <= 10) { //VIP walking to the front
                //Event E
                int nameprob = rand() % 100;
                string name = names[nameprob];
                Coffeeline->push_front(name);
                cout << "\t" << name << " (VIP) joins the front of the line" << endl;
            }
        }
        cout << "\tResulting line: " << endl;
        Coffeeline->print();
        cout << endl;
    }
    
    delete Coffeeline;
    
    return 0;
}
