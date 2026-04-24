# CPPGraph

Generic undirected graph implemented in C++ for a university project

## Build Options

### Build Project

```
make
```

### Run Tests

```
make test
```

### Clean

```
make clean
```

## Create Specification PDF

1. Install `pandoc` and `typst`
2. `cd docs`

```zsh
pandoc specification.md \
  --from=markdown \
  --to=typst \
  --pdf-engine=typst \
  --include-in-header=./pandoc/template.typ \
  --output=specification.pdf
```

> [!TIP] Optional: Install fonts
>
> 1. Vollkorn
> 2. Lato
> 3. FiraCode Nerd Font Mono
