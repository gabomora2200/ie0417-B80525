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

**Paso 1.** Confirm There Is Sufficient Requirements Information.

El primer paso es el de verificar que se cuente con los requerimientos suficientes para el desarrollo del análisis. Este paso es igual para ambos bloques por analizar, esto se deriva del análisis realizado en la parte anterior. Por lo tanto ya se cuenta con los requerimientos suficientes para poder emplear ADD.


**Paso 2.** Choose an Element of the System to Decompose.

En este caso se debe seleccionar un elemento del sistema para descomponer, debido a que el sistema se compone de dos elementos principales llamados en los bocetos iniciales como **eieManager** y **eieDevice**. Primero se realiza el análisis a partir del paso 2 de la metodología de ADD. Comenzando por el módulo de **eieManager**.

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
|| Que el sistema sea capaz de soportar una amplia variedad de comandos.    |  Alta  |  Media |
|| Nuevos comandos deben ser sencillos de agregar.                          |        |        |
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


En el primer caso se selecciona una prioridad **Baja** de Arquitectura debido a que existen múltiples protocolos que son compatibles con todos o casi todos los lenguajes, entre los que podemos mencionar TCP, UDP, entre otros. Otro motivo es que mayoritariamente las API funcionan por serialización de datos empleando métodos como JSON. Debido a esto es que no tiene baja relevancia en la arquitectura que se implemente dentro del **eieManager**. 

En el segundo caso se selecciona una prioridad de **Alta** en la arquitectura, esto debido a que el **eieManager** sea compatible con múltiples dispositivos, sin importar el protocolo de comunicación, es muy importante e impacta directamente en la arquitectura del elemento y del sistema. Ya que a diferencia del punto anterior, la conexión con los dispositivos, la comunicación con los dispositivos puede cambiar entre muchos de ellos. En este caso se puede pensar en las implicaciones que puede tener, dar soporte a diferentes protocolos, sin poder cambiar las funcionalidades de la API. 

En el tercer requerimiento, se define una prioridad **Media** en la arquitectura, esto debido a que la arquitectura debe tener la capacidad de generalizar los comandos para poder tener una configuración que permita una integración sencilla de nuevos comandos. Sin embargo el impacto en la arquitectura no es demasiado alto ya que los comandos al ser generalizados, tienen alta facilidad de integración.

En el cuarto requerimiento, se define una prioridad **Alta** en la arquitectura. La escalabilidad es un requerimiento importante que impacta la arquitectura del sistema, ya que está ligada con el rendimiento del sistema. Por lo que una mala arquitectura de software afectaría el rendimiento del sistema.

En el quinto requerimiento, se define una prioridad **Alta** en la arquitectura, debido a que la disponibilidad, aún cuando se den problemas en el `eiemanager`, impacta en gran manera la forma en la que se determina la arquitectura, ya que este tipo de funcionalidad requiere de algún patrón de diseño, lo cual afecta directamente la arquitectura.



**Paso 4:** Choose a Design Concept That Satisfies the Architectural Drivers.

En este paso se realiza el planteamiento de conceptos de diseño a partir de los objetivos planteados y de los requerimientos de funcionalidad del elemento ``eieManager``. Para ello se analizan los requerimientos del sistema, para cada uno se plantean posibles soluciones que puedan cumplir con dicho requerimiento.

* La API debe ser sencilla de usar, y no debe tener cambios cuando se agregan nuevos comandos, y/o dispositivos. Para ello se debe definir un método sencillo de comandos los cuales se deben permitir indicar el comando que se desea usar, así como el o los dispositivos en donde se requiere ejecutar el comando. Además de la lista de argumentos necesaria para el comando. Entonces los comandos necesarios de implementar en el API son: ejecutar comando, listar dispositivos, listar comandos con sus respectivos dispositivos habilitados. Y un comando de estatus del sistema. Las respuestas de cada comando debe tener una estructura definida. por ejemplo para ejecutar un comando, la respuesta es un diccionario con el id del dispositivo como llave y el contenido es el resultado del comando. Este formato permite devolver la respuesta de múltiples dispositivos en una sola respuesta. En el caso de los demás comandos estos deben contener listas de resultados con el mismo formato, en el caso de cada comando. Por último en el caso del comando de status este se debe parecer a un comando de PING el cual notifica el estado del ``eieManager``.

