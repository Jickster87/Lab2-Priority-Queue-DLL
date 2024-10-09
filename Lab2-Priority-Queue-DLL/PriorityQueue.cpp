
#include "PriorityQueue.h"
#include <exception>
using namespace std;


PriorityQueue::PriorityQueue(Relation r) {
    head = tail = nullptr;
    rel = r;
    queueSize = 0;
}


void PriorityQueue::push(TElem e, TPriority p) {
    Element newElem(e,p);
    Node * newNode = new Node(newElem);
    //list empty
    if (isEmpty()) {
        head = tail = newNode;
    }
    //push according to p rel
    else {
        //set correct possition with nomad traveler node
        Node * nomad = head;
        while (nomad != nullptr && rel(nomad->elem.second, newNode->elem.second)) {
            nomad = nomad->next;
        }
        // Case 2: Insert at the head
        if (nomad == head) {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        // Case 3: Insert at the tail
        else if (nomad == nullptr) {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        // Case 4: Insert in the middle
        else {
            newNode->next = nomad;
            newNode->prev = nomad->prev;
            nomad->prev->next = newNode;
            nomad->prev = newNode;
        }
    }
    queueSize++;
}

//throws exception if the queue is empty
Element PriorityQueue::top() const {
    if (isEmpty()) {
        throw exception();
    }
    return head->elem;
}

Element PriorityQueue::pop() {
    if (isEmpty()) {
        throw exception();
    }
    
    // Save the element to return
    Element removedElem = head->elem;
    
    // Remove the head node
    Node* nodeToRemove = head;
    head = head->next;
    
    if (head != nullptr) {
        head->prev = nullptr;
    } else {
        // If the list is now empty, update the tail as well
        tail = nullptr;
    }
    
    // Delete the removed node and decrement the size
    delete nodeToRemove;
    queueSize--;
    
    return removedElem;
}

bool PriorityQueue::isEmpty() const {
    return queueSize == 0;
}


PriorityQueue::~PriorityQueue() {
    while (head != nullptr) {
        Node * temp = head;
        head = head->next;
        delete temp;
    }
};

