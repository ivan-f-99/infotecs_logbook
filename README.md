# infotecs_logbook
Тестовое задание для конкурса на стажера "C++ разработчик"

Программа и библиотека собраны GNU Make 4.3 под операционной системой Ubuntu 24.04.1 LTS.
Тесты выполнены в виде bash-скриптов.

В библиотеке описан класс, позволяющий записывать сообщения с разным уровнем важности в журнал.
Для последующего использования в нескольких потоках созданы специальные интерфейсы.
В том числе очередь сообщений и флаги завершения работы с журналом.

В приложении описаны несколько функций осуществляющих взаимодействие с журналом.
Эти функции запускаются в отдельных потоках, которые работают параллельно с использованием 
функционала предусмотренного в библиотеке функционала.
Приложение запускается несколькими способами:
1. С передачей опций - имя журнала и важность по умолчанию
2. Без передачи опций ( тогда приложение попросит пользователя ввести данные с консоли)
Посмотреть очередность опций для вызова можно по команде "./testapp.exe -help"

