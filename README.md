# Аргументы для парсера
 
-h - аргумент без параметров
-int_value - аргумент для интового значения, можно вводить только один раз
-b или --bool_value - аргумент для булевского значение, можно вводить один раз
-s --string_value - аргумент для нескольких строковых значений

Пример запуска программы через консоль:
ArgsParser.exe -h --string_value test_word --int_value -s second_string -b true -s third_word
