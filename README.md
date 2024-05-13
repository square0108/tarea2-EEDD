## Entregable 2: Tablas Hash

<b style="color: #ff5733">Todo lo siguiente es del enunciado de la </b> [tarea](https://udec.instructure.com/courses/50234/assignments/474620)

En este entregable compararemos el rendimiento de diferentes tablas hash sobre el dominio de usuarios de X (ex Twitter). Para la comparación utilizaremos el dataset universities_followers.zip
Download universities_followers.zip, el cual consiste de 21.070 usuarios de X que son seguidores de la cuenta oficial de alguna universidad chilena en la red social. A continuación, se muestra un extracto del dataset:
![image](https://github.com/square0108/tarea2-EEDD/assets/78096857/1b709125-09aa-4db1-a492-263e6dca3261)
Por cada usuario se entregan los campos:

  - **University:** Universidad a la que sigue el usuario en la red social.
  - **User ID:** Número identificador del usuario en Twitter. Este campo es único.
  - **User Name:** Nombre de usuario en Twitter. Este campo es único.
  - **Number Tweets:** Número de tweets publicados por el usuario.
  - **Friends Count:** Número de cuentas que el usuario sigue en la red social.
  - **Followers Count:** Número de seguidores que tiene el usuario en la red social.
  - **Created At:** Fecha en la que el usuario creó su cuenta en la red social.

Se solicita almacenar la información del dataset utilizando diferentes tablas hash. Para ello, se deben considerar dos claves: User ID y User Name. En otras palabras, se pide diseñar e implementar estructuras de datos que utilicen User ID como clave, y un grupo similar que utilice User Name como clave. El valor asociado a cada clave será un struct o clase con toda la información de una fila del dataset.

Las estructuras de datos mínimas a considerar son:

  - Implementación propia (o del laboratorio) de tabla hash con hashing abierto (encadenamiento)
  - Implementación propia (o del laboratorio) de tabla hash con hashing cerrado. Para este caso se piden evaluar las estrategia para manejo de colisiones linear probing, quadratic probing y double hashing.
  - La implementación de unordered map de la STL de C++

Sobre las funciones hash a usar, queda a criterio de los estudiantes las funciones hash que usarán. Nótese que necesitarán al menos dos funciones hash: una para User ID y otra para User Name. En el caso de double hashing necesitarán una segunda función hash para ambos casos.

## Informe

En esta ocasión se pide que entreguen un pequeño informe reportando un estudio experimental de las estructuras (no más allá de 8 páginas) con las siguientes secciones:

  - **Introducción** [máximo 1 página]:
    - Breve reseña de todo el trabajo realizado. Descripción a alto nivel del problema planteado y estructuras de datos utilizadas (implementadas y provistas por bibliotecas), herramientas, fuentes de datos y conclusiones preliminares.
  
  - **Descripción de las estructuras de datos comparadas** [máximo 1 página]:
    - Entrega de todos los códigos como adjuntos al documento o enlaces a dónde encontrarlos en el mismo. El código debe estar documentado y seguir algún estándar de codificación adoptado por el estudiante.
    - Para cada estructura de datos, entregar una descripción general, indicar los costos de inserción, eliminación y búsqueda, y especificar los parámetros utilizados (función hash, número inicial de buckets, etc). Se debe destinar, como máximo, un párrafo por cada estructura de datos descrita. En dicho párrafo se pueden incluir links a sitios web y otras referencias bibliográficas.
  
  - **Descripción del dataset y del ambiente de experimentación** [máximo 1 página]: Describir los métodos de lectura del dataset. Si fuese necesario realizar alguna modificación al dataset, específicar las modificaciones de manera justificada. Además, describir en detalle la máquina en la que se realizaron los experimentos (modelo del procesador, tamaño de la memoria RAM, tamaño de las memorias caché, etc).
  
  - **Resultados experimentales** [máximo 4 páginas]: Comparar el rendimiento de las estructuras de datos  usando evidencia experimental. Como mínimo, se pide entregar gráficas y/o tablas con las siguientes comparaciones
    - Tamaño de las estructuras de datos, expresadas en B, KB o MB.
    - Rendimiendo en la creación de la estructura de datos. Por cada estructura de datos, medir experimentalmente su escalabilidad en función de la cantidad de usuarios almacenados en la estructura. Por ejemplo, medir el tiempo que toma insertar los primeros 1.000, 5.000, 10.000, 15.000 y 20.000 usuarios.
    - Comparar el rendimiento de las estructura de datos para realizar búsquedas. Para ello, se solicita realizar dos tipos de experimentos. En el primer tipo, se pide medir el tiempo promedio de ejecutar varias búsquedas de usuarios que están almacenados. Para el segundo tipo de experimentos, se pide medir el tiempo de consultar por usuarios que NO están almacenados en las estructuras de datos.
    - Cada medición experimental debe ser realizada utilizando las claves User ID y User Name. Se pide mostrar evidencia experimental de la clave más eficiente para cada estructura de datos.
  
  - **Conclusiones** [máximo 1 página]: Describir los principales descubrimientos obtenidos. Hacer hincapié en las estructuras de datos más rápidas para cada tipo de experimento y en la comparación de los dos tipos de claves evaluadas.

## Recomendaciones para realizar un estudio experimental

Para obtener resultados confiables en un estudio experimental, como el solicitado en este entregable, deben considerar lo siguiente

  - Todos los experimentos se deben realizar en el mismo computador. Al momento de medir tiempo de ejecución sólo deben estar abierto los programas estrictamente necesadios. Otros programas, como navegadores Web, editores de texto, etc, deben estar cerrados.
  - Cada experimento se debe repetir varias veces. Idealmente repetirlo 20 veces y reportar luego su promedio y desviación estándar (nota: una desviación estándar muy alta hace que el promedio sea poco confiable)
  - Es recomendable que dejen todo preparado para ejecutar todos los experimentos de una sola vez. Por ejemplo, pueden dejar ejecutándose experimentos en horas en las que no usen mucho el computador que usarán para medir tiempos (ej. de noche)
  - Para su posterior análisis de resultados, es recomendable que su programa genere un archivo CSV. Esto se logra imprimiendo por cada experimento una línea como la siguiente
      ``número_experimento;dataset;estructura_de_datos;cantidad_consultas;tiempo_ejecucion``
    De esa manera, todos los experimentos se verán como un archivo CSV con valores separados por ';', en el cual es más sencillo obtener estadísticas como el promedio usando hojas de cálculo o lenguajes como Python.
