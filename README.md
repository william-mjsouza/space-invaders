# Space Invaders em C

## Apresentação

**Space Invaders em C** é uma recriação do clássico jogo arcade onde o jogador controla uma nave e deve defender a Terra de uma invasão alienígena. O jogo é apresentado em uma interface de texto utilizando caracteres ASCII, proporcionando uma experiência nostálgica para os fãs de jogos retro.

Neste jogo, você controla uma nave representada pelo caractere 'M', enquanto as naves inimigas são representadas por caracteres 'M' também. Prepare-se para desviar de ataques e eliminar os invasores!

## Estrutura do Projeto

- **src/**: Código fonte dividido em módulos.
- **assets/**: Armazenamento de pontuações e recursos futuros.
- **include/**: Arquivos de cabeçalho.
- **tests/**: Testes unitários (planejados).

## Como Jogar

1. **Inicie o jogo**: Execute o programa compilado.
2. **Controle sua nave**: Use as teclas de movimento para mover sua nave para a esquerda e direita.
3. **Atire nos inimigos**: Pressione a tecla designada para disparar projéteis (representados pelo caractere '^') em direção às naves inimigas.
4. **Sobreviva**: Desvie dos ataques inimigos e tente derrotar o maior número possível de naves antes que elas alcancem a base!

### Controles (a definir)
- `A` ou `←`: Mover para a esquerda
- `D` ou `→`: Mover para a direita
- `Espaço`: Atirar

## Instruções de Compilação e Uso

### Pré-requisitos

Certifique-se de ter o GCC instalado em seu sistema. Você pode instalá-lo usando o seguinte comando:

```bash
sudo apt-get update
sudo apt-get install build-essential
```

### Compilação

Para compilar o jogo, execute o seguinte comando no diretório do seu projeto:

```bash
gcc main.c ./cli-lib/src/*.c -I./cli-lib/include -o space-invaders
```


### Execução

Após a compilação bem-sucedida, execute o jogo com o comando:

```bash
./space-invaders
```
