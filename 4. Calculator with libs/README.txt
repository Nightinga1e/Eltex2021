Для работы со статическими библиотеками(если библиотека создана, то с  пункта):

1)Создаем объектники:
gcc CalcAdd.c -c
gcc CalcDiv.c -c
gcc CalcMult.c -c
gcc CalcSub.c -c
gcc GetVar.c -c

2) собираем библиотеку:
ar rc libcalcfunc.a CalcAdd.o CalcDiv.o CalcMult.o CalcSub.o GetVar.o

3) Собираем исполняемый файл с указанием библиотеки:
gcc CalcMain.c -o CalcMain -L. -lcalcfunc

4) запускаем:
./CalcMain
======================================

Для работы с динамическими библиотеками(если библиотека собрана, то с 3 пункта):
1) Создаем объектники с позиционно независимым кодом:
gcc CalcAdd.c -c -fPIC
gcc CalcDiv.c -c -fPIC
gcc CalcMult.c -c -fPIC
gcc CalcSub.c -c -fPIC
gcc GetVar.c -c -fPIC

2) Собираем библиотеку:
gcc -shared CalcAdd.o CalcDiv.o CalcMult.o CalcSub.o GetVar.o -o libcalcfunc.so

3) собираем объектник для мэйна:
gcc CalcMain-c -c

4) Собираем исполняемый файл с указанием библиотеки:
gcc CalcMain.o libcalcfunc.so -o CalcMain

5) Запускаем с указанием пути библиотеки:
LD_LIBRARY_PATH=$PWD ./CalcMain