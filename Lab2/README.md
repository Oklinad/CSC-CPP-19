# Lab2

Шаблонный класс Polynomial («Многочлен от одной переменной»). 
Тип коэффициентов многочлена передаётся в качестве параметра шаблона. 
Хранение коэффициентов плотное (то есть, хранятся все коэффициенты, в том числе и промежуточные нулевые). 
Возможность работы с нецелыми или отрицательными степенями переменной не предусмотрена.

Подразумевается, что экземпляр класса создаётся так:
```
#include "polynomial.h"
int main (int argc, char∗ argv [ ]) {
  Polynomial<double> a ( . . . );
  Polynomial<double> b ( . . . );
  Polynomial<double> c = a * b;
  c = a / b;
  c ∗= 2;
  ...
}
```

# Build

```
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
```