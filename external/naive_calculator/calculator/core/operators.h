#pragma once

class BinaryOperator {
 protected:
  int m_left;
  int m_right;

 public:
  BinaryOperator(int left, int right): m_left(left), m_right(right) {}

  int get_left() const {return m_left;}
  int get_right() const {return m_right;}

  virtual int compute() const = 0;
  virtual int the_ultimate_answer() const = 0;
};
