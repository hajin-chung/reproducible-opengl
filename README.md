# trying out opengl

learning about opengl in a reproducable fashion

compiled in mingw gcc


## build

1. without cmd

```cmd
gcc main.c glad.c libglfw3.a -lopengl32 -lgdi32 -mwindows
```

2. with cmd

```cmd
gcc main.c glad.c libglfw3.a -lopengl32 -lgdi32
```
