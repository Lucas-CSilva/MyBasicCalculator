# MyBasicCalculator

`MyBasicCalculator` é uma calculadora de linha de comando simples, porém poderosa, que suporta as operações aritméticas básicas, atribuição de variáveis e o uso de parênteses para agrupar expressões.

## Funcionalidades

  * **Operações Aritméticas:** Suporta adição (`+`), subtração (`-`), multiplicação (`*`) e divisão (`/`).
  * **Atribuição de Variáveis:** Você pode criar variáveis e atribuir valores a elas usando o operador `:=`. Por exemplo, `x := 2*5`.
  * **Ordem de Operações:** Respeita a ordem matemática padrão das operações (PEMDAS/BODMAS) e permite o uso de parênteses para agrupar expressões.
  * **Comandos de Saída:** Você pode sair da calculadora usando os comandos `quit` ou `exit`.

## Compilação

Para compilar o projeto, certifique-se de ter o `make` e um compilador C (como o GCC) instalados. Depois, basta usar os seguintes comandos:

### Compilar o projeto

Para compilar a calculadora, execute o comando `make` no diretório raiz do projeto. Isso criará o arquivo executável `mybc`.

```bash
make
```

### Limpar os arquivos de compilação

Para remover os arquivos-objeto (`.o`) gerados durante a compilação, use o comando:

```bash
make clean
```

Para uma limpeza mais completa, que remove os arquivos-objeto, arquivos temporários (`*~`) e o executável `mybc`, use:

```bash
make mostlyclean
```

## Como Usar

Após a compilação, você pode executar a calculadora com o seguinte comando:

```bash
./mybc
```

Depois de iniciar, você pode inserir expressões matemáticas. Cada expressão deve ser seguida por um ponto e vírgula (`;`) ou uma nova linha.

### Exemplos de Uso

```
>> 5 + 5
result: 10

>> x := 10
result: 10

>> x * 2
result: 20

>> y := (3 + 2) * 4
result: 20

>> x + y
result: 30

>> quit
```
