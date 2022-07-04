********
Proyecto
********

* Andrés Arias Campos - B80661
* Erick Sancho Abarca - B77145
* Gabriel Araya Mora - B80525

Planeamiento
************

Para el presente proyecto, se utiliza el framework de desarrollo y manejo de proyectos `SCRUM`. Por lo que el primer paso a seguir es separar el problema en releases o entregas estratégicas y coherentes de tal forma que al cumplir uno de estos milestones, el mismo sirva para desarrollar la entrega posterior.

Cada release o sprint, se hace pensando en desarrollar un componente completamente funcional del software o sistema en cuestión.

Para el planeamiento de este proyecto, se usa la herramienta `taiga.io`, con el fin de poner en práctica toda la teoría ``SCRUM`` vista en clase. 

Además, después de varias sesiones de planeamiento se definieron:

* Los `Epics` del proyecto en función de la arquitectura del proyecto.

* Los `User Stories` para cada `Epic`, los cuales fueron nombrados desde el punto del vista del usuario. 

* Los `Tasks` específicos para complementar cada `User story`.

* Se distribuyeron los `User Stories` entre los miembros del equipo. 

Justificación
*************

Debido a que las acciones de eieLabs han crecido exponencialmente, hay muchos inversionistas que han puesto in ojo en las plataformas de IoT como lo es ``eieManager``. El objetivo final de esta plataforma es administrar una gran cantidad de diferentes dispositivos dentro de un ambiente industrial. 

Después de una reunión con los ejecutivos de alto rango de eieLabs, se llamó al arquitecto de software, el cual ha informado que si bien ``eieManager`` tiene un gran potencial, aún hay problemas a nivel de requerimientos funcionales del sistema y los atributos de calidad del mismo. 

* Los ``RPCs`` que se usan actualmente en el sistema no se ajustan del todo a la necesidad de comunicar eventos de forma asincrónica desde los dispositivos. 

* La arquitectura actual del sitema no toma en cuenta el concepto de los diferentes niveles de autorización para el acceso a los diferentes grupos de dispositivos.

* Los clientes han manifestado que a nivel de mantenibilidad, al sistema le faltan cosas, ya que darle soporte es complejo. Lo anterior debido a que los dispositivos se deben registrar manualente, modificando el archivo ``JSON``. 

Con base en lo hablado en esta reunión, los ejecutivos de eieLabs aprueban todo lo necesario para que el departamento de ``R&D``, haga un prototipo de ``eieManager 2.0``, el cual sea una mejora del modelo anterior, además de contener una nueva arquitectura que permita cubrir las necesidades de los inversionistas y así hacer crecer el negocio.

El patrón de diseño `broker` sirve para estas necesidades ya que el mismo cuenta como un componente encargado de coordinar la comunicación entre dos componentes. El `broker` se encarga de enviar las solicitudes del cliente a su respectivo `device`, además de ayudar a transmitir los resultados de dichas solicitudes y errores que aparezcan.

De esta forma es que se puede inicializar por medio del `broker` los diferentes dispositivos a partir de las señales enviadas por el ``eie-Manager-config``. De igual manera, si el dispositivo se inicializa solo, el ``broker`` debe recibir las señales enviadas para así publicar su configuración al manager config.

Requerimientos
**************

Requerimientos Funcionales eie-device:
======================================

* ``eieDev-REQ-001`` Cada uno de los dispositivos deben ser capaces de inicializarse a sí mismos, por medio de un archivo de configuración, o bien por medio de un `request` del ``eie-Manager-Config`` con su respectiva configuración.
* ``eieDev-REQ-002`` Al inicializarse cada dispositivo, este debe publicar su respectiva configuración al ``eie-Manager-Config`` y luego recibir su respectivo ``UID``. 
* ``eieDev-REQ-003`` La biblioteca debe ser capaz de abstraer el manejo del protocolo ``Ditto``, el protocolo ``MQTT``, y el handling del ``CJSON``.
* ``eieDev-REQ-004`` Ser capaz de registrar funciones que respondan a callbacks.



Requerimientos Funcionales eie-manager-config:
==============================================

* ``eieMC-REQ-001`` Administración del `Twin` de ``Ditto`` y la configuración del ``eieDevice``. 
* ``eieMC-REQ-002`` Ser capaz de enviar y recibir ( publicación/suscripción ) mensajes en el administrador de ``MQTT``.
* ``eieMC-REQ-003`` Registrar el dispositivo a partir de un archivo de configuración empleando el ``Device Discovery``.
* ``eieMC-REQ-004`` Asignar un ``UID`` a cada nuevo dispositivo que se inicialice.


Diseño de API
**************

* Create_device: Esta función recibe la configuración y su `UID` por parte del ``eie-Manager-Config``, y se crea una estructura ``Thing``. Esta función sirve para inicizalizar el dispositivo desde el cliente.
* Destroy_device: Se desregistrar la estructura ``Thing`` y el dispositivo como tal, este debe enviar una notificación a ``Ditto`` y el ``eie-Mmanager-Config`` para borrar el `Twin` y su configuración del sistema. Esta función no parámetros, simplemente se ejecuta.
* Modify_config: Esta se utiliza para añadir, eliminar o actualizar la propiedad `configuration` en el feature del `Twin`.
* Register_callback: Este recibe el puntero a una función (callback) y el `feature` al cual esta ligado dicha función.
* Update_feature: Esta función recibe el nombre del `feature` y su dato respectivo, para luego ser enviado a ``Ditto`` mediante una publicación por ``MQTT`` y este actualizar el `Twin`.

Diagramas
**********

* Diagrama de secuencia para el primer escenario:

.. uml::
    client -> Ditto: Modifica la propiedad configuration
    Ditto -> MQTT_broker: Envío de la propiedad mediante evento
    MQTT_broker -> eie_device: Realiza el callback con el configuration
    eie_device -> eie_device: Realiza un callback de la propiedad configuration

* Diagrama de secuencia para el segundo escenario:

.. uml::
    eie_device -> MQTT_broker: Publica una actualización de status
    MQTT_broker -> Ditto: Actualización del Twin con el nuevo status

* Diagrama de secuencia para el tercer escenario:

.. uml::
    eie_device -> MQTT_broker: Publica la configuración del Thing/device
    MQTT_broker -> eie_manager_config: Toma la configuracion del evento y la guarda
    eie_manager_config -> MQTT_broker: Le asigna un ID único al device por evento
    eie_manager_config -> Ditto: Crea un digital twin para el device
    MQTT_broker -> eie_device: Realiza un callback con el ID del device
    eie_device -> eie_device: Toma el callback para actualizar la configuración
