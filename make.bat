@echo off

:: 1) Compila o programa
echo Compilando...
g++ -o programa -I header source\*.cpp
echo.

:: 2) Lista de instâncias (pastas)
set INSTANCES=   n100w8 n120w8 n080w8
:: n030w4 n040w4 n050w4 n060w4 n080w4 n100w4 n120w4 n030w8 n040w8 n050w8 n060w8


:: 3) Para cada instância, roda 50 vezes
for %%I in (%INSTANCES%) do (
    echo Rodando para a instância %%I...
    for /l %%J in (1,1,10) do (
        echo  - Execução %%J
        :: Se quiser abrir janelas separadas (paralelo), use START sem /wait.
        :: Se quiser rodar uma por vez, use apenas "programa.exe" ou "start /wait".
        start /wait programa.exe %%I %%J
    )
    echo.
)

echo Todas as execuções terminaram!
pause
