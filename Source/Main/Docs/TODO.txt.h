TODO:

29-Ago-2009

- Pasar el sistema de colisiones a sistema de colisiones con callbacks.
- Poner callbacks para cuando se toca un segmento...
- Marcar los segmentos con flags, para diferenciarlos de cuando es un segmento delimitador de circuito,
de cuando es un segmento gu�a del circuito.
- Los callbacks de colisi�n devuelven el coche que ha inflingido la colisi�n, el segmento, y el punto 
del coche que ha sufrido la colisi�n.
Pueden ocurrir 2 colisiones durante el mismo frame? por ejemplo, un punto cruza una guia pero a la vez 
colisiona con otra guia? Dificil pero posible. Peor es el caso en que el coche colisiona con 2 guias
delimitadoras.

18-Ago-2009

- Sombras por encima de los coches. 
Creamos una m�scara de grises que se aplica de la siguiente manera:
pintamos circuito.
pintamos coches,
pintamos m�scara con cierto grado de alfa.

El efecto conseguido es de como si los coches tuvieran proyectada la sombra que hay sobre el circuito.
Probablemente haya que eliminar de alguna manera la sombra que ya hay sobre el circuito en si.


- Overlay de elementos del circuito.
Se trata de aislar las partes m�viles de las est�ticas del circuito.
Pintamos parte est�tica (escenario)
pintamos coches
(pintamos sombreado circuito)
pintamos parte overlay.

El efecto conseguido es el de que los coches pueden pasar por debajo de objetos de la vida real, plantas etc...
Se puede obtener a partir de un video por ejemplo, con las utilidades realizadas hasta el momento, o tb se puede 
hacer con 2 fotos: una del circuito en si, y otra a�adiendo elementos que ser�n el overlay. Si no se mueve la c�mara,
se puede hacer una imagen diferencial para obtener qu� parte es overlay y cual no (m�scara).
