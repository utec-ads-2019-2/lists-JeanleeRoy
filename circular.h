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
            } else {
                if ( this->nodes == 1) {
                    temp->next = temp->prev = this->head;
                    this->head->prev = this->head->next = temp;
                } else {
                    temp->next = this->head;
                    temp->prev = this->head->prev;
                    this->head->prev->next = temp;
                    this->head->prev = temp;
                }
            } this->head = temp;
            this->nodes++;
        }

        void push_back(T value) {
            Node<T>* temp = new Node<T>(value);
            if ( this->empty() ){
                temp->next = temp->prev = this->head;
                this->head = temp;
            } 
            else {
                if ( this->nodes == 1) {
                    temp->next = temp->prev = this->head;
                    this->head->prev = this->head->next = temp;
                } else {
                    temp->next = this->head;
                    temp->prev = this->head->prev;
                    this->head->prev->next = temp;
                    this->head->prev = temp;
                }
            } this->nodes++;
        }

        void pop_front() {
            if (this->empty()) throw invalid_argument("Empty List!");
            Node<T>* temp = this->head;
            this->nodes--;
            if (this->nodes > 0) {
                this->head = this->head->next;
                this->head->prev = temp->prev;
                temp->prev->next = this->head;
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
            if (index < 0)
                throw out_of_range("Out of range");
            Node<T>* temp = this->head;
            int nodo = index%(this->nodes);
            for (int i = 0; i < nodo; ++i)
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
            if (this->empty()) return;
            Node<T>* temp = this->head;
            if (this->nodes > 1)
                for (int i = 0; i < this->nodes; ++i, temp = temp->next)
                delete temp->prev;
            delete temp;
            this->head = nullptr;
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

        void print() {
            if (this->nodes > 0) {
                Node<T>* temp = this->head;
                for (int i = 0; i < this->nodes; ++i){
                    cout << temp->data << " ";
                    temp = temp->next;
                } cout << endl;
            } else cout << "Empty List!";
        }

        string name() {
            return "Circular Linked List";
        }

        BidirectionalIterator<T> begin() {
            return BidirectionalIterator<T>(this->head);
        }

	    BidirectionalIterator<T> end() {
            return BidirectionalIterator<T>(this->head);
        }

        void merge(CircularLinkedList<T> &list) {
            Node<T>* temp = list.head;
            for (int i = 0; i < list.nodes; ++i, temp = temp->next)
                this->push_back(temp->data);
        }

        ~CircularLinkedList() {
            if (!this->empty()) {
                Node<T>* temp = this->head;
                if (this->nodes > 1)
                    for (int i = 0; i < this->nodes; ++i, temp = temp->next)
                    delete temp->prev;
                delete temp;
            }
        }
};

#endif