Entonces para este se plantea un bloque llamado ``APIServer`` el cual se debe encargar de brindar el servicio del API a los clientes. Cada comando que ingresa lo convierte en un formato entendible para el sistema. Este formato (paquete) se basa en un bloque el cual define la estructura de un comando, el cual se implementa en un bloque llamado ``CommandInfo``. En este se definen las características principales del comando, como lista de argumentos, dispositivo objetivo, y id del comando. En el caso de un comando de tipo *Broadcast*, el contenido del dispositivo objetivo se representa como una lista, donde cada elemento es un dispositivo destino.

* Transportar los comandos desde la API hasta el o los dispositivos, esto se puede solucionar empleando el patrón de diseño de tipo cadena de responsabilidades, este patrón de diseño propone una arquitectura de tipo árbol, donde cada nodo se define como un handler que opera sobre el request hasta que este alcance su destino (``eieDevice``). 

Entonces empleando el patrón de diseño cadena de responsabilidades, podemos definir dos ramas principales, estas son comandos de tipo broadcast (o también multicast) y de tipo unicast. Por lo tanto se requiere un primer handler que identifica cual de las dos ramas debe tomar el request. Este bloque se denomina ``Manager``, es el primer nodo del árbol de ejecución del ``eieManager``. A partir de este bloque se define dos ramas la primera es un bloque que controle los sistemas cuando se ejecuta un comando de tipo broadcast, el cual se denomina ``GroupManager``. El segundo es un bloque que implementa la lógica de control para administrar el ciclo de vida de cada dispositivo, este es el ``DeviceManager``.

* Soportar dispositivos heterogéneos, para ello se implementa un ``DeviceManager``, este bloque se encarga de administrar el ciclo de vida de los dispositivos disponibles, entre sus funciones está la de generar una lista de los dispositivos, donde se registra los estados de cada uno, por ejemplo cuando entra un comando a un dispositivo este almacena el estado de este comando en el dispositivo. 

En este caso el ``DeviceManager`` emplea un módulo base llamado ``Device``, este módulo implementa los datos de control, los cuales el ``DeviceManager``, usa para gestionar el ciclo de vida de cada dispositivo.

* Se requiere que el sistema sea capaz de ejecutar múltiples comandos, además de poder agregar nuevos comandos de forma sencilla, sin implicar cambios importantes en el mismo. esto se resuelve empleando el patrón de diseño **command**, sin embargo, en este caso la ejecución del mismo se realiza de forma remota, ya que la ejecución se ejecutará en el ``eieDevice``. 

Para poder cumplir con este requisito se emplea un ``CommandInvoker``, el cual se encarga de controlar la ejecución de los comandos en el dispositivo destino, para ello hace uso de otro bloque llamado ``Transportclient``, este es el encargado de enviar el request al dispositivo. Estos bloques son los últimos de la cadena de responsabilidades. Estos son controlados por el ``DeviceManager``.

* Para poder establecer conexión con múltiples dispositivos, se puede emplear el patrón de diseño Proxy, sin embargo, algunos dispositivos pueden requieren protocolos de comunicación por lo tanto se puede emplear el patrón de diseño Adapter, el cual proporciona los métodos de conversión de las información en el protocolo específico para cada uno de los dispositivos. Entonces para este caso se define una solución que mezcla las propiedades del patrón de diseño Proxy con las propiedades del patrón de diseño de tipo Adapter. Esto se implementa dentro del módulo llamado ``Transportclient``. De este módulo se derivan otro módulo como el RPCClient el cual implementa la interfaz de conexión entre el **eieManager** y el **eieDevice**. 


