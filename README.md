# MISP_project

# Cómo ejecutar `results_MISP.sh`

Para realizar la ejecución del programa se utiliza el archivo "results_MISP.sh".\
Este script está escrito en **Bash** y funciona en **dos modalidades**:\
con permisos de ejecución (`chmod +x`) o sin ellos (`bash results_MISP.sh`).\
En ambos casos el **contenido del script es el mismo**.

---

## 1. Con permisos de ejecución

En este caso se aprovecha el **shebang** (`#!/usr/bin/env bash`)
incluido en la primera línea del script.

### Pasos:

```bash
chmod +x results_MISP.sh     # se otorgan permisos de ejecución
./results_MISP.sh            # se ejecuta directamente
```

- El sistema detecta el shebang.
- Llama automáticamente a `bash` para ejecutar el archivo.
- Es la forma más cómoda si planeas distribuir el script y quieres que
  se ejecute con `./results_MISP.sh`.

---

## 2. Sin permisos de ejecución

Aquí no es necesario usar `chmod`. En vez de eso, se llama a `bash`
explícitamente.

### Pasos:

```bash
bash results_MISP.sh
```

- El shebang **no se usa** en este caso (pero no molesta que esté).
- Es útil en entornos donde no puedes (o no quieres) usar `chmod`.
