*************
Laboratorio 2
*************

* Andrés Arias Campos - B80661
* Erick Sancho Abarca - B77145
* Gabriel Araya Mora - B80525

Diseño de los endpoints
************

Para el presente laboratorio, se utilizo el web framework de FastAPI para construir la REST API que permita la conexion entre el cliente y el eieManager. La API cuenta con los metodos basicos 

Releases:
=========

#. Completar un API que sea funcional y que cumpla con los requerimientos funcionales del mismo. 
#. Completar todos los "managers" y sus funcionalidades. (``Manager``, ``GroupManager``, ``DeviceManager``, ``DatabaseHandler``)
#. Completar la capa de comandos. (``CommandInvoker``, ``CommandRegistry``, ``CommandInfo``) 
#. Completar capa transporte del ``eieManager``. (``TransportClient``, ``RPCClient``)
#. Completar capa transporte del ``eieDevice``. (``TransportServer``, ``Protocol``)
#. Completar la capa de commando. (``CommandManager``, ``Command``)

Requerimientos
**************

Requerimientos Funcionales:
===========================

* ``F-REQ-001`` El sistema debe funcionar como un API (Aplication programming interface) para controlar los dispositivos de forma remota desde el client y hasta los dispositivos asi como devolver respuesta de los mismos al client de ser necesario.
* ``F-REQ-002`` El sistema deberá comunicarse de ida y vuelta con un cliente externo al sistema.
* ``F-REQ-003`` El sistema deberá comunicarse de ida y vuelta con N dispositivos externos al sistema por medio de protocolos (HTTP/HTTPs) todo basado en la metodología RPC
* ``F-REQ-004`` El sistema deberá contar con un set de comandos definidos e indentificables por nombre, así como desplegar un mensaje de error en el client cuando el dispositivo seleccionado no soporta dicho comando.
* ``F-REQ-005`` El sistema debe ser capaz de comunicarse con un dispositivo seleccionado o bien comunicarse con todos los dispositivos al mismo tiempo, usando broadcast.
* ``F-REQ-006`` Cuando se trate de un mensaje de broadcast, el sistema debe captar la respuesta de todos los dispositivos y una vez hecho esto formular una respuesta que devolverle al client.
* ``F-REQ-007`` El sistema deberá validar cada uno de los comandos con el fin de generar una señal de error si fuese necesario.
* ``F-REQ-008`` El sistema será capaz de volver a su estado normal de operación después de un fallo.
* ``F-REQ-009`` El sistema sea capaz de soportar una amplia variedad de comandos, y que además sea sencillo agregar nuevos comandos. 
* ``F-REQ-010`` La aplicación deberá ser capaz de recibir más comandos del client, sin que necesariamente el dispositivo haya devuelto una respuesta. (Funcionamiento similar al de una cola)

Requerimientos No Funcionales:
==============================

* ``NF-REQ-001`` El sistema debe poder ser utilizado por cualquier ambiente de desarrollo externo, es decir cualquier otra plataforma en cualquier lenguaje debe poder hacer uso de la aplicación. 
* ``NF-REQ-002`` El sistema debe soportar cualquier tipo de dispositivo capaz de ejecutar el sistema de ``eieDevice``.
* ``NF-REQ-003`` El sistema debe ser capaz de entender cualquier distribución de linux. (Compatibilidad)
* ``NF-REQ-004`` El sistema debe cumplir con las normas de seguridad informática y no presentar vulnerabilidades. (Seguridad)
* ``NF-REQ-005`` El sistema debe ser lo suficientemente ligero como para no impactar en sobremanera el desempeño del dispositivo que lo está usando. (Desempeño)

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


Para este caso el proceso de aplicar ADD se debe realizar en dos componentes ya establecidos los cuales son **eieManager** y **eieDevice**, esto son tomados del primer boceto elaborado del sistema. 