* Para poder recuperar el sistema luego de una caída del ``eieManager``, se establece un módulo ``DatabaseHandler``, el cual se encarga de controlar la base de datos empleada en módulos como por ejemplo el ``DeviceManager``, o el ``GroupManager``, ya que a partir de estos datos lo módulos son capaces de regresar al estado antes de la falla en el sistema. Además es importante considerar las configuraciones iniciales del sistema, como por ejemplo los comandos soportados y los dispositivos disponibles. 

**Paso 5:** Instantiate Architectural Elements and Allocate Responsibilities

* ``APIserver``: Este es el bloque en el cual se implementa el API, este tiene dos funciones: escuchar comandos que ingresan y enviar respuestas de los comandos al cliente específico. Por lo tanto se puede separar dos funciones principales, la primera es la poder recibir requests desde los clientes, etiquetando cada uno de ellos con el id del cliente que envía el request, esto con el objetivo de poder responder con el resultado de la operación solicitada. La segunda función es la de convertir el comando de ingreso en el paquete que el sistema puede procesar.
* ``CommandInfo``: Este es un bloque que define la estructura básica del comando de entrada, en este se definen los campos requeridos por el sistema.
* ``CommandRegistry``: Este es una memoria, la cual funciona como un registro de los comandos válidos por cada dispositivo, El funcionamiento se basa en el id de cada dispositivo y el id de cada comando, entonces en un diccionario se registra como llave el id de cada dispositivo y el contenido es una lista con los id de los comandos soportados. Además implementa los métodos requeridos para registrar nuevos comandos soportados por cada dispositivo así como el registro de nuevos dispositivos.
* ``DeviceManager``: Este módulo se encarga del control de los devices, establece tablas de comandos pendientes para cada dispositivo, llevando el control de cada uno. Además es el encargado de implementar los mecanismos de control como por ejemplo los timeouts, los cuales definen el tiempo máximo que el ``DeviceManager``, puede esperar una respuesta del dispositivo. 
* ``GroupManager``: Este bloque implementa la lógica de control de los mensajes de tipo Broadcast, en este se implementa la tabla de control de los comandos recibidos, además se encarga de unir todas las respuestas de los los dispositivos, en una sola respuesta para ser enviada al ``APIServer`` para devolverse al client. 
* ``CommandInvoker``: En este módulo se implementa la lógica de verificación del comando, con lo cual se verifica que el dispositivo soporte el comando solicitado. Además se encarga de iniciar la transmisión con el dispositivo. 
* ``TransportClient``: En este módulo se implementa el proxy de comunicaciones, encargado de determinar el tipo de protocolo que aplica dependiendo del dispositivo destino. Además ejecuta el cliente que es el que se conecta al dispositivo. 
* ``RPCClient``: En este módulo se implementa el protocolo de comunicación.
* ``DatabaseHandler``: este bloque es el encargado de implementar los métodos necesarios para que los demás módulos tengan acceso a la base de datos, además de implementar los métodos de control en caso se produzcan errores en el eieManager. De igual forma gestiona los datos de inicialización del sistema.
* ``Device``: Este es un módulo implementa la estructura necesaria para el cada device, con ello poder gestionar el ciclo de vida del mismo.
* ``Group``: Esta es una estructura base la cual implementa las características básicas de un grupo de broadcast. Es empleado por el ``GroupManager`` para el control de los comandos enviados de forma de mensaje broadcast.




**Paso 6:** Define Interfaces for Instantiated Elements.

El flujo de información entre los módulos se realiza empleando el concepto de paquetes, donde cada paquete contiene la información necesaria para cada módulo destino, por ejemplo, del ``APIServer`` sale un paquete con la información enviada desde el cliente, esta es tomada por el ``Manager`` y clasificada para ser enviada por alguna de las ramas definidas. Así también se envía un paquete desde el DeviceManager hasta el ``TransportClient`` para ser enviado al dispositivo, en este último paquete únicamente se especifica un solo dispositivo. 

