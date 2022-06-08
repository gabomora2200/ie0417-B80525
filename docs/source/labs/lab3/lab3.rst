*************
Laboratorio 3
*************

* Andrés Arias Campos - B80661
* Erick Sancho Abarca - B77145
* Gabriel Araya Mora - B80525


eieDevice:
==========

El eieDevice es un servidor cuyo objetivo principal es ejecutar comandos de un dispositivo. Para cumplir lo anterior, se implementa el servidor utilizando la librería ``ZMQ``. 

Además se decidió utilizar una arquitectura de tipo RPC, con el fin de enviar las solicitudes de los comandos desde el cliente.

Cada instancia de ``eieDevice`` puede ser vista como un pequeño programa que corre en un servidor de ``ZMQ`` y el mismo responde a las solicitudes enviadas por el cliente. 

Con el fin de empaquetar los datos del servidor se utiliza la norma ``JSON`` y para ello la librería para C, ``CJSON``.


Commandos:
==========

* ``Message``: Comando el cual devuelve un mensaje arbitrario y no recibe argumentos.   

* ``Status``: Commando encargado de informar el estado actual del dispositivo en cuestión.

* ``PingPong``: Commando que retorna todos los argumentos de entrada. 




