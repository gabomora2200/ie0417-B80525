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

1.El sistema debe funcionar como una especie de API para controlar los dispositivos de forma remota desde el client y hasta los dispositivos asi como devolver respuesta de los mismos al client de ser necesario.

2.El sistema deberá comunicarse de ida y vuelta con un cliente externo al sistema por medio de protocolos (TCP/UDP/MQTT entre otros) todo basado en RPC

3.El sistema deberá comunicarse de ida y vuelta con N dispositivos externos al sistema por medio de protocolos (TCP/UDP/MQTT entre otros) todo basado en RPC

4.El sistema deberá contar con un set de comandos definidos e indentificables por nombre, así como desplegar un mensaje de error en el client cuando el dispositivo seleccionado no soporta dicho comando. 

5.El sistema debe ser capaz de comunicarse con un dispositivo seleccionado o bien comunicarse con todos los dispositivos al mismo tiempo por medio de broadcast. 

6.Cuando se trate de un mensaje de broadcast, el sistema debe captar la respuesta de todos los dispositivos y una vez hecho esto formular una respuesta que darle al client.

7.El sistema deberá validar cada uno de los comandos con el fin de generar una señal de error si fuese necesario.

8.El sistema será capaz de volver a su estado normal de operación después de un fallo de cualquier tipo. 


Requerimientos de desempeño:
-----------------------------

1.El sistema debe ser capaz de soportar N clientes controlando dispositivos. 

2.El sistema debe ser capaz de soportar N dispositivos por cliente con el menor impacto rendimiento posible. 

3.La aplicación deberá ser capaz de recibir más comandos del client, sin que necesariamente el dispositivo haya devuelto una respuesta. (Multi hilo)


Requerimientos del sistema:
---------------------------

1.El sistema debe poder ser utilizado por cualquier ambiente de desarrollo externo, es decir cualquier otra plataforma en cualquier lenguaje debe poder hacer uso de la aplicación.

2.El sistema debe soportar cualquier tipo de dispositivo sin importar fabricante y características.

3.El sistema debe ser capaz de generar alta variedad de comandos de forma sencilla y rápida. 

4.El sistema debe ser capaz de entender cualquier distribución de linux.

ADD
==================

Patrones de diseño
==================


Diagramas UML
==================


