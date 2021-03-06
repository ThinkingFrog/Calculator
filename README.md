# Модульный калькулятор

Ограничение на платформу - используются методы из *WIN32 API*

Все классы операций должны наследоваться от одного из базовых классов *BinaryOperation, PrefixOperation, PostfixOperation*

Каждый модуль должен иметь загрузчик вида:

**extern "C" BaseOperation* LoadOperation() { return new my_op; }**

Входное выражение должно чётко разделять каждую операцию и число пробелами, например:

**( 2 + 2 ) * 2**

**cos 60 - 6 ! + 7 ^ 4 * 78 - 8 / 4**

**0.5 - 2 * -7 + 2 / 3 / ( 2 * 4 + 3 ) / 4 * 11 / 12**

Разработано и протестировано на *gcc для mingw32 9.2.0* и *msvc 2019*

В коде указывается относительный путь до директории плагинов, для MinGW это **../plugins**, для msvc **../../plugins**

**Файлы библиотек в директории plugins должны быть собраны тем же компилятором, что и проект.**

**Сейчас они собраны под 64-битной версией msvc 2019**

**Все операции считаются левоассоцитаивными**
