# Console Calculator

Учебный проект консольного калькулятора на C++17.

### Возможности:
1. Числа могут быть только целые
2. Доступные операции: sum sub mul div pow fact

### Сборка
```bash
cmake -B build
cmake --build build
sudo cmake --build build --target install
```
### Использование
```bash
calculator '{"operation": "[operation]", "operands": [operands]}'
```
