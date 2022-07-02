import requests

def add_thing(thing_id, payload):

    url = f"http://localhost:8080/api/2/things/{thing_id}"


    headers = {
        'Authorization': 'Basic ZGl0dG86ZGl0dG8=',
        'Content-Type': 'application/json'
    }

    response = requests.request("PUT", url, headers=headers, data=payload)

    return response.status_code, response.text