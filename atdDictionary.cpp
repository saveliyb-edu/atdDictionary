#include <iostream>
#include <string>

class DictionaryList {
private:
    struct Node {
        std::string word;
        Node* next;

        Node(const std::string& w) : word(w), next(nullptr) {}
    };

    Node* head;

public:
    DictionaryList() : head(nullptr) {}

    void insert(const std::string& newWord) {
        Node* newNode = new Node(newWord);
        if (!head || head->word > newWord) {
            newNode->next = head;
            head = newNode;
        }
        else {
            Node* current = head;
            while (current->next && current->next->word < newWord) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }

    bool search(const std::string& target) {
        Node* current = head;
        while (current) {
            if (current->word == target) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void remove(const std::string& target) {
        Node* current = head;
        Node* prev = nullptr;
        while (current) {
            if (current->word == target) {
                if (prev) {
                    prev->next = current->next;
                }
                else {
                    head = current->next;
                }
                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }
    }

    ~DictionaryList() {
        while (head) {
            Node* tmp = head->next;
            delete head;
            head = tmp;
        }
    }

    friend std::ostream& operator<<(std::ostream& out, const DictionaryList& obj);
    //TODO Добавьте методы merge, deleteWords и дружественную функцию getIntersection, испроавить insert - нельзя добавлять одинаковые элементы
};

std::ostream& operator<<(std::ostream& out, const DictionaryList& obj) {
    DictionaryList::Node* current = obj.head;
    while (current) {
        out << current->word << " ";
        current = current->next;
    }

    return out;
}

int main() {
    DictionaryList dict1;
    dict1.insert("apple");
    dict1.insert("banana");
    dict1.insert("cherry");
    std::cout << dict1 << std::endl;

    DictionaryList dict2;
    dict2.insert("banana");
    dict2.insert("date");
    dict2.insert("fig");
    std::cout <<  dict2 << std::endl;


    dict1.remove("apple");
    std::cout << "delete 'apple' from dict1: ";
    std::cout << dict1 << std::endl;

    std::cout << "search 'banana' from dict1: " << dict1.search("banana") << std::endl;



    return 0;
}
