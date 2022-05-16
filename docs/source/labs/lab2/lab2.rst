************
Laboratorio 2
*************

* Andrés Arias Campos - B80661
* Erick Sancho Abarca - B77145
* Gabriel Araya Mora - B80525

Diseño de los endpoints
***********************

Para el presente laboratorio, se utilizo el web framework de FastAPI para construir una REST API que permita la conexion entre el cliente y el eieManager. La API cuenta con los metodos HTTP basicos como lo son el GET, POST, PUT y DELETE para manejar el intercambio de informacion con el cliente, y en cada una de las funciones propias del API se interactua con el DeviceManager para el manejo de los Devices.



Metodos de la API:
==================

Los metodos trabajan bajo el route ``/devices``, con excepcion del **Get_command** que utiliza el route ``/command``. Los metodos usados son los siguientes:

#. Create_device: Mediante un metodo POST se crea un nuevo **Device** con la informacion suministrada en el Body del metodo.
#. Update_device: Mediante un metodo PUT se pasa la informacion en el Body del **Device** a cambiar y el backend realiza los cambios respectivos.
#. Devices_info: Mediante un metodo GET se retorna toda la lista de **Devices** que haya dentro del eieManager.
#. Device_info: Mediante un metodo GET al route ``/devices/{ID}`` se retorna el **Device** que tenga el mismo ID del route dentro del eieManager.
#. Delete_device: Mediante un metodo DELETE al route ``/devices/{ID}`` se elimina el **Device** que comparta el mismo ID del route dentro del eieManager.
#. Get_command: Mediante un metodo POST al route ``/command`` se envia el comando deseado con la informacion dentro del Body.

Consideraciones especiales de diseño:
=====================================

#. Con el fin de evitar el acoplamiento entre el ``API`` y el ``DeviceManager`` , y mantener su funcionalidad dentro de los limites de los mismos, se implementó un ``DeviceManager`` global, el cual maneja los comandos del ``CRUD`` y el ``API`` solo consume estos servicios.
#. Con el fin de apegarse la documentación del ``FastAPI`` se divide el mismo en dos funciones, esto para separar la estructura del ``API``, en dos partes, donde la primera implementa la función base y la segunda contiene la implementación de los entry points. 