Otro punto importante a mencionar es el sistema de etiquetado el cual debe ser capaz de identificar cada request, comando y dispositivo involucrado en el sistema, ya que de eso depende la eficacia del sistema. En términos sencillos el eieManager debe comportarse como un servidor y como un router el cual recibe los request desde un cliente, y la vez transporta los resultados desde los dispositivos hasta el cliente.

**Paso 7:** Verify and Refine Requirements and Make Them Constraints for Instantiated Elements.


Al analizar los pasos anteriores podemos verificar el cumplimiento de los requerimientos, con la unica observacion que la definición de protocolo para este contexto no se especifica del todo, ya que de protocolos de comunicaciones existen múltiples como por ejemplo TCP, UDP, entre otros, sin embargo no se especifica si el protocolo se refiere a estos mencionados, o a formatos de serialización de datos.





**eieDevice**
=============

**Paso 3:** Identify Candidate Architectural Drivers.

En este caso se identifican y categorizan los requerimientos que aplican al módulo `eieDevice`, el cual recibe los comandos desde el `eieManager`, los procesa y genera el resultado, que posteriormente devuelve al `eieManager`. Por lo tanto podemos clasificar requerimientos según lo descrito por los stakeholders y según cómo puede afectar la arquitectura.

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
|| dispositivo en el cual se está ejecutando el `eiedevice`.           |       |       |
+----------------------------------------------------------------------+-------+-------+
|| Nuevos comandos deben ser sencillos de agregar.                     | Alta  | Alta  |
+----------------------------------------------------------------------+-------+-------+

En el primer requerimiento se define un impacto `Alto`, esto se debe a que la funcionalidad mencionada requiere una arquitectura dirigida a dicho problema de diseño. Ya que podemos decir que se requiere algún nivel de concurrencia, además de emplear colas, y otros mecanismos para evitar la pérdida de comandos en situaciones de alta demanda de solicitudes de ejecución.

En el segundo caso se determina un impacto `Bajo`, esto es porque la compatibilidad con un sistema operativo no depende de la arquitectura, si no del lenguaje en que se implemente el código.

En el tercer caso, se determinó un impacto `Medio`, esto es porque la compatibilidad con diferentes protocolos de comunicación, es una funcionalidad de una pequeña parte del sistema, la cual únicamente se encarga de las comunicaciones, esto lo podemos definir como una abstracción del bloque de comunicaciones.

En el último requerimiento se define un impacto `Alto`, debido a que cada comando es al final un método, entonces el poder integrar un método nuevo sin mucha dificultad tiene un gran impacto en la arquitectura del sistema.

Analizando estos requerimientos podemos plantear el siguiente atributos de calidad:

* Modificable: Esto se deriva de la necesidad de tener facilidad de incluir nuevas funcionalidades posteriormente. Esto debido a la necesidad de soportar diferentes protocolos en la capa de transporte.



**Paso 4:** Choose a Design Concept That Satisfies the Architectural Drivers.

En este caso se plantean los conceptos de diseño que satisfacen los requerimientos planteados, para el elemento. El ``eieDevice`` es el software que se encuentra dentro de cada dispositivo controlado por el ``eieManager``, esto es de gran importancia, ya que el software no es distinto para cada dispositivo, sino que este debe ser compatible con cada uno de ellos. Entonces analizamos los principales requerimientos del elemento:



* El primer requerimiento del sistema es la necesidad de ejecutar comandos de estado y/o comandos de ejecución. Este requerimiento deriva en el problema de cómo se puede recibir un comando de un agente externo, y ejecutarlo localmente, para posteriormente devolver el resultado que este genere. Al analizar estos requerimientos, podemos plantear el patrón de diseño **Comando**. Este patrón de diseño se puede emplear cuando se tiene que ejecutar comandos que pueden provenir, tanto localmente, como desde el exterior. Además este presenta la ventaja de poder agregar nuevos comandos de forma sencilla, ya que se basa en el uso de la herencia de una clase base, que puede ser una clase **comando**. Además que se pueden definir colas de ejecución, por lo tanto si entran más comandos de los que se pueden ejecutar estos entran en una cola y eventualmente se ejecutarán.


