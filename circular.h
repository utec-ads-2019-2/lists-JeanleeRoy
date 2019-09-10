#ifndef CIRCULAR_H
#define CIRCULAR_H

#include "list.h"

template <typename T>
class CircularLinkedList : public List<T> {
    public:
        CircularLinkedList() : List<T>() {}

        T front() {
            return (this->empty()) ? throw invalid_argument("Empty List!") : this->head->data;
        }

        T back() {
            return (this->empty()) ? throw invalid_argument("Empty List!") : this->head->prev->data;
        }

        void push_front(T value) {
            Node<T>* temp = new Node<T>(value);
            if ( this->empty() ){
                temp->next = temp->prev = this->head;
                this->head = temp;
            } else {
                temp->next = this->head;
                temp->prev = this->head->prev;
                this->head->prev = temp;
                this->head = temp;
            } this->nodes++;
        }

        void push_back(T value) {
            Node<T>* temp = new Node<T>(value);
            if ( this->empty() ){
                temp->next = temp->prev = this->head;
                this->head = temp;
            } else {
                temp->next = this->head;
                temp->prev = this->head->prev;
                this->head->prev = temp;
            } this->nodes++;
        }

        void pop_front() {
            if (this->empty()) throw invalid_argument("Empty List!");
            Node<T>* temp = this->head;
            this->nodes--;
            if (this->nodes > 0) {
                this->head = this->head->next;
                this->head->prev = temp->prev;
            } else
                this->head = nullptr;
            delete temp;
        }

        void pop_back() {
            if (this->empty()) throw invalid_argument("Empty List!");
            Node<T>* temp = this->head->prev;
            this->nodes--;
            if (this->nodes > 0) {
                this->head->prev = temp->prev;
                temp->prev->next = this->head;
            } else
                this->head = nullptr;
            delete temp;
        }

        T operator[](int index) {
            if (index < 0 || index >= this->nodes)
                throw out_of_range("Out of range");
            Node<T>* temp = this->head;
            for (int i = 0; i < index; ++i)
                temp = temp->next;
            return temp->data;
        }

        bool empty() {
            return (this->head == nullptr);
        }

        int size() {
            return this->nodes;
        }

        void clear() {
            this->head->killSelf();
            this->head = this->tail = nullptr;
            this->nodes = 0;
        }

        void sort() {
            Node<T>* temp = this->head;
            vector<T> sorted;
            int n = this->nodes;
            for (int i = 0; i < this->nodes; ++i, temp = temp->next)
                sorted.push_back(temp->data);
            std::sort(sorted.begin(), sorted.end());
            this->clear();
            for (int j = 0; j < n; ++j)
                this->push_back(sorted[j]);
        }
    
        void reverse() {
            Node<T>* temp = this->head;
            int n = this->nodes;
            T arr[n];
            for (int i = 0; i < n; ++i, temp = temp->next)
                arr[n-1-i] = temp->data;
            this->clear();
            for (int j = 0; j < n; ++j)
                this->push_back(arr[j]);
        }

        string name() {
            return "Circular Linked List";
        }

        BidirectionalIterator<T> begin() {
            // TODO
        }

	    BidirectionalIterator<T> end() {
            // TODO
        }

        void merge(CircularLinkedList<T> &list) {
            Node<T>* temp = list.head;
            for (int i = 0; i < list.nodes; ++i, temp = temp->next)
                this->push_back(temp->data);
        }

        ~CircularLinkedList() {
            if (!this->empty()) this->head->killSelf();
        }
};

#endif