#ifndef FORWARD_H
#define FORWARD_H

#include "list.h"
#include "iterators/forward_iterator.h"
#include <vector>
#include <algorithm>

template <typename T>
class ForwardList : public List<T> {
    public:
        ForwardList() : List<T>() {}

        T front() {
            return (this->empty()) ? throw invalid_argument("Empty List!") : this->head->data;
        }

        T back() {
            return (this->empty()) ? throw invalid_argument("Empty List!") : this->tail->data;
        }

        void push_front(T value) {
            Node<T>* temp = new Node<T>(value);
            if ( this->empty() )
                this->head = this->tail = temp;
            else {
                temp->next = this->head;
                this->head = temp;
            } this->nodes++;
        }

        void push_back(T value) {
            Node<T>* temp = new Node<T>(value);
            if ( this->empty() )
                this->head = this->tail = temp;
            else {
                this->tail->next = temp;
                this->tail = temp;
            } this->nodes++;
        }

        void pop_front() {
            if (!this->empty()) {
                Node<T>* temp = this->head;
                this->head = this->head->next;
                delete temp;
                this->nodes--;
            } else throw invalid_argument("Empty List!");
        }

        void pop_back() {
            if (!this->empty()) {
                Node<T>* temp = this->head;
                while (temp->next != this->tail)
                    temp = temp->next;
                delete this->tail;
                this->tail = temp;
                this->tail->next = nullptr;
                this->nodes--;
            } else throw invalid_argument("Empty List!");
        }

        T operator[](int index) {
            if (index < this->nodes) {
                Node<T>* temp = this->head;
                for (int i = 0; i < index; ++i)
                    temp = temp->next;
                return temp->data;
            } else
                throw out_of_range("Out of range");
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
            for (int i = 0; i < this->nodes; ++i){
                sorted.push_back(temp->data);
                temp = temp->next;
            }
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
            return "Forward List";
        }

        ForwardIterator<T> begin() {
            // TODO
        }

	    ForwardIterator<T> end() {
            // TODO
        }

        void merge(ForwardList<T> &list) {
            Node<T>* temp = list.head;
            for (int i = 0; i < list.nodes; ++i){
                this->push_back(temp->data);
                temp = temp->next;
            }
        }

        void print() {
            Node<T>* temp = this->head;
            for (int i = 0; i < this->nodes; ++i){
                cout << temp->data << " ";
                temp = temp->next;
            }
            cout << endl;
        }

        ~ForwardList() {
            if (!this->empty()) this->head->killSelf();
        }
};

#endif