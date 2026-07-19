# SistemaDeGestion-proyectoFInal
 ============================================================================
  TERMINAL PORTUARIO TURISTICO DE BUENAVENTURA
  ----------------------------------------------------------------------------
  Gestion de destinos (FIFO dinamica), pasajeros por destino (FIFO dinamica)
  y viajes programados por destino (ABB - Arbol Binario de Busqueda).
 
 Estructuras utilizadas:
    - FIFO de Destinos: lista enlazada con apuntadores frente/final.
    - Cada Destino contiene su propia FIFO de Pasajeros (enlazada).
    - Cada Destino contiene su propio ABB de Viajes Programados
    (ordenado por codigo de viaje).

Todo el manejo de memoria es dinamico (malloc/free) mediante apuntadores,
 sin arreglos fijos. El sistema soporta N destinos, N pasajeros por destino
y N viajes programados por destino.
 

