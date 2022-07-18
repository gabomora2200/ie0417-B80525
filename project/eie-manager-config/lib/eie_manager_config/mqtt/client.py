import paho.mqtt.client as mqtt
import time

def on_connect(client, userdata, flags, rc):
    if rc==0:
        client.connected_flag=True #set flag
        client.subscribe('v1/devices/me/rpc/request/+')
        print("connected OK")
    else:
        print("Bad connection Returned code=",rc)
        client.loop_stop()  

def on_disconnect(client, userdata, rc):
   print("client disconnected ok")

def on_publish(client, userdata, mid):
    print("In on_pub callback mid= "  ,mid)


def MQTT_publish(topic: str, payload: str):
    try:
        client.publish(topic, payload)
    except:
        print("Error at publish message")

def on_message(client, userdata, message):
    print("message received " ,str(message.payload.decode("utf-8")))
    print("message topic=",message.topic)
    print("message qos=",message.qos)
    print("message retain flag=",message.retain)

def MQTT_suscribe(topic: str):
    client.subscribe(topic)

broker_address="172.17.0.1"

client = mqtt.Client("MQTT_conection") #create new instance

client.connect(broker_address, port=1883) #connect to broker

client.on_message = on_message
client.on_connect = on_connect
client.on_disconnect = on_disconnect



while (1):
    client.loop()

    MQTT_suscribe("devices/send")

    time.sleep(5)
    
    MQTT_publish("devices/send", "Hola mundo")