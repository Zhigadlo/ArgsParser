# Аргументы для парсера
 
-h - аргумент без параметров<br/>
-int_value - аргумент для интового значения, можно вводить только один раз<br/>
-b или --bool_value - аргумент для булевского значение, можно вводить один раз<br/>
-s --string_value - аргумент для нескольких строковых значений<br/>

Пример запуска программы через консоль:<br/>
ArgsParser.exe -h --string_value test_word --int_value 123 -s second_string -b true -s third_word<br/>
