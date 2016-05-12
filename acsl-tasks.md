# Задачи на ACSL

## Тип 1. Написать код(полностью корректный) в соответствии со спецификацией
### Задание 1. Найти среднее арифметическое двух чисел
#### Вариант 1.
Задание:
```c
/*@ requires a >= 0 && b >= 0;
    requires b >= a;
    assigns \nothing;
    ensures \result == (a+b)/2;
*/
int average(int a, int b)
{
   int average = 0;
   // Your code here
   return average;
}
```
Решение:
```c
   average = a + (b - a) / 2;
```
#### Вариант 2.
Задание:
```c
/*@ requires a >= 0 && b >= 0;
    requires a >= b;
    assigns \nothing;
    ensures \result == (a+b)/2;
*/
int average(int a, int b)
{
   int average = 0;
   // Your code here
   return average;
}

```
Решение:
```c
   average = b + (a - b) / 2;
```
#### Вариант 3.
Задание:
```c
/*@ requires a <= 0 && b <= 0;
    requires b <= a;
    assigns \nothing;
    ensures \result == (a+b)/2;
*/
int average(int a, int b)
{
   int average = 0;
   // Your code here
   return average;
}

```
Решение:
```c
   average = a + (b - a) / 2;
```
#### Вариант 4.
Задание:
```c
/*@ requires a <= 0 && b <= 0;
    requires a <= b;
    assigns \nothing;
    ensures \result == (a+b)/2;
*/
int average(int a, int b)
{
   int average = 0;
   // Your code here
   return average;
}

```
Решение:
```c
   average = b + (a - b) / 2;
```
#### Вариант 5.
Задание:
```c
/*@ axiomatic sign {
    logic integer get_sign(integer i);

    axiom zero:
       0 == get_sign(0);
    axiom positive:
       \forall integer i; i > 0 ==> get_sign(i) == 1;
    axiom negative:
       \forall integer i; i < 0 ==> get_sign(i) == -1;
    }
 */

/*@ requires get_sign(a) == get_sign(b);
    assigns \nothing;
    ensures \result == (a+b)/2;
*/
int average(int a, int b)
{
   int average = 0;
   // Your code here
   return average;
}
```
Решение:
```c
int greater;
int smaller;
if (a > b) {
   greater = a;
   smaller = b;
} else {
   greater = b;
   smaller = a;
}
if (a >= 0 && b >= 0) {
   average = smaller + (greater - smaller) / 2;
} else {
   average = greater + (smaller - greater) / 2;
}
```
#### Вариант 6.
Задание:
```c
/*@ assigns \nothing;
    ensures \result == (a+b)/2;
*/
int average(int a, int b)
{
   int average = 0;
   // Your code here
   return average;
}
```
Решение:
```c
int greater;
int smaller;
if (a > b) {
   greater = a;
   smaller = b;
} else {
   greater = b;
   smaller = a;
}
if (a >= 0 && b >= 0) {
   average = smaller + (greater - smaller) / 2;
} else if (a < 0 && b < 0) {
   average = greater + (smaller - greater) / 2;
} else if (a >= 0 && b <= 0 || a <= 0 && b >= 0) {
   average = (a + b) / 2;
}
```
### Задание 2. Напишите полностью корректную функцию в соответствии со спецификацией
#### Вариант 1.
Задание (используйте две целочисленных переменных a и b в качестве входных переменных):
```c
/*@ requires \true;
    assigns \nothing;
    ensures \result == \max(a, b) - \min(a, b);
 */
```
Ответ:
```c
unsigned distance(unsigned a, unsigned b)
{
   unsigned res;
   a > b && (res = a - b) || (res = b - a);
   return res;
}
```
#### Вариант 2.
Задание (используйте знаковую целочисленную переменную a в качестве входного аргумента):
```c
#define INT_MIN -2147483648
#define INT_MAX 2147483647

/*@ assigns \nothing;
    ensures \result >= 0;
    behavior positive:
       assumes a > 0;
       ensures \result == a;
    behavior zero:
       assumes a == 0;
       ensures \result == 0;
       ensures \result == a;
    behavior negative:
       assumes a < 0;
       ensures \result == -a;
    complete behaviors;
    disjoint behaviors;
 */
```
Ответ:
```c
long abs(int a)
{
   long abs;

   abs = a;
   if (a < 0) {
      abs = -abs;
   }

   return abs;
}
```
#### Вариант 3.
Задание:
```c
```
Ответ:
```c
```
## Тип 2. Найти ошибку в спецификациях
### Задание 1. Найдите все ошибки в спецификации, в предположении что все предусловия и инварианты выписаны (дописывать ничего не нужно), а функция полностью корректна
#### Вариант 1.
Задание:
```c
/*@ requires \valid(a+(0..n-1));
    requires \forall integer i, j; 0 <= i < j < n ==> a[i] <= a[j];
    assigns \nothing;
    behavior NOT_EXISTS:
       assumes \forall integer i; 0 <= i < n ==> a[i] != key;
       ensures \result == \null; 
    behavior EXISTS:
       assumes \exists integer i; 0 <= i < n && a[i] == key;
       ensures \exists integer i; 0 <= i < n && \result == (a + i);
       ensures (*\result) == key;
    complete behaviors;
    disjoint behaviors;
 */
int *bsearch(int a[], unsigned n, int key)
{
   unsigned left = 0;
   long right = ((long)n) - 1;

   /*@ loop invariant 0 <= left <= right < n;
       loop invariant \forall integer i; 0 <= i < n && a[i] == key ==> left <= i <= right;
       loop invariant \forall integer i; 0 <= i < n && a[i] == key ==> a[left] <= key <= a[right];
       loop variant right - left;
    */
   while (left <= right) {
      unsigned m = left + (right - left) / 2;

      if (a[m] < key) {
         left = m + 1;
      } else if (a[m] > key) {
         right = ((long)m) - 1;
      } else {
         return &a[m];
      }
   }
   return NULL;
}
```
Ответ:
```c
left <= right //ошибка
```
### Задание 2. Исправьте/допишите предусловия, в предположении что код полностью корректен
#### Вариант 1.
Задание:
```c
#define INT_MIN -2147483648
#define INT_MAX 2147483647

/*@ assigns \nothing;
    ensures \result >= 0;
    behavior positive:
       assumes a > 0;
       ensures \result == a;
    behavior zero:
       assumes a == 0;
       ensures \result == 0;
       ensures \result == a;
    behavior negative:
       assumes a < 0;
       ensures \result == -a;
    complete behaviors;
    disjoint behaviors;
 */
int abs(int a)
{
   int abs;

   if (a < 0) {
      abs = -a;
   } else {
      abs = a;
   }

   return abs;
}

```
Ответ:
```c
//requires INT_MIN < a <= INT_MAX;
requires INT_MIN < a;
```
## Тип 3. Напишите спецификацию
### Задание 1. Напишите инвариант на цикл и оценочную функцию
#### Вариант 1.
Задание:
```c
/*@ axiomatic Sum {
    logic integer sum(integer a, integer b);

    axiom sum_init:
       \forall integer a, b; (a >= 0 && b >= 0) && b <= a ==> sum(a, b) == a;

    axiom sum_step_dec:
       \forall integer a, b; (a >= 0 && b >= 0) && b > a ==> sum(a, b) == sum(a, b - 1) + b;

    lemma sum_lower_bound:
       \forall integer a, b; a >= 0 && b >= 0 ==> sum(a, b) >= a;

    lemma sum_increases:
       \forall integer i, a, b; (a >= 0 && b >= 0) && b > a && a <= i <= b ==> sum(a, i) <= sum(a, b);
    }
 */

#define INT_MAX 32767

/*@ requires a < b;
    requires a >= 0 && b >= 0;
    requires sum(a, b) < INT_MAX;
    assigns \nothing;
    ensures \result == sum(a, b);
 */
int sum(int a, int b)
{
   int i;
   int sum = a;

   for(i = a + 1; i <= b; ++i) {
      sum += i;
   }

   return sum;
}
```
Ответ:
```c
   /*@ loop invariant a < i <= (b+1);
       loop invariant sum == sum(a, i - 1);
       //loop invariant sum(a, i - 1) < INT_MAX; Доказывается и без него
       loop variant b - i;
    */
```
#### Вариант 2.
Задание:
```c
/*@ axiomatic Sum {
    logic integer sum{L}(unsigned *a, integer b);

    axiom init{L}:
       \forall unsigned *a, integer b; b <= 0 ==> sum(a, b) == 0;

    axiom step_dec{L}:
       \forall unsigned *a, integer b; sum(a, b) == sum(a, b-1) + a[b];

    lemma lower_bound:
       \forall unsigned *a, integer b; sum(a, b) >= 0;

    lemma sum_increases:
       \forall unsigned *a, integer i, b; 0 <= i <= b ==> sum(a, i) <= sum(a, b);
    }
 */

#define UINT_MAX 32767

/*@ requires \valid(a+(0..n-1));
    requires sum(a, n) < UINT_MAX;
    assigns \nothing;
    ensures \result == sum(a, n-1);
 */
unsigned sum(unsigned a[], unsigned n)
{
   unsigned i;
   unsigned sum = 0;

   for(i = 0; i < n; ++i) {
      sum += a[i];
   }

   return sum;
}
```
Ответ:
```c
   /*@ loop invariant 0 <= i <= n;
       loop invariant sum == sum(a, i-1);
       //loop invariant sum(a, i-1) < UINT_MAX; Не обязательно
       loop variant n - i;
    */
```
### Задание 2. Перепишите спецификацию с использованием предикатов
### Задание 3. Напишите спецификацию на функцию(контракт и инвариант на цикл), в предположении что код полностью корректен
#### Вариант 1.
Задание (в спецификации должно быть отображено, 1) функция присваивает значение val каждому чётному элементу массива; 2) остальные элементы остаются неизменными):
```c
void set_even(int *p, unsigned size, int val)
{
   unsigned i;
   for(i = 0; i < size; ++i) {
      if (i % 2 == 0) {
         p[i] = val;
      }
   }
}
```
Ответ:
```c
/*@ requires \valid(p+(0..size-1));
    assigns p[0..size-1];
    ensures \forall integer j; 0 <= j < size && j % 2 == 0 ==> p[j] == val;
    ensures \forall integer j; 0 <= j < size && j % 2 != 0 ==> p[j] == \old(p[j]);
 */
void set_even(int *p, unsigned size, int val)
{
   unsigned i;
   /*@ loop invariant 0 <= i <= size;
       loop invariant \forall integer j; 0 <= j < i && j % 2 == 0 ==> p[j] == val;
       loop invariant \forall integer j; 0 <= j < i && j % 2 != 0 ==>
          p[j] == \at(p[\at(j,Here)], Pre);
       loop assigns i, p[0..i-1];
       loop variant size - i;
    */
   for(i = 0; i < size; ++i) {
      if (i % 2 == 0) {
         p[i] = val;
      }
   }
}
```
#### Вариант 2.
Задание (в спецификации должно быть отображено, 1) функция присваивает значение val каждому нечётному элементу массива; 2) остальные элементы остаются неизменными):
```c
void set_odd(int *p, unsigned size, int val)
{
   unsigned i;
   for(i = 0; i < size; ++i) {
      if (i % 2 != 0) {
         p[i] = val;
      }
   }
}
```
Ответ:
```c
/*@ requires \valid(p+(0..size-1));
    assigns p[0..size-1];
    ensures \forall integer j; 0 <= j < size && j % 2 != 0 ==> p[j] == val;
    ensures \forall integer j; 0 <= j < size && j % 2 == 0 ==> p[j] == \old(p[j]);
 */
void set_odd(int *p, unsigned size, int val)
{
   unsigned i;
   /*@ loop invariant 0 <= i <= size;
       loop invariant \forall integer j; 0 <= j < i && j % 2 != 0 ==> p[j] == val;
       loop invariant \forall integer j; 0 <= j < i && j % 2 == 0 ==>
          p[j] == \at(p[\at(j,Here)], Pre);
       loop assigns i, p[0..i-1];
       loop variant size - i;
    */
   for(i = 0; i < size; ++i) {
      if (i % 2 != 0) {
         p[i] = val;
      }
   }
}
```
#### Вариант 3.
Задание (в спецификации должно быть отображено, 1) функция присваивает значение val каждому третьему элементу массива; 2) остальные элементы остаются неизменными):
```c
void set_only_third(int *p, unsigned size, int val)
{
   unsigned i;
   for(i = 0; i < size; ++i) {
      if (i % 3 == 0) {
         p[i] = val;
      }
   }
}
```
Ответ:
```c
/*@ requires size >= 0;
    requires \valid(p+(0..size-1));
    assigns p[0..size-1];
    ensures \forall integer j; 0 <= j < size && j % 3 == 0 ==> p[j] == val;
    ensures \forall integer j; 0 <= j < size && j % 3 != 0 ==> p[j] == \old(p[j]);
 */
void set_only_third(int *p, unsigned size, int val)
{
   unsigned i;
   /*@ loop invariant 0 <= i <= size;
       loop invariant \forall integer j; 0 <= j < i && j % 3 == 0 ==> p[j] == val;
       loop invariant \forall integer j; 0 <= j < i && j % 3 != 0 ==> p[j] == \at(p[\at(j,Here)], Pre);
       loop assigns i, p[0..i-1];
       loop variant size - i;
    */
   for(i = 0; i < size; ++i) {
      if (i % 3 == 0) {
         p[i] = val;
      }
   }
}
```
#### Вариант 4.
Задание (в спецификации должно быть отображено, 1) функция оставляет неизменными значения каждого третьего элемента массива; 2) остальным элементам присваивается значение val с порядковым номером элемента по модулю три):
```c
#define INT_MAX 32767

void set_skip_third(int *p, unsigned size, int val)
{
   unsigned i;
   for(i = 0; i < size; ++i) {
      if (i % 3 != 0) {
         p[i] = val + i % 3;
      }
   }
}
```
Ответ:
```c
#define INT_MAX 32767

/*@ requires size >= 0;
    requires \valid(p+(0..size-1));
    requires val + 2 < INT_MAX;
    assigns p[0..size-1];
    ensures \forall integer j; 0 <= j < size && j % 3 != 0 ==> p[j] == val + j % 3;
    ensures \forall integer j; 0 <= j < size && j % 3 == 0 ==> p[j] == \old(p[j]);
 */
void set_skip_third(int *p, unsigned size, int val)
{
   unsigned i;
   /*@ loop invariant 0 <= i <= size;
       loop invariant \forall integer j; 0 <= j < i && j % 3 != 0 ==> p[j] == val + j % 3;
       loop invariant \forall integer j; 0 <= j < i && j % 3 == 0 ==> p[j] == \at(p[\at(j,Here)], Pre);
       loop assigns i, p[0..i-1];
       loop variant size - i;
    */
   for(i = 0; i < size; ++i) {
      if (i % 3 != 0) {
         p[i] = val + i % 3;
      }
   }
}
```
#### Вариант 5.
Задание:
```c
int sign(int x)
{
   return (x > 0) - (x < 0);
}
```
Ответ:
```c
/*@ assigns \nothing;
    ensures \result == 0 || \result == 1 || \result == -1;
    behavior positive:
       assumes x > 0;
       ensures \result == 1;
    behavior zero:
       assumes x == 0;
       ensures \result == 0;
    behavior negative:
       assumes x < 0;
       ensures \result == -1;
    complete behaviors;
    disjoint behaviors;
 */
int sign(int x)
{
   return (x > 0) - (x < 0);
}
```
#### Вариант 6.
Задание (в спецификации должно быть отображено, 1) функция оставляет неизменными значения каждого третьего элемента массива; 2) каждый чётный элемент приравнивается единице; 3) остальные элементы приравниваются нулю):
```c
void set_odd_even_skip(int a[], unsigned n)
{
   unsigned i;
   for(i = 0; i < n; ++i) {
      if (i % 3 == 0) {
         continue;
      } else if (i % 2 == 0) {
         a[i] = 1;
      } else {
         a[i] = 0;
      }
   }
}
```
Ответ:
```c
/*@ requires \valid(a+(0..n-1));
    assigns a[0..n-1];
    ensures \forall integer i; 0 <= i < n && (i % 2 == 0) && (i % 3 != 0) ==> a[i] == 1;
    ensures \forall integer i; 0 <= i < n && (i % 2 == 1) && (i % 3 != 0) ==> a[i] == 0;
    ensures \forall integer i; 0 <= i < n && (i % 3 == 0) ==> a[i] == \old(a[i]);
 */
void set_odd_even_skip(int a[], unsigned n)
{
   unsigned i;
   /*@ loop invariant 0 <= i <= n;
       loop invariant \forall integer j; 0 <= j < i && j % 2 == 0 && j % 3 != 0 ==> a[j] == 1;
       loop invariant \forall integer j; 0 <= j < i && j % 2 == 1 && j % 3 != 0 ==> a[j] == 0;
       loop invariant \forall integer j; 0 <= j < i && j % 3 == 0 ==> a[j] == \at(a[\at(j,Here)], Pre);
       loop assigns a[0..i-1];
       loop variant n - i;
    */
   for(i = 0; i < n; ++i) {
      if (i % 3 == 0) {
         continue;
      } else if (i % 2 == 0) {
         a[i] = 1;
      } else {
         a[i] = 0;
      }
   }
}
```
## Тип 4. Найдите ошибки в реализации, принимая во внимание что спецификация полна и корректна
### Задание 1.
#### Вариант 1.
Задание:
```c
/*@ requires \valid(a+(0..size-1));
    requires \valid(max);
    requires \valid(min);
    behavior zero_size:
       assumes size == 0;
       assigns \nothing;
       ensures max == \old(max) && min == \old(min);
    behavior positive_size:
       assumes size > 0;
       assigns *max, *min;
       ensures \exists integer i; 0 <= i < size && (a + i) == *max;
       ensures \exists integer i; 0 <= i < size && (a + i) == *min;
       ensures **max >= **min;
       ensures \forall integer i; 0 <= i < size ==> **max >= a[i] >= **min;
    complete behaviors;
    disjoint behaviors;
 */
void max_min(int a[], unsigned size, int **max, int **min)
{
   int i;
   *max = &a[0];
   *min = *max;
   /*@ loop invariant 1 <= i <= size;
       loop invariant \exists integer j; 0 <= j < i && (a+j) == *max;
       loop invariant \exists integer j; 0 <= j < i && (a+j) == *min;
       loop invariant **max >= **min;
       loop invariant \forall integer j; 0 <= j < i ==> **max >= a[j] >= **min;
       loop assigns *max, *min;
       loop variant size - i;
    */
   for(i = 1; i < size; ++i) {
      if (**max < a[i]) {
         *max = &a[i];
      } else if (**min > a[i]) {
         *min = &a[i];
      }
   }
}
```
Ответ:
```c
/*@ requires \valid(a+(0..size-1));
    requires \valid(max);
    requires \valid(min);
    behavior zero_size:
       assumes size == 0;
       assigns \nothing;
       ensures max == \old(max) && min == \old(min);
    behavior positive_size:
       assumes size > 0;
       assigns *max, *min;
       ensures \exists integer i; 0 <= i < size && (a + i) == *max;
       ensures \exists integer i; 0 <= i < size && (a + i) == *min;
       ensures **max >= **min;
       ensures \forall integer i; 0 <= i < size ==> **max >= a[i] >= **min;
    complete behaviors;
    disjoint behaviors;
 */
void max_min(int a[], unsigned size, int **max, int **min)
{
   if (size > 0) { // <== if
      unsigned i;  // <== int
      *max = &a[0];
      *min = *max;
      /*@ loop invariant 1 <= i <= size;
          loop invariant \exists integer j; 0 <= j < i && (a+j) == *max;
          loop invariant \exists integer j; 0 <= j < i && (a+j) == *min;
          loop invariant **max >= **min;
          loop invariant \forall integer j; 0 <= j < i ==> **max >= a[j] >= **min;
          loop assigns *max, *min;
          loop variant size - i;
       */
      for(i = 1; i < size; ++i) {
         if (**max < a[i]) {
            *max = &a[i];
         } else if (**min > a[i]) {
            *min = &a[i];
         }
      }
   }
}
```
#### Вариант 2.
Задание:
```c
/*@ requires \valid(a+(0..size-1));
    requires \valid(min1) && \valid(min2);
    behavior zero_size:
       assumes size == 0;
       assigns \nothing;
       ensures min1 == \old(min1);
       ensures min2 == \old(min2);
    behavior positive_size:
       assumes size > 0;
       assigns *min1, *min2;
       ensures \valid(min1) && \valid(min2);
       ensures \exists integer i; 0 <= i < size && (a + i) == *min1;
       ensures \exists integer i; 0 <= i < size && (a + i) == *min2;
       ensures **min1 <= **min2;
       ensures \forall integer i; 0 <= i < size ==> a[i] >= **min1;
       ensures \exists integer i; 0 <= i < size && a[i] <= **min2 && a[i] == **min1;
       ensures ! (\exists integer i,j; 0 <= i < size && 0 <= j < size && i != j && (a[i] < **min2 && a[j] < **min2 && a[i] < a[j]));
    complete behaviors;
    disjoint behaviors;
 */
void min_min(int *a, unsigned size, int **min1, int **min2)
{
   unsigned i;
   *min1 = &a[0];
   *min2 = *min1;

   /*@ loop invariant 0 < i <= size;
       loop invariant \exists integer j; 0 <= j < i && (a + j) == *min1;
       loop invariant \exists integer j; 0 <= j < i && (a + j) == *min2;
       loop invariant **min1 <= **min2;
       loop invariant \forall integer j; 0 <= j < i ==> a[j] >= **min1;
       loop invariant \exists integer j; 0 <= j < i && a[j] <= **min2 && a[j] == **min1;
       loop invariant ! (\exists integer j,k; 0 <= j < i && 0 <= k < i && j != k && (a[j] < **min2 && a[k] < **min2 && a[k] < a[j]));
       loop assigns *min1, *min2;
       loop variant size - i;
    */
   for(i = 1; i < size; ++i) {
      if (a[i] < **min1) {
         *min1 = &a[i];
      } else if (a[i] < **min2) {
         *min2 = &a[i];
      }
   }
}
```
Ответ:
```c
/*@ requires \valid(a+(0..size-1));
    requires \valid(min1) && \valid(min2);
    behavior zero_size:
       assumes size == 0;
       assigns \nothing;
       ensures min1 == \old(min1);
       ensures min2 == \old(min2);
    behavior positive_size:
       assumes size > 0;
       assigns *min1, *min2;
       ensures \valid(min1) && \valid(min2);
       ensures \exists integer i; 0 <= i < size && (a + i) == *min1;
       ensures \exists integer i; 0 <= i < size && (a + i) == *min2;
       ensures **min1 <= **min2;
       ensures \forall integer i; 0 <= i < size ==> a[i] >= **min1;
       ensures \exists integer i; 0 <= i < size && a[i] <= **min2 && a[i] == **min1;
       ensures ! (\exists integer i,j; 0 <= i < size && 0 <= j < size && i != j && (a[i] < **min2 && a[j] < **min2 && a[i] < a[j]));
    complete behaviors;
    disjoint behaviors;
 */
void min_min(int *a, unsigned size, int **min1, int **min2)
{

   if (size > 0) { // <== добавить
      unsigned i;
      *min1 = &a[0];
      *min2 = *min1;

      /*@ loop invariant 0 < i <= size;
          loop invariant \exists integer j; 0 <= j < i && (a + j) == *min1;
          loop invariant \exists integer j; 0 <= j < i && (a + j) == *min2;
          loop invariant **min1 <= **min2;
          loop invariant \forall integer j; 0 <= j < i ==> a[j] >= **min1;
          loop invariant \exists integer j; 0 <= j < i && a[j] <= **min2 && a[j] == **min1;
          loop invariant ! (\exists integer j,k; 0 <= j < i && 0 <= k < i && j != k && (a[j] < **min2 && a[k] < **min2 && a[k] < a[j]));
          loop assigns *min1, *min2;
          loop variant size - i;
       */
      for(i = 1; i < size; ++i) {
         if (a[i] < **min1) {
            *min2 = *min1; // <== добавить
            *min1 = &a[i];
         } else if (a[i] < **min2) {
            *min2 = &a[i];
         }
      }
   }
}
```
#### Вариант 3.
Задание:
```c
/*@ requires \valid(a+(0..size-1));
    requires \valid(max1) && \valid(max2);
    behavior zero_size:
       assumes size == 0;
       assigns \nothing;
       ensures max1 == \old(max1);
       ensures max2 == \old(max2);
    behavior positive_size:
       assumes size > 0;
       assigns *max1, *max2;
       ensures \valid(max1) && \valid(max2);
       ensures \exists integer i; 0 <= i < size && (a + i) == *max1;
       ensures \exists integer i; 0 <= i < size && (a + i) == *max2;
       ensures **max1 >= **max2;
       ensures \forall integer i; 0 <= i < size ==> a[i] <= **max1;
       ensures \exists integer i; 0 <= i < size && a[i] >= **max2 && a[i] == **max1;
       ensures ! (\exists integer i,j; 0 <= i < size && 0 <= j < size && i != j && (a[i] > **max2 && a[j] > **max2 && a[i] > a[j]));
       //ensures (size > 1) ==> (\exists integer i,j; 0 <= i < size && 0 <= j < size && i != j);
    complete behaviors;
    disjoint behaviors;
 */
void max_max(int *a, unsigned size, int **max1, int **max2)
{
   int i;
   *max1 = &a[0];
   *max2 = *max1;

   /*@ loop invariant 0 < i <= size;
       loop invariant \exists integer j; 0 <= j < i && (a + j) == *max1;
       loop invariant \exists integer j; 0 <= j < i && (a + j) == *max2;
       loop invariant **max1 >= **max2;
       loop invariant \forall integer j; 0 <= j < i ==> a[j] <= **max1;
       loop invariant \exists integer j; 0 <= j < i && a[j] >= **max2 && a[j] == **max1;
       loop invariant ! (\exists integer j,k; 0 <= j < i && 0 <= k < i && j != k && (a[j] > **max2 && a[k] > **max2 && a[k] > a[j]));
       loop assigns *max1, *max2;
       loop variant size - i;
    */
   for(i = 1; i < size; ++i) {
      if (a[i] > **max1) {
         *max1 = &a[i];
      } else if (a[i] > **max2) {
         *max2 = &a[i];
      }
   }
}
```
Ответ:
```c
/*@ requires \valid(a+(0..size-1));
    requires \valid(max1) && \valid(max2);
    behavior zero_size:
       assumes size == 0;
       assigns \nothing;
       ensures max1 == \old(max1);
       ensures max2 == \old(max2);
    behavior positive_size:
       assumes size > 0;
       assigns *max1, *max2;
       ensures \valid(max1) && \valid(max2);
       ensures \exists integer i; 0 <= i < size && (a + i) == *max1;
       ensures \exists integer i; 0 <= i < size && (a + i) == *max2;
       ensures **max1 >= **max2;
       ensures \forall integer i; 0 <= i < size ==> a[i] <= **max1;
       ensures \exists integer i; 0 <= i < size && a[i] >= **max2 && a[i] == **max1;
       ensures ! (\exists integer i,j; 0 <= i < size && 0 <= j < size && i != j && (a[i] > **max2 && a[j] > **max2 && a[i] > a[j]));
       //ensures (size > 1) ==> (\exists integer i,j; 0 <= i < size && 0 <= j < size && i != j);
    complete behaviors;
    disjoint behaviors;
 */
void max_max(int *a, unsigned size, int **max1, int **max2)
{

   if (size > 0) { // <==
      unsigned i; // <== int
      *max1 = &a[0];
      *max2 = *max1;

      /*@ loop invariant 0 < i <= size;
          loop invariant \exists integer j; 0 <= j < i && (a + j) == *max1;
          loop invariant \exists integer j; 0 <= j < i && (a + j) == *max2;
          loop invariant **max1 >= **max2;
          loop invariant \forall integer j; 0 <= j < i ==> a[j] <= **max1;
          loop invariant \exists integer j; 0 <= j < i && a[j] >= **max2 && a[j] == **max1;
          loop invariant ! (\exists integer j,k; 0 <= j < i && 0 <= k < i && j != k && (a[j] > **max2 && a[k] > **max2 && a[k] > a[j]));
          loop assigns *max1, *max2;
          loop variant size - i;
       */
      for(i = 1; i < size; ++i) {
         if (a[i] > **max1) {
            *max2 = *max1; // <==
            *max1 = &a[i];
         } else if (a[i] > **max2) {
            *max2 = &a[i];
         }
      }
   }
}
```
