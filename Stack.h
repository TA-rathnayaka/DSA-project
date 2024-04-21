//
// Created by Dhananjaya on 2023-10-20.
//
#include <iostream>

#ifndef FILEMANAGEMENTSYSTEM_STACK_H
#define FILEMANAGEMENTSYSTEM_STACK_H
namespace stack {
    template<typename T>
    class Node {
    public:
        Node<T> *next;
        T value;

        Node(T value) : value{value} {}

    };


    template<typename T>
    class Stack {
    private:
        Node<T> *top;
        int height;
    public:
        Stack(T value);

        Stack();

        void printStack();

        bool pop();

        void push(T value);

        T peek();

        bool isEmpty();

        ~Stack();

    };

    template<typename T>
    Stack<T>::Stack(T value) : height{0} {
        auto *newNode = new Node<T>(value);
        top = newNode;
        height += 1;
    }
    template<typename T>
    Stack<T>::Stack() : height{0}, top{nullptr}{

    }

    template<typename T>
    Stack<T>::~Stack() {
        auto *temp = top;
        Node<T> *dumb;
        while (temp) {
            dumb = temp;
            temp = temp->next;
            delete dumb;
        }

    }

    template<typename T>
    void Stack<T>::printStack() {
        auto *temp = top;
        while (temp) {
            std::cout << temp->value << std::endl;
            temp = temp->next;
        }
    }

    template<typename T>
    bool Stack<T>::pop() {
        if (height == 0) {
            return false;
        }
        Node<T> *temp = top;
        top = top->next;
        height -= 1;
        delete temp;
        return true;
    }

    template<typename T>
    bool Stack<T>::isEmpty() {
        return (height == 0);
    }

    template<typename T>
    void Stack<T>::push(T value) {
        auto *newNode = new Node<T>(value);
        if (height == 0) {
            top = newNode;
        } else {
            newNode->next = top;
            top = newNode;
        }
        height += 1;

    }

    template<typename T>
    T Stack<T>::peek() {
        return top->value;
    }


}

#endif //FILEMANAGEMENTSYSTEM_STACK_H