A partir del análisis anterior se definen dos bloques, el primero es el bloque **Comand**, este bloque implementa las funcionalidades de comando, como puede ser la interfaz de la cual se derivan de los comandos, ademas de implementar la funcionalidad de los comandos. El segundo bloque es el **ComandManager**, en este bloque se implementa el registro de los comandos soportados por el sistema, además es donde se coordina la ejecución de los mismos. Entre las funciones principales está la de tomar la entrada del TansportServer y registrarla en la cola de comandos. 



* El siguiente requerimiento es la capacidad de poder soportar diferentes protocolos de comunicación. Para este caso se puede emplear un patrón de diseño como el Template (o plantilla). Este patrón de diseño propone una estructura base o esqueleto, el cual se pueden sobreescribir los métodos, con lo cual se obtiene una funcionalidad diferente, sin alterar su estructura básica. Este tipo de funcionalidades se pueden ejemplificar como herencia de clases y polimorfismo. Otro posible patrón de diseño que aplica a este caso es el de estrategia, el cual propone una estructura base que ofrece servicios, los cuales dependen de quién solicite estos servicios. Entonces cual es el patrón que más se adapta para este caso:


  * **Template**: Ese patrón permite añadir funcionalidades derivadas del mismo esqueleto `Protocolo`. Además es fácil de agregar, ya que se basa en el polimorfismo. Sin embargo, debido a que se basa únicamente en polimorfismo, las nuevas funcionalidades deben realizarse sobre una base fija de métodos, por lo que es necesario ser claros en la cantidad de métodos que se pueden llegar a requerir para implementar todos los protocolos que se quiere dar soporte.
  * **Strategy**: Este patrón de diseño se basa en herencia desde una interfaz por ende los nuevos protocolos son muy fáciles de agregar. Además que la manera en que se indica que clase se quiere emplear en la ejecución de un comando, nos da la ventaja de emplear una estructura de configuración. Ya que se puede emplear un identificador del tipo de protocolo y el contexto en donde se ejecuta no requiere conocer la clase, únicamente su identificador, esto es una propiedad de intercambiabilidad entre los protocolos. Esto es diferente a lo que sucede en el caso de Template ya que en ese caso, el contexto sí requiere conocer la clase que se quiere emplear.


Entonces a partir del análisis anterior podemos plantear un bloque llamado **TransportServer**, en este bloque de función se implementan las funcionalidades de comunicación con el `eieManager`. La implementación de este bloque se basa en el patrón de diseño strategy ya que este permite una modificabilidad alta, además de una integración con diferentes protocolos bastante alta. Un punto importante por el cual se emplea este patrón de diseño es que el contexto no se quiere conocer la implementación de la funcionalidad deseada únicamente un identificador del mismo. Por lo tanto en adición se define un bloque de configuración **ConfigDev** el cual implementa estas configuraciones para su fácil adaptabilidad entre diferentes dispositivos. 


**Paso 5:** Instantiate Architectural Elements and Allocate Responsibilities


* ``Command``: De este módulo se derivan los comandos soportados por el sistema, es decir, cada comando se define por herencia a partir de la interfaz implementada en el bloque comando. Este recibe el identificador del comando y la lista de argumentos requeridos por el sistema. 
* ``CommandManager``: En este módulo se implementa el invocador de los comandos, el cual es el encargado de registrar los comandos, e invocar su ejecución. Además se encarga de implementar una cola la cual se llena con las requests entrantes desde el ``TransportServer``.
* ``ConfigDev``: En este módulo se definen las configuraciones necesarias para el sistema. Las cuales son determinadas para cada uno de los dispositivos ``eieDevice``.
* ``TransportServer``: En este se implementa la lógica requerida para poder responder a request provenientes del ``eieManager``. Como se mencionó en la etapa anterior, este bloque se basa en la metodología Strategy, por lo tanto en este módulo se define la lógica del contexto, el cual se define como un **listener**, debido a que es un sistema de tipo servidor. Además es el encargado de definir el tipo de protocolo, a partir de la configuración determinada en el módulo ``ConfigDev``. 
* ``Protocolo``: En este módulo se implementa la interfaz base del protocolo, así como los protocolos soportados.


