1. Organização Inicial

    Objetivo Geral:
        Implementar um minishell funcional, que seja capaz de interpretar comandos básicos, suportar algumas funcionalidades do shell, e lidar com entradas/saídas de forma eficiente.
    Requisitos:
        Verificar quais as funções mínimas obrigatórias (e.g., cd, echo, exit).
        Definir extensões ou funcionalidades extras que queiram implementar (se for um trabalho avaliativo, confirmem as exigências do professor/tutor).

2. Etapas do Projeto

Etapa 1: Estrutura Inicial do Projeto

    Criar os arquivos de código (e.g., main.c, headers, etc.).
    Configurar o ambiente de trabalho (e.g., Makefile para compilar facilmente).
    Decidir quais bibliotecas usar (e.g., unistd.h, signal.h, stdlib.h).

Etapa 2: Comandos Básicos

    Implementar execução de comandos simples usando execve (e.g., ls, pwd).
    Testar a leitura da linha de comando usando readline.

Etapa 3: Comandos Internos (Builtins)

    Implementar comandos internos:
        echo
        cd
        pwd
        export
        unset
        env
        exit.

Etapa 4: Redirecionamentos e Pipes

    Implementar redirecionamentos (>, <, >>, <<).
    Implementar suporte a pipes (|) para encadear comandos.

Etapa 5: Gerenciamento de Processos

    Lidar com processos em foreground e background.
    Implementar captura de sinais (e.g., CTRL+C, CTRL+Z, CTRL+\).

Etapa 6: Testes e Melhorias

    Testar todos os comandos em diversos cenários (e.g., comandos inválidos, múltiplos pipes).
    Tratar erros (mensagens de erro amigáveis para o usuário).

Etapa 7: Documentação

    Criar um README explicando como o minishell funciona, como compilar e usar.

Divisão de Tarefas
Responsável 1 (Tu)

    Leitura e interpretação de comandos:
        Criar a função principal que lê e divide os comandos da linha de entrada (readline e split).
    Comandos Internos (Builtins):
        Implementar echo, pwd e exit.
    Redirecionamentos simples:
        Implementar redirecionamento de saída (> e >>).
    Documentação:
        Criar um README inicial.

Responsável 2 (Colega)

    Execução de comandos externos:
        Implementar o uso de execve para rodar programas externos.
    Comandos Internos (Builtins):
        Implementar cd, export, unset e env.
    Redirecionamentos complexos e pipes:
        Implementar redirecionamento de entrada (< e <<) e suporte a pipes (|).
    Testes e mensagens de erro:
        Criar cenários de teste e tratar erros de execução.

Responsabilidade Compartilhada

    Configurar o Makefile e estruturar os arquivos do projeto.
    Testar e revisar o código.
    Resolver conflitos no código e ajustar detalhes finais.

Cronograma (Sugestão)
Semana	Tarefa	Responsáveis
Semana 1	Configuração inicial (Makefile, estrutura de arquivos)	Ambos
Semana 2	Implementar leitura de comandos e execução básica (execve)	Ambos
Semana 3	Desenvolver comandos internos básicos (e.g., echo, cd)	Tu: echo e pwd
Colega: cd e env
Semana 4	Implementar redirecionamentos e pipes	Tu: Redirecionamento
Colega: Pipes
Semana 5	Tratamento de sinais e testes finais	Ambos
Semana 6	Revisar código, documentar, e entregar	Ambos
