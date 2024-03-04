// g++ lists.cpp && ./a.out
//
#include <iostream>

typedef struct list_tag
{
    void *data;
    struct list_tag *next;
} list_t, *list_p;


template <typename T>
struct Node
{
    T data;
    Node<T>* next;
};

template <typename T>
struct List {
    Node<T>* head;

    List() : head(nullptr) {}
    
    void append(T x)
    {
        auto new_node = new Node<T>;
        new_node->data = x;
        new_node->next = head;
        head = new_node;
    }

    void reverse()
    {
        Node<T>* new_head = nullptr;
        while (head)
        {
            auto next = head->next;
            head->next = new_head;
            new_head = head;
            head = next;
        }
        head = new_head;
    }

    bool empty() {
        return head == nullptr;
    }
};

void append(list_p *l, void *data)
{
    list_p node = new list_t;
    node->data = data;
    node->next = *l;
    *l = node;
}

void reverse(list_p *l) {
    list_p tmp = nullptr;
    for (list_p it = *l; it;)
    {
        list_p next = it->next;
        it->next = tmp;
        tmp = it;
        it = next;
    }
    *l = tmp;
}

int main() {
    std::cout << "============== C++ ==================" << std::endl;   

    List<int> list2;
    list2.append(10);
    list2.append(11);
    list2.append(12);

    for (auto it = list2.head; it; it = it->next)
    {
         std::cout << it->data << std::endl;
    }

    std::cout << "============== C++ Reversed ==================" << std::endl;   

    list2.reverse();
    for (auto it = list2.head; it; it = it->next)
    {
         std::cout << it->data << std::endl;
    }


    std::cout << "============== Plain C ==================" << std::endl;   

    list_p list = nullptr;

    int x0 = 0;
    append(&list, &x0);

    int x1 = 1;
    append(&list, &x1);

    int x2 = 2;
    append(&list, &x2);

    int x3 = 3;
    append(&list, &x3);

    for (list_p l = list; l != nullptr; l = l->next)
    {
        std::cout << *static_cast<int*>(l->data) << std::endl;
    }

    std::cout << "============== REVERSED ==================" << std::endl;   
    reverse(&list);

    for (list_p l = list; l != nullptr; l = l->next)
    {
        std::cout << *static_cast<int*>(l->data) << std::endl;
    }
}
