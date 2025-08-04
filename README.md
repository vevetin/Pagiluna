# Pagiluna

## Sobre o Projeto

**Pagiluna** é um sistema simples de gerenciamento de livros desenvolvido em linguagem C. O projeto foi pensado como aplicação prática de conceitos de Estrutura de Dados I, e permite:

- Inserir livros com informações como título, autor, gênero e ano;
- Buscar livros por título;
- Editar ou excluir livros existentes;
- Visualizar todo o catálogo em ordem crescente pela chave (ID).

## Pré-requisitos

- Compilador C compatível com o padrão **C99** (como `gcc` ou `clang`);
- **make** instalado para facilitar a compilação (opcional, mas recomendado);

## Passo 1: Clonar o Repositório

```bash
git clone https://github.com/vevetin/Pagiluna.git
cd Pagiluna
```

## Passo 2: Compilar o Projeto

Utilize o `Makefile` incluso:

```bash
make
```

Makefile irá criar um executável com nome `pagiluna.exe` (no Windows) ou `pagiluna` (no Linux/macOS)

## Passo 3: Executar o Projeto

```bash 
make run
```

Ou, alternativamente:

```bash 
./pagiluna   # Linux
pagiluna.exe # Windows
```

## Próximos Passos

- Validação robusta de entradas do usuário;

- Persistência em arquivos (salvar e carregar catálogo);

- Testes automatizados e cobertura de código.

- Desenvolvimento de uma interface gráfica para interação com o usuário.