#ifndef QUEUE
#define QUEUE
template <typename T>
struct Node {
    T data;
    Node<T>* next;
};

template <typename T>
class Queue {
private:
    Node<T>* nFront;
    Node<T>* nBack;
    Node<T>* nCurrent;
    int qSize;
public:
    //Constructors
    Queue();
    //Modifiers
    void push_back(T);
    void pop_front();
    //Get
    T front();
    int size();
    //Iteration
    void reset();
    void next();
    bool atEnd();
    T current();
};

/*
 * Implemention below
 * Cannot be seperated due to template
 */

//Constructors
template <typename T>
Queue<T>::Queue() {
    this->nFront=NULL;
    this->nBack=NULL;
    this->nCurrent=NULL;
    this->qSize=0;
}

//Modifiers
template <typename T>
void Queue<T>::push_back(T data){
    Node<T>* tmp=new Node<T>;
    tmp->data=data;
    tmp->next=NULL;
    if(this->qSize>0) {
        this->nBack->next=tmp;
        this->nBack=tmp;
    } else {
        this->nFront=tmp;
        this->nBack=tmp;
    }
    this->qSize++;
}

template <typename T>
void Queue<T>::pop_front() {
    Node<T>* tmp=this->nFront;
    this->nFront=this->nFront->next;
    delete tmp;
    tmp=NULL;
    this->qSize--;
}

//Get
template <typename T>
T Queue<T>::front() {
    return this->nFront->data;
}

template <typename T>
int Queue<T>::size() {
    return this->qSize;
}

//Iteration
template <typename T>
void Queue<T>::reset() {
    this->nCurrent=this->nFront;
}

template <typename T>
void Queue<T>::next() {
    this->nCurrent=this->nCurrent->next;
}

template <typename T>
bool Queue<T>::atEnd() {
    if(!this->nCurrent) {return true;}
    else {return false;}
}

template <typename T>
T Queue<T>::current() {
    return this->nCurrent->data;
}
#endif