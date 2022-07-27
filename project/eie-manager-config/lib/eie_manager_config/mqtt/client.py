from ..utils.device_discovery import device_discovery
import paho.mqtt.client as mqtt
import json


def on_connect(client, userdata, flags, rc):
    if rc==0:
        client.connected_flag=True #set flag
        client.subscribe('eie-manager/config/device_discovery/request')
        print("connected OK")
    else:
        print("Bad connection Returned code=",rc)
        client.loop_stop()  

def on_disconnect(client, userdata, rc):
   print("client disconnected ok")

def on_publish(client, userdata, mid):
    print("In on_pub callback mid= "  ,mid)

def on_message(client, userdata, message):
    # print("message received " ,str(message.payload.decode("utf-8")))
    # print("message topic=",message.topic)
    # print("message qos=",message.qos)
    # print("message retain flag=",message.retain)

    resp = userdata.register(message.payload)

    MQTT_publish(client, "eie-manager/config/device_discovery/response", resp)





def MQTT_publish(client, topic: str, payload: str):
    try:
        client.publish(topic, payload)
    except:
        print("Error at publish message")


def MQTT_suscribe(client, topic: str):
    client.subscribe(topic)


def mqtt_start():
    dev_disc_mgr = device_discovery()

    client = mqtt.Client("MQTT_conection") #create new instance
    client.on_message = on_message
    client.on_connect = on_connect
    client.on_disconnect = on_disconnect

    client.user_data_set(dev_disc_mgr);

    
    client.connect("172.17.0.1", port=1883) #connect to broker    

    client.loop_forever()