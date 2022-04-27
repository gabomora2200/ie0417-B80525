*************
Laboratorio 1
*************

* Andrés Arias Campos - B80661
* Erick Sancho Abarca - B77145
* Gabriel Araya Mora - B80525

Planeamiento
************

Requerimientos
**************

Requerimientos Funcionales:
===========================

#. El sistema debe funcionar como una especie de API para controlar los dispositivos de forma remota desde el client y hasta los dispositivos asi como devolver respuesta de los mismos al client de ser necesario.
#. El sistema deberá comunicarse de ida y vuelta con un cliente externo al sistema por medio de protocolos (TCP/UDP/MQTT entre otros) todo basado en RPC
#. El sistema deberá comunicarse de ida y vuelta con N dispositivos externos al sistema por medio de protocolos (TCP/UDP/MQTT entre otros) todo basado en RPC
#. El sistema deberá contar con un set de comandos definidos e indentificables por nombre, así como desplegar un mensaje de error en el client cuando el dispositivo seleccionado no soporta dicho comando.
#. El sistema debe ser capaz de comunicarse con un dispositivo seleccionado o bien comunicarse con todos los dispositivos al mismo tiempo por medio de broadcast.
#. Cuando se trate de un mensaje de broadcast, el sistema debe captar la respuesta de todos los dispositivos y una vez hecho esto formular una respuesta que darle al client.
#. El sistema deberá validar cada uno de los comandos con el fin de generar una señal de error si fuese necesario.
#. .El sistema será capaz de volver a su estado normal de operación después de un fallo de cualquier tipo.

Requerimientos de desempeño:
============================

#. El sistema debe ser capaz de soportar N clientes controlando dispositivos.
#. El sistema debe ser capaz de soportar N dispositivos por cliente con el menor impacto rendimiento posible.
#. La aplicación deberá ser capaz de recibir más comandos del client, sin que necesariamente el dispositivo haya devuelto una respuesta. (Multi hilo)

Requerimientos del sistema:
===========================

#. El sistema debe poder ser utilizado por cualquier ambiente de desarrollo externo, es decir cualquier otra plataforma en cualquier lenguaje debe poder hacer uso de la aplicación.
#. El sistema debe soportar cualquier tipo de dispositivo sin importar fabricante y características.
#. El sistema debe ser capaz de generar alta variedad de comandos de forma sencilla y rápida.
#. El sistema debe ser capaz de entender cualquier distribución de linux.

Attribute-Driven Design (ADD)
*****************************


En esta sección se realiza el análisis del problema empleando ADD. Para ello se discutirá empleando la secuencia de pasos dispuesto en el paper Attribute-Driven Design (ADD),
Version 2.0. Los pasos descritos en el paper anterior son los siguientes:

#. Confirm There Is Sufficient Requirements Information.
#. Choose an Element of the System to Decompose.
#. Identify Candidate Architectural Drivers.
#. Choose a Design Concept That Satisfies the Architectural Drivers.
#. Instantiate Architectural Elements and Allocate Responsibilities.
#. Define Interfaces for Instantiated Elements.
#. Verify and Refine Requirements and Make Them Constraints for Instantiated Elements.
#. Repeat steps 2 through 7 for the Next Element of the System You Wish to Decompose


Para este caso el proceso de aplicar ADD se debe realizar en dos compoenntes ya establecidos los cuales son **eieManager** y **eieDevice**, esto son tomados del primer boceto elaborado del sistema. 

**Paso 1.** Confirm There Is Sufficient Requirements Information.

El primer paso es el de verificar que se cuente con los requerimientos suficientes para el desarrollo del análisis. Este paso es igual para ambos bloques por analizar, esto se deriva del análisis realizado en la parte anterior. Por lo tanto ya se cuenta con los requerimientos suficientes para poder emplear ADD.


**Paso 2.** Choose an Element of the System to Decompose.

