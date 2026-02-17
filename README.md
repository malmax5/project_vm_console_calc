# Console Calculator

Учебный проект консольного калькулятора на C++17.

### Возможности:
1. Числа могут быть только целые
2. Доступные операции: + - * / ^ !

### Сборка
```bash
cmake -B build
cmake --build build
sudo cmake --build build --target install
```
### Использование
```bash
# Для + - * /
calculator --first [num] --second [num] --op [operation]

# Для ^
calculator --first [num] --second [exp] --op ^

# Для !
calculator --first [num] --op !

# Получить информацию
calculator --help
```
