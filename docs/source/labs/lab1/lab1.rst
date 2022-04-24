*************
Laboratorio 1
*************

* Andrés Arias Campos - B80661
* Erick Sancho Abarca - B77145
* Gabriel Araya Mora - B80525

Planeamiento
==================

Requerimientos
==================

Requerimientos Funcionales:
---------------------------

#. El sistema debe funcionar como una especie de API para controlar los dispositivos de forma remota desde el client y hasta los dispositivos asi como devolver respuesta de los mismos al client de ser necesario.
#. El sistema deberá comunicarse de ida y vuelta con un cliente externo al sistema por medio de protocolos (TCP/UDP/MQTT entre otros) todo basado en RPC
#. El sistema deberá comunicarse de ida y vuelta con N dispositivos externos al sistema por medio de protocolos (TCP/UDP/MQTT entre otros) todo basado en RPC
#. El sistema deberá contar con un set de comandos definidos e indentificables por nombre, así como desplegar un mensaje de error en el client cuando el dispositivo seleccionado no soporta dicho comando.
#. El sistema debe ser capaz de comunicarse con un dispositivo seleccionado o bien comunicarse con todos los dispositivos al mismo tiempo por medio de broadcast.
#. Cuando se trate de un mensaje de broadcast, el sistema debe captar la respuesta de todos los dispositivos y una vez hecho esto formular una respuesta que darle al client.
#. El sistema deberá validar cada uno de los comandos con el fin de generar una señal de error si fuese necesario.
#. .El sistema será capaz de volver a su estado normal de operación después de un fallo de cualquier tipo.

Requerimientos de desempeño:
-----------------------------

#. El sistema debe ser capaz de soportar N clientes controlando dispositivos.
#. El sistema debe ser capaz de soportar N dispositivos por cliente con el menor impacto rendimiento posible.
#. La aplicación deberá ser capaz de recibir más comandos del client, sin que necesariamente el dispositivo haya devuelto una respuesta. (Multi hilo)

Requerimientos del sistema:
---------------------------

#. El sistema debe poder ser utilizado por cualquier ambiente de desarrollo externo, es decir cualquier otra plataforma en cualquier lenguaje debe poder hacer uso de la aplicación.
#. El sistema debe soportar cualquier tipo de dispositivo sin importar fabricante y características.
#. El sistema debe ser capaz de generar alta variedad de comandos de forma sencilla y rápida.
#. El sistema debe ser capaz de entender cualquier distribución de linux.

ADD
==================

Patrones de diseño
==================


Diagramas UML
==================


