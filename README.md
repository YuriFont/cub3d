<div align="center">

# cub3D

### A real-time raycasting engine written from scratch in C

*Inspired by the legendary Wolfenstein 3D — built as part of the [42 School](https://42.fr) curriculum.*

![Language](https://img.shields.io/badge/Language-C-00599C?style=flat-square&logo=c)
![Graphics](https://img.shields.io/badge/Graphics-MiniLibX-FF6F00?style=flat-square)
![Platform](https://img.shields.io/badge/Platform-Linux-FCC624?style=flat-square&logo=linux&logoColor=black)
![Norm](https://img.shields.io/badge/42-Norminette-000?style=flat-square)

</div>

---

## English

### Overview

**cub3D** is a from-scratch 3D game engine that renders a textured, navigable world from a 2D map using **raycasting** — the same technique that powered *Wolfenstein 3D* (1992). The entire pipeline, from parsing the scene description to drawing each vertical wall slice pixel-by-pixel, is implemented in pure C with no game engine, no OpenGL, and only a minimal X11 wrapper (MiniLibX) for putting pixels on screen.

The challenge isn't just to make it work — it's to make it work **fast**, **safely** (no leaks, no segfaults, on any malformed input), and within the strict coding standards of 42.

### Highlights

- **DDA raycasting algorithm** — efficient grid traversal that casts one ray per screen column to determine wall distance, side, and texture coordinates.
- **Textured rendering** — four directional wall textures (North / South / East / West), per-pixel sampling, perspective-correct vertical stretching, and shaded floors/ceilings via RGB triples.
- **Animated walls** — supports a 10-frame texture cycle for living, breathing environments.
- **Robust `.cub` parser** — validates file extension, texture paths, RGB ranges, map closure, character set, and player spawn before a single pixel is drawn.
- **Real-time controls** — smooth WASD movement, arrow-key camera rotation, collision detection, and clean ESC / window-close shutdown with zero memory leaks.
- **Zero external dependencies** beyond MiniLibX + a custom `libft` (the project's own re-implementation of the C standard library).

### Tech Stack

| Layer | Choice |
|---|---|
| Language | **C** (ISO C99, `-Wall -Wextra -Werror`) |
| Graphics | **MiniLibX** (X11 wrapper) |
| Math | `<math.h>` — vectors, trig, DDA |
| Build | GNU Make |
| Standard lib | Custom `libft` (re-implemented from scratch) |

### Project Structure

```
cub3d/
├── inc/                  Header file (data structures, prototypes)
├── src/
│   ├── main.c            Entry point + event hooks
│   ├── validation/       .cub file & map validation
│   ├── fill_struct/      Parsing → in-memory scene
│   ├── window/           MLX window init
│   ├── create_vision/    Raycasting + rendering pipeline
│   ├── movement/         Keyboard input + player physics
│   └── loop_game.c       Per-frame game loop
├── libs/
│   ├── libft/            Custom C standard library
│   └── minilibx-linux/   Graphics library
├── assets/               XPM textures (walls, animations)
└── maps/                 Sample .cub scenes
```

### Build & Run

```bash
make                       # Compile (builds libft + MiniLibX + cub3D)
./cub3D maps/mini.cub      # Launch with a sample map
```

**Controls:** `W` `A` `S` `D` to move · `←` `→` to rotate · `ESC` to quit.

### What I Learned

Implementing a raycaster forces you to be fluent in **linear algebra** (camera planes, ray directions, perspective projection), **performance-aware C** (every pixel costs cycles in the inner loop), **manual memory management** (every `malloc` paired with a freed exit path), and **defensive parsing** (a map file is hostile until proven safe). The result is the kind of project where every shortcut shows up immediately on screen — as a tear, a leak, or a crash — which makes it a uniquely honest teacher.

---

## Português

### Visão Geral

**cub3D** é um motor 3D construído do zero que renderiza um mundo texturizado e navegável a partir de um mapa 2D usando **raycasting** — a mesma técnica que deu vida ao *Wolfenstein 3D* (1992). Todo o pipeline, do parsing da cena à pintura de cada fatia vertical de parede pixel a pixel, é escrito em C puro, sem game engine, sem OpenGL, e usando apenas um wrapper minimalista do X11 (MiniLibX) para colocar pixels na tela.

O desafio não é só fazer funcionar — é fazer funcionar **rápido**, **com segurança** (sem leaks, sem segfaults, em qualquer entrada malformada), e dentro do padrão rígido de código da 42.

### Destaques

- **Algoritmo DDA de raycasting** — varredura eficiente da grid lançando um raio por coluna da tela para determinar distância, lado e coordenadas de textura.
- **Renderização com texturas** — quatro texturas direcionais (Norte / Sul / Leste / Oeste), amostragem por pixel, esticamento vertical com correção de perspectiva e piso/teto coloridos via RGB.
- **Paredes animadas** — suporte a ciclo de 10 frames para ambientes vivos.
- **Parser `.cub` robusto** — valida extensão do arquivo, caminhos das texturas, faixa RGB, fechamento do mapa, conjunto de caracteres e spawn do jogador antes de desenhar um único pixel.
- **Controles em tempo real** — movimento suave WASD, rotação por setas, detecção de colisão e encerramento limpo (ESC ou fechar janela) sem nenhum vazamento de memória.
- **Zero dependências externas** além da MiniLibX + uma `libft` própria (reimplementação da biblioteca padrão de C feita por mim).

### Stack Técnica

| Camada | Escolha |
|---|---|
| Linguagem | **C** (ISO C99, `-Wall -Wextra -Werror`) |
| Gráficos | **MiniLibX** (wrapper de X11) |
| Matemática | `<math.h>` — vetores, trigonometria, DDA |
| Build | GNU Make |
| Lib padrão | `libft` própria (reimplementada do zero) |

### Estrutura do Projeto

```
cub3d/
├── inc/                  Header (estruturas e protótipos)
├── src/
│   ├── main.c            Entrada e hooks de eventos
│   ├── validation/       Validação do .cub e do mapa
│   ├── fill_struct/      Parsing → cena em memória
│   ├── window/           Inicialização da janela MLX
│   ├── create_vision/    Pipeline de raycasting e renderização
│   ├── movement/         Entrada de teclado e física do jogador
│   └── loop_game.c       Loop de frame
├── libs/
│   ├── libft/            Biblioteca C própria
│   └── minilibx-linux/   Biblioteca gráfica
├── assets/               Texturas XPM (paredes, animações)
└── maps/                 Mapas .cub de exemplo
```

### Build e Execução

```bash
make                       # Compila (libft + MiniLibX + cub3D)
./cub3D maps/mini.cub      # Roda com um mapa de exemplo
```

**Controles:** `W` `A` `S` `D` para mover · `←` `→` para girar · `ESC` para sair.

### O Que Aprendi

Implementar um raycaster exige fluência em **álgebra linear** (planos de câmera, direções de raio, projeção em perspectiva), **C consciente de performance** (cada pixel custa ciclos no loop interno), **gerenciamento manual de memória** (todo `malloc` com um caminho de liberação garantido) e **parsing defensivo** (um arquivo de mapa é hostil até prova em contrário). É o tipo de projeto onde qualquer atalho aparece imediatamente na tela — como tearing, leak ou crash — o que o torna um professor singularmente honesto.

---

<div align="center">

### Authors · Autores

Built by **[@yufonten](https://github.com/yufonten)** & **[@erramos](https://github.com/erickramosxp)** at 42 Rio.

</div>