En este caso se debe seleccionar un elemento del sistema para descomponer, debido a que le sistema se componen de dos elementos principales llamandos en los bocetos iniciales como **eieManager** y **eieDevice**. Primero se realiza el análisis a partir del paso 2 de la metodología de ADD. Comenzando por el módulo de **eieManager**.

**eieManager**
==============


**Paso 3:** Identify Candidate Architectural Drivers.
En este paso se identifican y categorizan los requerimientos del elemento. En este caso el `eieManager` este es el componente principal del sistema ya que debe coordinar las comunicaciones con el cliente y con los `eieDevice`, además gestionar los mensajes broadcast a los dispositivos y sus respuestas, generar las respuestas a los comandos del cliente, entre otros. Por lo tanto podemos clasificar requerimientos según lo descrito por los stakeholders y según cómo puede afectar la arquitectura.


+---------------------------------------------------------------------------+--------+--------+
| Requerimientos                                                            | SH     | Arch   |
+===========================================================================+========+========+
|| Que el API pueda ser fácilmente consumido por otro equipo de desarrollo  | Alta   | Baja   |
|| para implementar un cliente en un App móvil con GUI. No se puede asumir  |        |        |
|| que este cliente va a utilizar algún lenguaje en específico.             |        |        |
+---------------------------------------------------------------------------+--------+--------+
|| Soportar dispositivos heterogéneos, de distintos fabricantes y/o         | Alta   |  Alta  |
|| características. Nuevos dispositivos deben ser sencillos de agregar y    |        |        |
|| esto no debe implicar cambios en el API. Además, ciertos dispositivos y  |        |        |
|| casos de uso podrían requerir nuevos protocolos de comunicación.         |        |        |
+---------------------------------------------------------------------------+--------+--------+
|| Que el sistema sea capaz de generar una amplia variedad de comandos.     |  Alta  |  Media |
|| Nuevos comandos deben ser sencillos de agregar y esto no debe implicar   |        |        |
|| cambios en el API.                                                       |        |        |
+---------------------------------------------------------------------------+--------+--------+
|| Que el sistema tenga un rendimiento y escalabilidad adecuada al operar   |  Media |  Alta  |
|| con los dispositivos, tal que se soporte el envío de comandos a          |        |        |
|| múltiples dispositivos simultáneamente en los casos de `broadcast`.      |        |        |
+---------------------------------------------------------------------------+--------+--------+
|| Que el sistema tenga alta disponibilidad, siendo capaz de volver a su    |  Media |  Alta  |
|| operación normal luego de un fallo que genere un cierre del proceso de   |        |        |
|| ``eieManager``, recuperando su estado original.                          |        |        |
+---------------------------------------------------------------------------+--------+--------+

.. note::
   Donde `SH` significa StakeHolder, y `Arch` significa Arquitectura.


En el prinmer caso se selecciona una prioridad **Baja** de Arquitectura debido que existen multiples protocolos que son compatibles con todos o casi todos los lenguajes, entre los que podemos mecionar TCP, UDP, entre otros. Otro motivo es que mayoritariamente las API funcionan por serialización de datos empleando métodos como JSON. Debido a esto es que no tiene baja relevancia en la arquitectura que se implemente dentro del **eieManager**. 

En el segundo caso se selecciona una prioridad de **Alta** en la arquitectura, esto debido a que el **eieManager** sea compatible con multiples dispositivos, sin importar el protocolo de comunicación, es muy importante e impacta directamente en la arquitectura del elemento y del sistema. Ya que a diferencia del punto anterior, la conexion con los dispositivos, la comunicación con los dispositivos puede cambiar entre muchos de ellos. En este caso se puede pensar en las implicaciones que puede tener, dar soporte a diferentes protocolos, sin poder cambiar las funcionalidades de la API. 

En el tercer requerimiento, se define una prioridad **Media** en la arquitectura, esto debido a que la arquitectura debe tener la capacidad de generalizar los comandos para poder tener una configuración que permita una integracion sencilla de nuevos comandos. Sin embargo el impacto en la arquitectura no es demasiado alta ya que los comandos al ser generalizados, tienen alta facilidad de integración.

