# C-Ray-Tracing
# Proyecto: Simulador Gráfico con SDL2

Este proyecto es un programa escrito en C que utiliza la biblioteca SDL2 para generar gráficos en pantalla. Su objetivo principal es simular el comportamiento de rayos (“rays”) interactuando con círculos en una ventana gráfica. A continuación, se detallan las características principales del proyecto y cómo ejecutarlo.

---

## Características principales

- **Resolución de ventana:** 1200x700 px.
- **Elementos gráficos:**
  - Círculos definidos por su posición (“x”, “y”) y su radio.
  - Rayos definidos por su ángulo, punto de origen y punto de finalización.
- **Colores principales:**
  - Blanco, negro, amarillo y tonos derivados para los rayos y su "desenfoque".
- **Constantes configurables:**
  - Cantidad de rayos: `RAYS_NUMBER`.
  - Grosor de los rayos: `RAY_THICKNESS`.

---

## Dependencias

Este proyecto depende de las siguientes bibliotecas:

1. **SDL2**: Una biblioteca popular para la programación de gráficos y multimedia.
2. **math.h**: Para realizar cálculos matemáticos necesarios (trigonometría).

### Instalación de SDL2 en Linux

```bash
sudo apt-get install libsdl2-dev
```

### Instalación de SDL2 en Windows

1. Descarga SDL2 desde su sitio oficial: [https://libsdl.org/](https://libsdl.org/)
2. Sigue las instrucciones de configuración para tu IDE preferido (por ejemplo, Visual Studio o Code::Blocks).

---

## Cómo compilar y ejecutar

### Compilación
Para compilar el programa, asegúrate de tener un compilador como `gcc` instalado y usa el siguiente comando:

```bash
gcc -o simulador main.c -lSDL2 -lm
```

### Ejecución
Una vez compilado, ejecuta el programa con:

```bash
./simulador
```

---

## Descripción técnica

El programa incluye las siguientes funciones principales:

1. **`FillCircle`**: Rellena un círculo en la superficie proporcionada usando SDL2.
2. **Simulación de rayos:** Los rayos son generados a partir de un punto de origen y se proyectan según ángulos calculados.
3. **Renderizado:** Utiliza SDL2 para dibujar y actualizar los elementos gráficos en pantalla.

---

## Posibles mejoras

1. **Blur:** El codigo para el blur está dentro del codigo pero hay fallos en su implementacion, habría que crear un loop distinto
   para el blur y para los rays, y así no habría separacion entre los rays.

---


