# 👾 Tavola Space

**Tavola Space** é uma recriação do clássico jogo arcade Space Invaders onde o jogador controla uma nave e deve defender a Terra de uma invasão alienígena, tudo em uma interface de texto com arte ASCII. Esta abordagem proporciona uma experiência nostálgica e diferenciada para os fãs de jogos retro.

Neste jogo, você controla uma nave representada pelo caractere 'M', enquanto as naves inimigas também são representadas por caracteres 'M'. Prepare-se para desviar de ataques e eliminar os invasores!

## 📁 Estrutura do Projeto

- **src/**: Código fonte dividido em módulos.
- **assets/**: Armazenamento de pontuações e recursos futuros.
- **include/**: Arquivos de cabeçalho.

## 🎮 Como Jogar

1. **Inicie o jogo**: Execute o programa compilado.
2. **Controle sua nave**: Use as teclas de movimento para mover sua nave para a esquerda e direita.
3. **Atire nos inimigos**: Pressione a tecla designada para disparar projéteis (representados pelo caractere '^') em direção às naves inimigas.
4. **Sobreviva**: Desvie dos ataques inimigos e tente derrotar o maior número possível de naves antes que elas alcancem a base!

### Controles (a definir)
- `A`: Mover para a esquerda
- `D`: Mover para a direita
- `Espaço`: Atirar

## 📋 Instruções de Clonagem, Compilação e Uso

### Pré-requisitos

O jogo funciona apenas em sistemas Linux e MacOS e requer o **GCC** para compilação. Instale o GCC usando os seguintes comandos:

- **Linux (Ubuntu, etc)**:
```bash
sudo apt-get update
sudo apt-get install build-essential
```

- **MacOS**:
```bash
xcode-select --install
```

### 📥 Clonar o Repositório
Para começar, clone o repositório do jogo em sua máquina local usando o seguinte comando:

```bash
git clone https://github.com/usuario/space-invaders.git
cd space-invaders
```

### Compilação e Execução

Para compilar e executar o jogo, simplesmente execute o seguinte comando no terminal do seu projeto:

```bash
mkdir build
make run
```

## 🤝 Desenvolvedores
- João Pedro
- Rafael Serpa
- William Souza
