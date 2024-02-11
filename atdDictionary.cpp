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
        if (search(newWord)) { return; }
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

    void deleteWords(DictionaryList& list) {
        Node* prev = nullptr;
        Node* current = head;

        while (current) {
            if (list.search(current->word)) {
                Node* tmp = current;
                current = current->next;
                if (prev) {
                    prev->next = current;
                }
                else {
                    head = current;
                }
                delete tmp;
            }
            else {
                prev = current;
                current = current->next;
            }
        }
    }

    void merge(DictionaryList& list) {
        Node* current = list.head;

        while (current) {
            if (!search(current->word)) {
                insert(current->word);
            }
            Node* tmp = current;
            current = current->next;
            delete tmp;
        }

        list.head = nullptr;
    }



    friend std::ostream& operator<<(std::ostream& out, const DictionaryList& obj);

    friend DictionaryList getIntersection(const DictionaryList& list1, DictionaryList& list2) {
        DictionaryList result;

        Node* current1 = list1.head;
        while (current1) {
            if (list2.search(current1->word)) {
                result.insert(current1->word);
            }
            current1 = current1->next;
        }

        return result;
    }
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
    std::cout << "dict1: " << dict1 << std::endl;

    DictionaryList dict2;
    dict2.insert("banana");
    dict2.insert("date");
    dict2.insert("fig");
    std::cout << "dict2: " << dict2 << std::endl;

    std::cout << "test getIntersection function" << std::endl;
    DictionaryList dict3 = getIntersection(dict2, dict1);
    std::cout << "dict3: " << dict3 << std::endl;


    dict1.remove("apple");
    std::cout << "delete 'apple' from dict1: " << std::endl;
    std::cout << "dict1: " << dict1 << std::endl;

    std::cout << "search 'banana' from dict1: " << dict1.search("banana") << std::endl;

    std::cout << "we delete all the words from dict2 that are in dict1" << std::endl;
    dict2.deleteWords(dict1);
    std::cout << "dict2: " << dict2 << std::endl << "dict1: " << dict1 << std::endl;


    std::cout << "merge dict2 with dict1: " << std::endl;
    dict2.merge(dict1);
    std::cout << "dict2: " << dict2 << std::endl << "dict1: " << dict1 << std::endl;

    return 0;
}
