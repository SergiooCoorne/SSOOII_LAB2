# SSOOII_LAB2

Práctica realizada por:
  José Morán Galán
  Sergio Cornejo Prieto

Modo de compilación y ejecución:
Para compilar y ejecutar la práctica hemos creado un Makefile para simplificarnos la vida, por lo que solamente hay que ubicarse en la carpeta donde se encuentra el Makefile (teniendo los programas en CPP en la carpeta src) y hacer un make. Esto nos creará dos carpetas: la carpeta build con SSOOIIGLE.o y la carpeta bin con el ejecutable. Una vez realizado el make, solo hay que hacer ./bin.

Consideraciones:
Cuando la palabra buscada se encuentra al principio o final de la línea, se pondrá "NULL" en la palabra anterior o posterior. Es decir, si se encuentra al principio de la línea, no tiene palabra anterior, por lo que se pondrá "NULL" "palabra buscada" "palabra posterior". De la misma manera, cuando se encuentra al final, siendo "NULL" la palabra posterior.

Dado que algunos de los nombres de archivos tenían espacios, los hemos juntado debido a que darían error al pasarlos como línea de argumento, ya que al haber espacios se reconocerían como distintos argumentos. Por lo tanto, el programa está hecho para nombres de archivos sin espacios. Proporcionamos los archivos de prueba con los espacios eliminados, pero en caso de querer añadir otro distinto, debe tenerse en cuenta lo que acabamos de mencionar.

Hemos añadido diferentes colores a la hora de imprimir por pantalla, ya que cuando son numerosos hilos y cada hilo trabaja con muchas líneas, es muy complicado diferenciar solo por la lectura qué línea está siendo tratada por qué hilo. Por lo tanto, hemos considerado que para comprender de mejor manera la salida, la manera más efectiva era diferenciarlo por colores.
