#pragma once


class Node {
  private:
    Node* prev{nullptr};
    int value{};
    int i;
    int j;

  public:
      Node(int i, int j) {
          this->i = i;
          this->j = j;
      }

      void change_value(int new_value) {value = new_value;}
      void change_prev(Node* new_prev) {prev = new_prev;}
      int get_i() {return this->i;}
      int get_j() {return this->j;}
      int get_value() {return this->value;}
      Node* get_prev() {return prev;}
};
