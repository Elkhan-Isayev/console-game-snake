# 🐍 Console Snake

A tiny, dependency-free **Snake** game that runs right in your terminal.
Written in C++ and fully **cross-platform** — works on **macOS**, **Linux**, and **Windows**.

```
########################
#                      #
#                      #
#          F           #
#                      #
#       ooO            #
#                      #
#                      #
#                      #
#                      #
########################
SCORE: 30
Controls: W/A/S/D to move, X to quit
```

---

## 🎮 Gameplay

| Symbol | Meaning      |
|:------:|--------------|
| `O`    | Snake head   |
| `o`    | Snake body   |
| `F`    | Fruit        |
| `#`    | Wall         |

- Eat the **fruit** (`F`) to grow longer and earn **+10** points.
- The game ends if you hit a **wall** or run into **your own tail**.

### Controls

| Key | Action      |
|:---:|-------------|
| `W` | Move up     |
| `A` | Move left   |
| `S` | Move down   |
| `D` | Move right  |
| `X` | Quit        |

---

## 🚀 Running on macOS (via VS Code)

You don't need anything beyond what ships with macOS — the Xcode Command Line
Tools provide the `clang++` compiler.

### 1. Install the compiler (one time)

```bash
xcode-select --install
```

### 2. Open the project in VS Code

```bash
git clone https://github.com/<your-username>/console-game-snake.git
cd console-game-snake
code .
```

> 💡 Install the **C/C++** extension from Microsoft if VS Code prompts you.

### 3. Build & run

This repo ships with a ready-made VS Code task, so you can:

- Press **⌘ + Shift + B** to build, **or**
- Open the Command Palette (**⌘ + Shift + P**) → **Tasks: Run Task** → **run snake**.

The game opens in the integrated terminal. Enjoy! 🎉

---

## 🛠 Running from the terminal (any platform)

If you'd rather skip VS Code, just use the included `Makefile`:

```bash
make run       # build and play
make           # build only -> game-snake/game-snake
make clean     # remove the built binary
```

Or compile by hand:

```bash
# macOS / Linux
clang++ -std=c++17 -Wall -o game-snake/game-snake game-snake/game-snake.cpp
./game-snake/game-snake
```

```powershell
# Windows (Developer PowerShell / MSVC)
cl /EHsc game-snake\game-snake.cpp
.\game-snake.exe
```

> A prebuilt Windows binary is also available in the [`Run/`](Run) folder
> (`game-snake.exe`) if you just want to play on Windows.

---

## 🤝 Contributing

Contributions are welcome! Feel free to open an issue or a pull request.
Thank you for considering contributing to the project. 🙌
