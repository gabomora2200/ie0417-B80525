from ..ditto.thing import add_thing
import json

class device_discovery:

    things = {}

    def gen_thing_id(self, namespace: str):
        if (namespace in self.things.keys()):
            place = str(namespace) + ":" + str(len(self.things[namespace]))
            self.things[namespace].append(place)
            return place
        else:
            self.things[namespace] = [str(namespace) + ":0"]
            return str(namespace) + ":0"
        
    def register(self, data: str):
        payload = json.loads(data)
        thing_id = self.gen_thing_id(payload["namespace"])
        features = {'policyId': 'my.test:policy', 'features': payload['features']}
        add_thing(thing_id, json.dumps(features))

        resp = {"thing_id":thing_id, "correlation_id": payload["correlation_id"]}

        return json.dumps(resp)