**Paso 6:** Define Interfaces for Instantiated Elements.

Los datos en el sistema viajan en cascada, por ejemplo cuando un paquete entra (``Protocolo``) llega al ``TransportServer``, de ahí pasa al ``CommandManager`` donde entra a la cola, cuando sale de la cola este se envía al ``command``, el cual ejecuta la función y devuelve el resultado al ``CommandManager`` el cual a su vez devuelve el resultado al ``TransportServer``, para ser enviado al ``eieManager`` de vuelta. El método de conexión entre los módulos es por referencia, y por instancia. Donde el contenido de los paquetes que se transportan son el comando (id del comando), y argumentos. En la comunicación de regreso al cliente, el payload de la respuesta es el resultado del comando ejecutado.

Debido a que el sistema es un servidor este debe tener una rutina de inicialización la cual en este caso es la definir el tamaño máximo de la cola de comandos, así como la de iniciar el servidor de comunicaciones, en la cual se ejecuta configura el protocolo que se requiere. Todo esto antes de enviar un mensaje de estatus al ``eieManager``, el cual notifica que el dispositivo se encuentra operando con funcionalidad.


**Paso 7:** Verify and Refine Requirements and Make Them Constraints for Instantiated Elements.

Al emplear el patrón de diseño **command** Se garantiza la funcionalidad requerida en el primer requerimiento del sistema y el cuarto requerimiento, ya que agregar nuevos comandos se vuelve muy sencillo, y es posible soportar múltiples comandos. Además entre las funciones del ``commandManager`` se encuentra la de implementar una cola de comandos, lo cual cumple con los requerimientos solicitados. Al emplear la metodología de strategy nos garantizamos el cumplimiento del tercer requerimiento solicitado para el ``eieDevice``. Además nos garantizamos con el cumplimiento del atributo de calidad de modificabilidad ya que los protocolos soportados son mantenibles. 

En el caso del segundo requerimiento éste no afecta la arquitectura del sistema por lo tanto no tiene repercusión en las decisiones de diseño tomadas.


Patrones de diseño
******************

Proxy:
======

Como se sabe de la definición de este patrón de diseño, un proxy es una clase funcionando como una interfaz intermedia a algo más, a cualquier cosa.

Esta es exactamente la situación que se presenta en el enunciado laboratorio, en la que el ``eieManager`` va a funcionar como una interfaz intermedia entre el ``eieclient`` y los devices a los que el client quiere alcanzar.

La interfaz o la clase intermedia del ``eieManager`` tiene funcionalidad agregada y no solo hace forwarding de la data, pero para este momento del diseño, funciona básicamente como una caja negra la cual recibe entradas y da salidas según los requerimientos funcionales. 

Relación del patrón con el diseño:
----------------------------------

Siendo en este caso el ``TransportClient`` el proxy o la caja intermedia entre el client y los devices. Además de que se puede relacionar con el patrón de diseño ``Adapter`` el cual ayuda a implementar de una manera mas directa y sencilla los requerimientos funcionales y compatibilidad de diferentes protocolos. 

El proxy en la sana teoría solo  debería de hacer forwarding de la data, y usando una "caja" extra con el dicho ``Adapter`` se puede modificar esa data para cumplir los requerimientos.

Command:
========

``Command`` es uno de los muchos patrones de diseño de comportamiento, el cual abstrae una solicitud, en un objeto totalmente independiente, el cual contiene toda la información sobre la misma solicitud.

Esta abstracción permite parametrizar los métodos con diferentes solicitudes o comandos en el caso del sistema en cuestión, además de retrasar o poner en cola la ejecución de una solicitud y soportar operaciones que no se pueden realizar.

* Encapsular la información requerida para ejecutar comandos en dispositivos específicos:

