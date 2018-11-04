# Trabalho de Compiladores

## Execução
Execute os seguintes comandos na raiz do diretorio:
```
$ make
./intrepeter < <inputfile>
```

## Descrição do programa
O programa escreve a arvore sintatica de um programa de um subconjunto da linguagem C.

O programa deve conter uma unica função: int main(){...}

Dentro dessa função são aceites os seguintes comandos:

* Declarações de variáveis do tipo int (com ou sem atribuição) seguidas de um ;

```cpp
    exemplo:
        int a = 2;
    output:
        attrib
          int
            a

            2
```

* Atribuições a uma variavel 

```cpp
    exemplo:
        a = a + 2;
    output:
        attrib
          a

          +
            a
            2
```

* Comando de controlo if e else. Deve ser da forma if(cond) cmd, ou if(cond){cmd} ou if(cond){cmd} else cmd. Não é aceite if(cond) cmd else cmd para evitar o conflito "Dangling else"

```cpp
    exemplo:
        if(1==2) a = a+3;
    output:
        if
          ==
            1
            2

          attrib
            a
                
            +
              a
              3

    exemplo 2:
        if(a==a%2){
            a = a+3;

        }
    output 2:
        if
          ==
            a
            %
              a
              3

          attrib
            a
                
            +
              a
              3
```

* Comando for da forma for(attrib;boolexpr;attrib) cmd

```cpp
    exemplo:
        for(int i = 0; i<4; i = i+2)
            a = a+3;
    output:
        For
          attrib
            int
            i

            0

          <
            i
            4

          attrib
            i

            +
              i
              2

          attrib
            a

            +
              a
              3

```

* Comando while 

```cpp
    exemplo:
        while(1)
            a = a+3;
    output:
        while
          1

          attrib
            a

            +
              a
              3

```

* Comando printf

```cpp
    exemplo:
        printf("aaa",b,c);
    output:
        printf
          "aaa"

          b
          c

```

* Comando scanf

```cpp
    exemplo:
        scanf("aaa",&b,&c);
    output:
        scanf
          "aaa"

          &b
          &c

```

Numa lista de comandos os comandos estão separados por "---".

No inicio do output tem o inicio da função.

<br>

Trabalho feito por:

|Nome |Numero |
|---|---|
|Afonso das Neves Fernandes|201606852|
|Guilherme Paiva Guia | 201603049 |
