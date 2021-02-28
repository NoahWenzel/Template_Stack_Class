#ifndef ORDEREDLINKEDLIST_H
#define ORDEREDLINKEDLIST_H
#include <iostream>

template <class Type>
struct Node {
	Type data;
	Node<Type>* next = nullptr;
};

template <class Type>
class Stack;

template <class Type>
std::ostream& operator<<(std::ostream&, const Stack<Type>& stack);

template <class Type>
class Stack {
public:
	Stack(){}
	Stack(const Stack& other);
	Stack<Type>& operator=(const Stack<Type>& other);
	~Stack();

    int size() const;
    bool empty() const;
	Type top() const;
	void push(const Type&);
	void pop();
    void pop(int);
    Type topPop();
    void clear();

    friend std::ostream& operator<< <>(std::ostream&, const Stack<Type>& list);

private:
    Node<Type>* front_ = nullptr;
    int size_ = 0;

    std::ostream& recursive_output(std::ostream& out, const Node<Type>* curr) const;
    void recursive_copy(const Node<Type>* curr);
};

/**
 * @brief A helper to the copy constructors to recursively traverse the linked list in reverse so the copy
 *       constructor can copy the data in the correct order.
 * @param curr - Type: The list to be copied.
 */
template <class Type>
void Stack<Type>::recursive_copy(const Node<Type>* curr) {
    if (curr == nullptr) {
        return;
    } else {
        recursive_copy(curr->next);
        push(curr->data);
    }
}

/**
 * @brief Copy Constructor.
 * @param other - The object to be copied.
 */
template <class Type>
Stack<Type>::Stack(const Stack<Type>& other) {
    recursive_copy(other.front_);
}

/**
 * @brief = operator copy constructor.
 * @param other - The object to be copied.
 * @return Stack object that is a deep copy of other.
 */
template <class Type>
Stack<Type>& Stack<Type>::operator=(const Stack& other) {
    if (this != &other) {
        clear();
        recursive_copy(other.front_);
    }
    return *this;
}

/**
 * @brief Destructor.
 */
template <class Type>
Stack<Type>::~Stack() {
    Node<Type>* temp = front_;
    while (front_ != nullptr) {
        temp = front_;
        front_ = front_->next;
        delete temp;
    }
}

/**
 * @brief Returns the size of the stack.
 * @return int - The size of the stack.
 */
template <class Type>
int Stack<Type>::size() const {
return size_;
}

/**
 * @brief Determines if the stack is empty.
 * @return bool - true: If the stack is empty.
 *               false: If the stack is not empty.
 */
template <class Type>
bool Stack<Type>::empty() const {
    if (size_ == 0) {
        return true;
    }
    return false;
}

/**
 * @brief Returns the data from the item in the top of the stack. May return an error if the stack is empty.
 * @return Type - The data from the item in the top of the stack.
 * @error logic_error - Will be thrown if the stack is empty.
 */
template <class Type>
Type Stack<Type>::top() const {
    if (front_ == nullptr) {
        throw std::logic_error("The stack is empty! There is nothing to return!!!!!!!");
    }
    Type top = front_->data;
    return top;
}

/**
 * @brief Pushes an item to the top of the stack which is also the front.
 * @param item - Type: The data to be pushed to the stack.
 */
template <class Type>
void Stack<Type>::push(const Type& item) {
    size_++;
    auto temp = new Node<Type>();
    temp->data = item;
    temp->next = front_;
    front_ = temp;
}

/**
 * @brief Pops the top item from the stack.
 */
template <class Type>
void Stack<Type>::pop() {
    pop(1);
}

/**
 * @brief Pops the number of items given from the front of the stack. If the number is greater than the number
 *       of items in the list then all will be popped.
 * @param count - int: How many items will be removed from the top of the stack.
 */
template <class Type>
void Stack<Type>::pop(int count) {
    while (front_ != nullptr && count > 0) {
        auto toDelete = front_;
        front_ = front_->next;
        delete toDelete;
        size_--;
        count--;
    }
}

/**
 * @brief Returns the data from the top of the stack while also popping the item from the stack.
 * @return Type - The data from the item at the top of the list.
 */
template <class Type>
Type Stack<Type>::topPop() {
    Type top = this->top();
    pop();

    return top;
}

/**
 * @brief Deletes the entire stack clearing all data and resetting the stack object to an empty state.
 */
template <class Type>
void Stack<Type>::clear() {
    Node<Type>* temp = front_;
    while (front_ != nullptr) {
        temp = front_;
        front_ = front_->next;
        delete temp;
    }
    size_ = 0;
}

/**
 * @brief A helper function to the << operator overload function. This returns the stack from bottom to top
 *       of the stack with '->' between each data item. Ex: 1->2->3->4 with 4 being the top of the stack.
 * @param out - The ostream object to which the data will be written.
 * @param curr - The Node to start from.
 * @return out - ostream object to which the data is written.
 */
template <class Type>
std::ostream& Stack<Type>::recursive_output(std::ostream &out, const Node<Type> *curr) const {
    if (curr == nullptr) {
        return out;
    }
    if (curr->next == nullptr) {
        out << curr->data;
    } else {
        recursive_output(out, curr->next);
        out << "->";
        out << curr->data;
    }
    return out;
}

/**
 * @brief A helper function to the << operator overload function. This returns the stack from bottom to top
 *       of the stack with '->' between each data item. Ex: 1->2->3->4 with 4 being the top of the stack.
 * @param out - The ostream object to which the data will be written.
 * @param list - The Node to start from.
 * @return out - ostream object to which the data is written.
 */
template <class Type>
std::ostream& operator<<(std::ostream& out, const Stack<Type>& list) {
    list.recursive_output(out, list.front_);
    return out;
}
#endif
