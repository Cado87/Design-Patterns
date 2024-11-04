/**
 * Iterator Design Pattern
 *
 * Intent: Lets you traverse elements of a collection without exposing its
 * underlying representation (list, stack, tree, etc.).
 */

#include <iostream>
#include <string>
#include <vector>
#include <memory>

/**
 * C++ has its own implementation of iterator that works with a different
 * generics containers defined by the standard library.
 */

template <typename T, typename U>
class Iterator {
 public:
  typedef typename std::vector<T>::iterator iter_type;
  Iterator(U *p_data, bool reverse = false) : m_p_data_(p_data) {
    std::cout << "Constructor Iterator" << std::endl;
    m_it_ = m_p_data_->m_data_.begin();
  }
  ~Iterator(){
    std::cout << "Destructor Iterator" << std::endl;
  }

  void First() {
    //std::cout << "First" << std::endl;
    m_it_ = m_p_data_->m_data_.begin();
  }

  void Next() {
    //std::cout << "Next" << std::endl;
    m_it_++;
  }

  bool IsDone() {
    //std::cout << "IsDone" << std::endl;
    return (m_it_ == m_p_data_->m_data_.end());
  }

  iter_type Current() {
    //std::cout << "Current" << std::endl;
    return m_it_;
  }

 private:
  U *m_p_data_;
  iter_type m_it_;
};

/**
 * Generic Collections/Containers provides one or several methods for retrieving
 * fresh iterator instances, compatible with the collection class.
 */

template <class T>
class Container {
 friend class Iterator<T, Container>;

 public:
  void Add(T a) {
    //std::cout << "Add" << std::endl;
    m_data_.push_back(a);
  }

  Iterator<T, Container> *CreateIterator() {
    //std::cout << "CreateIterator" << std::endl;
    return new Iterator<T, Container>(this);
  }

Container(){
    std::cout << "Constructor Container" << std::endl;
  }

  ~Container(){
    std::cout << "Destructor Container" << std::endl;
  }

 private:
  std::vector<T> m_data_;
};

class Data {
 public:
  Data(int a = 0) : m_data_(a) {
    std::cout << "Constructor Data" << std::endl;
  }

  ~Data(){
    std::cout << "Destructor Data" << std::endl;
  }

  void set_data(int a) {
    std::cout << "set_data" << std::endl;
    m_data_ = a;
  }

  int data() {
    //std::cout << "data" << std::endl;
    return m_data_;
  }

 private:
  int m_data_;
};

/**
 * The client code may or may not know about the Concrete Iterator or Collection
 * classes, for this implementation the container is generic so you can used
 * with an int or with a custom class.
 */
void ClientCode() {
  std::cout << "________________Iterator with int______________________________________" << std::endl;
  Container<int> cont;

  for (int i = 0; i < 10; i++) {
    cont.Add(i);
  }

  //Iterator<int, Container<int>> *it = cont.CreateIterator();
  std::unique_ptr<Iterator<int, Container<int>>> it(cont.CreateIterator());
  for (it->First(); !it->IsDone(); it->Next()) {
    //std::cout << *it->Current() << std::endl;
  }

  Container<Data> cont2;
  Data a(100), b(1000), c(10000);
  cont2.Add(a);
  cont2.Add(b);
  cont2.Add(c);

  std::cout << "________________Iterator with custom Class______________________________" << std::endl;
  //Iterator<Data, Container<Data>> *it2 = cont2.CreateIterator();
  std::unique_ptr<Iterator<Data, Container<Data>>> it2(cont2.CreateIterator());
  for (it2->First(); !it2->IsDone(); it2->Next()) {
    //std::cout << it2->Current()->data() << std::endl;
  }
  //delete it;
  //delete it2;
}

int main() {
  ClientCode();
  return 0;
}