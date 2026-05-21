# 🐚 Minishell

> A minimal Unix shell implemented in C — inspired by **bash**, built from scratch as part of the **42 School** curriculum.

![Language](https://img.shields.io/badge/language-C-blue?style=flat-square)
![School](https://img.shields.io/badge/school-42-black?style=flat-square)
![Norm](https://img.shields.io/badge/norminette-compliant-brightgreen?style=flat-square)

---

## 📖 About

**Minishell** is a fully functional command-line interpreter written in C. It replicates core behaviours of the **bash** shell, including command parsing, pipelines, redirections, environment variable expansion, quoting rules, and signal handling — all implemented without relying on any external shell library beyond `readline`.

This project was developed as part of the **42 School** cursus and targets a deep understanding of how Unix processes, file descriptors, and inter-process communication work under the hood.

---

## ✨ Features

### 🔧 Built-in Commands

| Command | Description |
|---|---|
| `echo` | Print arguments to stdout, with `-n` flag support |
| `cd` | Change the current working directory |
| `pwd` | Print the current working directory |
| `env` | Display the current environment variables |
| `export` | Set or display environment variables |
| `unset` | Remove environment variables |
| `exit` | Exit the shell with an optional status code |

### 🔀 Pipelines & Redirections

- **Pipes** (`|`) — chain multiple commands, passing stdout of one to stdin of the next
- **Input redirection** (`<`) — read stdin from a file
- **Output redirection** (`>`) — write stdout to a file (truncate)
- **Append redirection** (`>>`) — append stdout to a file
- **Heredoc** (`<<`) — read input until a delimiter is reached

### 💬 Quoting & Expansion

- **Single quotes** (`'...'`) — preserve literal value of every character
- **Double quotes** (`"..."`) — allow `$VAR` expansion inside
- **`$VAR` expansion** — replace environment variable references with their values
- **`$?` expansion** — expand to the exit status of the last executed command

### ⚙️ Other

- **Interactive prompt** using GNU `readline` (with command history)
- **Signal handling** — `Ctrl+C`, `Ctrl+D`, `Ctrl+\` behave like in bash
- **Syntax tree** — commands are parsed into an AST before execution
- **Memory management** — no leaks (readline suppression included via `.readline.supp`)

---

## 🗂️ Project Structure

```
Minishell/
├── includes/           # Header files
├── src/
│   ├── main.c          # Entry point
│   ├── builtins/       # Built-in command implementations
│   │   ├── ft_echo.c
│   │   ├── ft_cd.c
│   │   ├── ft_env.c
│   │   ├── ft_exit.c
│   │   ├── ft_pwd.c
│   │   ├── ft_unset.c
│   │   ├── ft_export/  # export logic (split across multiple files)
│   │   └── ft_pipe/    # Pipe execution logic
│   ├── parse/          # Lexing, parsing, quoting, expansion, AST
│   │   ├── expander/   # $VAR and $? expansion
│   │   ├── init/       # Shell initialisation
│   │   └── tree/       # Syntax tree construction
│   ├── processes/      # Fork/exec and process management
│   ├── redirections/   # Heredoc and I/O redirections
│   ├── signals/        # Signal handlers
│   ├── splits/         # Custom split / quote-aware tokeniser
│   └── utils/          # General utilities, FD management, free
├── libraries/
│   └── libft/          # Custom C library (libft)
├── Makefile
└── .readline.supp      # Valgrind suppression for readline
```

---

## 🚀 Getting Started

### Prerequisites

- GCC or Clang
- GNU `readline` library (`libreadline-dev` on Debian/Ubuntu)
- GNU `make`

```bash
# Ubuntu / Debian
sudo apt install libreadline-dev

# macOS (with Homebrew)
brew install readline
```

### Build

```bash
git clone https://github.com/1Fr3aK2/Minishell.git
cd Minishell
make
```

This compiles the project and produces the `minishell` executable.

### Run

```bash
./minishell
```

You will be greeted with an interactive prompt. Type any command just as you would in bash.

---

## 🧹 Makefile Targets

| Target | Description |
|---|---|
| `make` / `make all` | Build the project |
| `make clean` | Remove object files |
| `make fclean` | Remove object files and the executable |
| `make re` | Full rebuild (`fclean` + `all`) |
| `make v` | Run with `valgrind` (full leak check) |

---

## 🧪 Testing with Valgrind

A `.readline.supp` suppression file is included to silence known readline-internal leaks:

```bash
make v
```

This runs:
```bash
valgrind --leak-check=full --track-fds=yes --show-leak-kinds=all \
         --track-origins=yes --show-reachable=yes \
         --suppressions=.readline.supp ./minishell
```

---

## 👥 Authors

- **[1Fr3aK2](https://github.com/1Fr3aK2)** & **[dsteiger42](https://github.com/dsteiger42)**

---

## 📄 License

This project was developed for educational purposes at **42 School**. No explicit license has been applied — please refer to the school's academic integrity policy before reusing any code.

---

> *"As beautiful as the simplest shell prompt."*
