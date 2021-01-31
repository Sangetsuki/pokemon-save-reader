Um leitor de save de pokémon da 3 geração. Consegue ler algumas informações do jogador, porém não consegue salvar pois não gera os checksums para validar o save.

A maneira que ele funciona não é uma das mais eficazes, ele tem o save num array de bytes e trabalha com a
localização no save, sendo bem dificil de interagir, planejo separar tudo em classes (uma para cada seção).

Para compilar:

```
g++ main.cpp Save.cpp
```

não coloquei makefile ainda

Para funcionar:
```
./a.out (caminho para o save, sem os ())
```

Se for compilar num windows lembre-se de compilar com um .exe eu acho