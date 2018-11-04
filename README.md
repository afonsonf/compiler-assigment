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