En el cuarto requerimiento, se define una prioridad **Alta** en la arquitectura. La escalanbilidad es un requerimiento importante que impacta la arquitectura del sistema, ya que esta ligada con el rendimiento del sistema. Por lo que una mala arquitectura de software afectaría el rendimiento del sistema.

En el quinto requerimiento, se define una prioridad **Alta** en la arquitectura, debido que la disponibilidad, aún cuando se den problemas en el `eiemanager`, impacta en gran manera la forma en la que se determina la arquitectura, ya que este tipo de funcionalidad requiere de algún patrón de diseño, lo cual afecta la arquitecctura directamente.



**Paso 4:** Choose a Design Concept That Satisfies the Architectural Drivers.

En este paso se realiza el planteamiento de conceptos de diseño a partir de los objetivos planteados y de los requerimientos de funcionalidad del elemento ``eieManager``.




**eieDevice**
=============

**Paso 3:** Identify Candidate Architectural Drivers.

En este caso identifican y categorizan los requerimientos que aplican al módulo `eieDevice`, el cual recibe los comandos desde el `eieManager`, los procesa y genera el resultado, que posteriormente devuelve al `eieManager`. Por lo tanto podemos clasificar requerimientos según lo descrito por los stakeholders y según cómo puede afectar la arquitectura.

+----------------------------------------------------------------------+-------+-------+
| Requerimientos                                                       | SH    | Arch  |
+======================================================================+=======+=======+
|| El dispositivo debe poder procesar múltiples comandos, aunque estos | Alta  | Alto  |
|| lleguen sin haber generado la respuesta del comando previo.         |       |       |
|| Manteniendo una cola de comandos.                                   |       |       |
+----------------------------------------------------------------------+-------+-------+
|| El Dispositivo debe ser capaz de soportar cualquier distribución de | Alta  | Bajo  |
|| Linux.                                                              |       |       |
+----------------------------------------------------------------------+-------+-------+
|| Soportar diferentes protocolos de comunicación que dependen del     | Media | Medio |
|| dispositivo en el cual se esta ejecutando el `eiedevice`.           |       |       |
+----------------------------------------------------------------------+-------+-------+

En el primer requerimiento se define un impacto `Alto`, esto se debe a que la funcionalidad mencionada requiere una arquitectura dirigida a dicho problema de diseño. Ya que podemos decir que se requiere algún nivel de concurrencia, además de emplear colas, y otros mecanismos para evitar la pérdidad de comandos en situaciones de alta demanda de solicitudes de ejecución.

En el segundo caso se determina un impacto `Bajo`, esto es porque la compatibilidad con un sistema operativo no depende de la arquitectura, si no del lenguaje en que se implemente el código.

En el tercer caso, se determino un impacto `Medio`, esto es porque la compatibilidad con diferentes protocolos de comunicación, es una funcionalidad de una pequeña parte del sistema, la cual únicamente se encarga de las comunicaciones, esto lo podemos definir como una abstracción del bloque de comunicaciones.


**Paso 4:** Choose a Design Concept That Satisfies the Architectural Drivers.

En este caso se plantean los conceptos de diseño que satisfacen los requerimientos planteados, para el elemento. El ``eieDevice`` es el software que se encuentra dentro de cada dispositivo controlado por el ``eieManager``, esto es de gran importancia, ya que le software no es distinto para cada dispositivo, sino que este debe ser compatible con cada uno de ellos. 



Ahora podemos plantear los problemas de diseño, encontrados para este sistema.
#. Procesar comandos de control y de ejecución.
#. Debe tener la capacidad de recibir múltiples comandos sin aún haber procesado los comandos recibidos anteriormente. 
#. Debe soportar multiples protocolos de comunicación.

A partir de los problemas de diseño planteados podemos determinar ciertos patrones de diseño que pueden solucionar estos problemas de diseño.

#. Para el primer caso





Patrones de diseño
******************


Diagramas UML
*************


