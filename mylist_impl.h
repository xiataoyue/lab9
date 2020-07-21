//
// Created by cyx on 20-5-29.
//

#ifndef INTLIST_IMPL_H
#define INTLIST_IMPL_H

#include <iostream>
#include "mylist.h"

template <class T>
void List<T>::print()
{
    node_t<T>* itr = first;
    while(itr){
        std::cout << itr->val;
        itr = itr->next;
    }
    std::cout << "\n";
}

template <class T>
void List<T>::removeAll() {
    while(first != NULL) removeFront();
    last = NULL;
}

template <class T>
void List<T>::copyFrom(const List<T> &l) {
    if(l.isEmpty()) return;
    if(first != NULL) removeAll();
    const node_t<T> *temp = l.returnHead();
    while(temp != NULL){
        this->insertBack(temp->val);
        temp = temp->next;
    }
    last->next = NULL;
}

template <class T>
bool List<T>::isEmpty() const {
    return !first;
}

template <class T>
void List<T>::insertBack(T val) {
    auto *node = new node_t<T>{NULL, val};
    if(this->isEmpty()){
        first = node;
        last = node;
    }
    else{
        last->next = node;
        last = node;
    }
}

template <class T>
T List<T>::removeFront() {
    if(this->isEmpty()) throw emptyList{};
    node_t<T> *rm = first;
    T temp = rm->val;
    first = first->next;

    delete rm;
    return temp;
}

template <class T>
const node_t<T> *List<T>::returnHead() const {
    return first;
}

template <class T>
List<T>::List():first(NULL), last(NULL) {}

template <class T>
List<T>::List(const List<T> &l): first(NULL), last(NULL) {
    copyFrom(l);
}

template <class T>
List<T>& List<T>::operator=(const List<T> &l) {
    copyFrom(l);
    return *this;
}

template <class T>
List<T>::~List() {
    removeAll();
}

int get_digit(const List<int> &l) {
    if(l.isEmpty()) return 0;
    int num = 0;
    const node_t<int> *temp = l.returnHead();
    while(temp != NULL){
        num++;
        temp = temp->next;
    }
    return num;
}

bool isLarger(const List<int> &a, const List<int> &b) {
    int d1 = get_digit(a);
    int d2 = get_digit(b);
    bool judge = false;

    if(d1 == 0) return false;

    if(d1 > d2) return true;
    else if(d1 < d2) return false;
    else{
        const node_t<int> *n1 = a.returnHead();
        const node_t<int> *n2 = b.returnHead();

        while(n1 != NULL){
            if(n1->val > n2->val) judge = true;
            if(n1->val < n2->val) judge = false;
            n1 = n1->next;
            n2 = n2->next;
        }
    }
    return judge;
}

List<int> Add(const List<int> &a, const List<int> &b) {
    List<int> l;
    const node_t<int> *n1 = a.returnHead();
    const node_t<int> *n2 = b.returnHead();
    int sum = 0;
    int carry = 0;

    while(n1 != NULL){
        if(n2 != NULL){
            sum = n1->val + n2->val + carry;
            if(sum >= 10){
                carry = 1;
                l.insertBack(sum - 10);
            }
            else{
                carry = 0;
                l.insertBack(sum);
            }
            n2 = n2->next;
        }
        else{
            sum = n1->val + carry;
            if(sum >= 10){
                carry = 1;
                l.insertBack(sum - 10);
            }
            else{
                carry = 0;
                l.insertBack(sum);
            }
        }
        n1 = n1->next;
    }

    while(n2 != NULL){
        sum = n2->val + carry;
        if(sum >= 10){
            carry = 1;
            l.insertBack(sum - 10);
        }
        else{
            carry = 0;
            l.insertBack(sum);
        }
        n2 = n2->next;
    }
    if(carry == 1) l.insertBack(1);
    return l;
}
#endif //INTLIST_IMPL_H