La clase ``command`` va a tener como atributo un ``deviceID`` con el fin de identificar al dispositivo al que se le quiere hablar, además va a tener otro atributo el cual encapsule el comando que se le va a mandar al device. Si al llegar al device correspondiente el mismo es capaz de ejecutarlo, lo ejecuta, sino crea un mensaje de error. 

* Ejecutar los comandos y esperar la respuesta correspondiente:

En este caso se hace uso de la clase llamada ``commandInvoker``, la cual se encarga de recibir los comandos, encolarlos, y enviarlos a ejecución.

Diagramas UML
*************

A partir de lo mencionado anteriormente, se realizaron los diagramas UML de clases para los componentes eieManager y eieDevice con las clases designadas para cada componente. Los diagramas realizados son los siguientes:

.. uml::

  title Classes - Class Diagram

  Class DatabaseHandler{}
  APIServer -down-- eieManager
  CommandInvoker -left-- eieManager

  CommandRegistry--|> CommandInvoker
  CommandInfo --|> CommandRegistry

  eieManager -- GroupManager
  eieManager -- DeviceManager

  Group -up--|> GroupManager
  Device -up--|> DeviceManager

  TransportClient -right-- eieManager


  TransportClient <|.. RPCClient
  TransportClient <|.. TCPClient
  TransportClient <|.. UDPClient

.. uml::

  title Classes - eieDevice

  TransportServer -- eieDevice

  Protocol -right-- eieDevice
  ConfigDev -- eieDevice

  Command_Manager -left-- eieDevice

  Protocol <|.. RPCServer
  Protocol <|.. TCPServer
  Protocol <|.. UDPServer

  Command_Manager <|-- Command
  
Teniendo los diagramas de clases, se procedio a realizar los diagramas secuenciales para los comandos a dispositivos específicos y a grupos de broadcast, esto para tener mejor control de cuales son los procesos o clases que llevan el flujo del programa. El diagrama secuencial de la comunicacion con un dispositivo es el siguiente:

.. uml::

  title Device - Sequence Diagram

  Client -> APIServer: Solicitud de datos/acciones

  APIServer -> Manager: Lectura e invocación del comando

  Manager -> DeviceManager: Se obtiene la información del dispositivo solicitado

  Manager <- DeviceManager: Se obtiene la información del dispositivo solicitado

  APIServer <- Manager: Datos/acciones efectuadas a la solicitud

  Client <- APIServer: Respuesta de de datos/acciones

.. uml::

  DeviceManager -> CommandInvoker: Se solicita implementación del comando
  
  CommandInvoker <-> TransportProxy: Envio del comando entre los sistemas

  TransportProxy -> Device: Lectura e implementación del comando

  TransportProxy <- Device: Respuesta al comando recibido

  CommandInvoker <-> TransportProxy: Respuesta del dispositivo entre los sistemas

  DeviceManager <- CommandInvoker: Se proporciona respuesta del dispositivo

El diagrama secuencial de la comunicacion con un grupo de broadcast es el siguiente:

.. uml::

  title Group - Sequence Diagram

  Client -> APIServer: Solicitud de datos/acciones

  APIServer -> Manager: Lectura e invocación del comando

  Manager -> GroupManager : Se obtiene la información del dispositivo solicitado

  Manager <- GroupManager : Se obtiene la información del grupo solicitado

  APIServer <- Manager: Datos/acciones efectuadas a la solicitud

  Client <- APIServer: Respuesta de de datos/acciones

.. uml::

  GroupManager -> DeviceManager: Indica cuales dispositivos deben ser utilizados

  DeviceManager -> CommandInvoker: Se solicita implementación del comando

  CommandInvoker <-> TransportProxy: Envio del comando entre los sistemas

  TransportProxy -> Group: Lectura e implementación del comando

  TransportProxy <- Group: Respuesta al comando recibido

  CommandInvoker <-> TransportProxy: Respuesta del grupo entre los sistemas

  DeviceManager <- CommandInvoker: Se proporciona respuesta del dispositivo

  GroupManager <- DeviceManager: Verifica la respuesta de todos los dispositivos