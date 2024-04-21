//
// Created by Dhananjaya on 2023-10-20.
//
#include <iostream>

#ifndef FILEMANAGEMENTSYSTEM_DOUBLYLINKLIST_H
#define FILEMANAGEMENTSYSTEM_DOUBLYLINKLIST_H

namespace dll {
    template<typename T>
    class Node {
    public:
        Node *next;
        Node *previous;
        T value;

        Node(T value);

        Node();

        ~Node();


    };

    template<typename T>
    Node<T>::Node(T value): value{value} {
    }

    template<typename T>
    Node<T>::Node() {

    }

    template<typename T>
    Node<T>::~Node() {

    }


    template<typename T>
    class DoublyLinkList {

    private:

        Node<T> *head;
        Node<T> *tail;

    public:
        int length;

        DoublyLinkList(T value);

        Node<T> *begin();

        Node<T> *end();

        DoublyLinkList();

        void printList();

        bool append(T value);

        bool prepend(T value);

        bool pop();

        bool popFirst();

        Node<T> *get(int index);

        bool set(int index, T value);

        bool insert(int index, T value);

        //bool remove(T value);

        bool remove(int index);

        ~DoublyLinkList();


    };


    template<typename T>
    DoublyLinkList<T>::DoublyLinkList(T value) :head{nullptr}, tail{nullptr}, length{0} {
        auto *newNode = new Node<T>(value);
        head = newNode;
        tail = newNode;
        length += 1;
    }

    template<typename T>
    DoublyLinkList<T>::DoublyLinkList() :head{nullptr}, tail{nullptr}, length{0} {
    }

    template<typename T>
    void DoublyLinkList<T>::printList() {
        auto *temp = head;
        while (temp) {
            std::cout << temp->value << std::endl;
            temp = temp->next;
        }
    }

    template<typename T>
    bool DoublyLinkList<T>::append(T value) {
        auto *newNode = new Node<T>(value);
        if (length == 0) {
            head = newNode;
            tail = newNode;
        } else {
            Node<T> *temp = tail;
            tail->next = newNode;
            newNode->previous = tail;
            tail = newNode;
        }
        length += 1;
        return true;
    }

    template<typename T>
    bool DoublyLinkList<T>::prepend(T value) {
        auto *newNode = new Node<T>(value);
        if (length == 0) {
            head = newNode;
            tail = newNode;
        } else {
            newNode->next = head;
            head->previous = newNode;
            head = newNode;
        }
        length += 1;
        return true;
    }

    template<typename T>
    bool DoublyLinkList<T>::pop() {
        if (length == 0) {
            return false;
        } else if (length == 1) {
            head = nullptr;
            tail = nullptr;
        } else {
            auto *temp = tail;
            tail = tail->previous;
            tail->next = nullptr;
            temp->previous = nullptr;
            length -= 1;
            delete temp;
        }
        return true;
    }

    template<typename T>
    bool DoublyLinkList<T>::popFirst() {
        if (length == 0) {
            return false;
        } else if (length == 1) {
            head = nullptr;
            tail = nullptr;
        } else {
            auto *temp = head;
            head = head->next;
            temp->next = nullptr;
            head->previous = nullptr;
            length -= 1;
            delete temp;
        }
    }

    template<typename T>
    Node<T> *DoublyLinkList<T>::get(int index) {
        if (index < 0 || index >= length) {
            return nullptr;
        }
        Node<T> *temp;
        if (index < (int) (length / 2)) {
            temp = head;
            for (int i = 0; i < index; i++) {
                temp = temp->next;
            }
        } else {
            temp = tail;
            for (int i = 0; i < (length - (index + 1)); i++) {
                temp = temp->previous;
            }
        }
        return temp;

    }

    template<typename T>
    bool DoublyLinkList<T>::set(int index, T value) {
        auto *temp = get(index);
        temp->value = value;
        return true;
    }

    template<typename T>
    bool DoublyLinkList<T>::insert(int index, T value) {
        if (index < 0 || index > length) {

            return false;
        }
        if (index == 0) {

            return prepend(value);

        }
        if (index == length) {
            return append(value);
        }
        auto *after = get(index);
        auto *before = after->previous;
        auto *newNode = new Node<T>(value);
        newNode->next = after;
        newNode->previous = before;
        before->next = newNode;
        after->previous = newNode;
        length += 1;
        return true;
    }

    template<typename T>
    bool DoublyLinkList<T>::remove(int index) {
        if (index < 0 || index > length)
            return false;
        if (index == 0)
            return popFirst();

        if (index == (length - 1))
            return pop();
        auto *temp = get(index);
        auto *before = temp->previous;
        auto *after = temp->next;
        before->next = after;
        after->previous = before;
        temp->next = nullptr;
        temp->previous = nullptr;
        length -= 1;
        delete temp;
        return true;
    }

    template<typename T>
    DoublyLinkList<T>::~DoublyLinkList() {
        auto *temp = head;
        Node<T> *dumb;
        while (temp) {
            dumb = temp;
            temp = temp->next;
            delete dumb;
        }
    }

    template<typename T>
    Node<T> *DoublyLinkList<T>::begin() {
        return head;
    }

    template<typename T>
    Node<T> *DoublyLinkList<T>::end() {
        return tail;
    }

}

#endif //FILEMANAGEMENTSYSTEM_DOUBLYLINKLIST_H
