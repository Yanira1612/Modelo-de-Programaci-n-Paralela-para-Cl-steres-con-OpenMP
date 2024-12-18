# Modelo-de-Programaci-n-Paralela-para-Cl-steres-con-OpenMP

# Ejemplos de OMPC

Este repositorio contiene ejemplos de programas OMPC.

## Imagen del Contenedor

La forma más sencilla de usar OMPC es descargando una imagen de Docker desde DockerHub. La imagen contiene el compilador y todas las bibliotecas necesarias para comenzar. Cada semana, un trabajo automatizado de CI crea y despliega una nueva imagen `latest` con la versión más reciente del runtime de OMPC.

Para descargar la imagen, ejecuta el siguiente comando:

```bash
$ docker pull ompcluster/runtime:latest
```

Después de descargar la imagen, navega al directorio de tu proyecto e inicia un contenedor desde la imagen utilizando:

```bash
$ docker run -it --rm -v $PWD:/root ompcluster/runtime:latest bash
```

Para asegurarte de que el contenedor funciona correctamente, ejecuta el siguiente comando dentro del contenedor:

```bash
$ clang --version
```

El resultado debería verse similar a esto:

```
OmpCluster clang version 14.0.0 (git@gitlab.com:ompcluster/llvm-project.git 4f60767e575b6f97c269f5a3e66cc1d508d23d32)
Target: x86_64-unknown-linux-gnu
Thread model: posix
InstalledDir: /scratch/llvm/build-debug/bin
```

## Compilar y Ejecutar Programas

El runtime de OMPC está construido sobre la interfaz `libomptarget` de OpenMP de LLVM. Los desarrolladores necesitan la versión personalizada de `clang` de OMPC para compilar programas.

### Para Programas en C
Para compilar programas en C, utiliza el siguiente comando:

```bash
$ clang -fopenmp -fopenmp-targets=x86_64-pc-linux-gnu program.c -o program
```

### Para Programas en C++
Para compilar programas en C++, utiliza:

```bash
$ clang++ -fopenmp -fopenmp-targets=x86_64-pc-linux-gnu program.cpp -o program
```

### Ejecutar el Programa
Después de compilar, el programa puede ejecutarse utilizando la utilidad `mpirun` de MPI. Pasa el número de procesos como argumento, y también puedes usar flags adicionales de `mpirun` (por ejemplo, `--hostfile`).

```bash
$ mpirun -np 3 ./program
```

