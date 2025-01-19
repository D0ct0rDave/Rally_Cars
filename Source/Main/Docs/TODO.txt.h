TODO:

29-Ago-2009

- Pasar el sistema de colisiones a sistema de colisiones con callbacks.
- Poner callbacks para cuando se toca un segmento...
- Marcar los segmentos con flags, para diferenciarlos de cuando es un segmento delimitador de circuito,
de cuando es un segmento guía del circuito.
- Los callbacks de colisión devuelven el coche que ha inflingido la colisión, el segmento, y el punto 
del coche que ha sufrido la colisión.
Pueden ocurrir 2 colisiones durante el mismo frame? por ejemplo, un punto cruza una guia pero a la vez 
colisiona con otra guia? Dificil pero posible. Peor es el caso en que el coche colisiona con 2 guias
delimitadoras.

18-Ago-2009

- Sombras por encima de los coches. 
Creamos una máscara de grises que se aplica de la siguiente manera:
pintamos circuito.
pintamos coches,
pintamos máscara con cierto grado de alfa.

El efecto conseguido es de como si los coches tuvieran proyectada la sombra que hay sobre el circuito.
Probablemente haya que eliminar de alguna manera la sombra que ya hay sobre el circuito en si.


- Overlay de elementos del circuito.
Se trata de aislar las partes móviles de las estáticas del circuito.
Pintamos parte estática (escenario)
pintamos coches
(pintamos sombreado circuito)
pintamos parte overlay.

El efecto conseguido es el de que los coches pueden pasar por debajo de objetos de la vida real, plantas etc...
Se puede obtener a partir de un video por ejemplo, con las utilidades realizadas hasta el momento, o tb se puede 
hacer con 2 fotos: una del circuito en si, y otra añadiendo elementos que serán el overlay. Si no se mueve la cámara,
se puede hacer una imagen diferencial para obtener qué parte es overlay y cual no (máscara).
