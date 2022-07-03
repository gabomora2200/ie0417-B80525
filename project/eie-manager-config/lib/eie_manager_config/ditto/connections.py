import requests

def set_connection(payload):

    url = "http://localhost:8080/devops/piggyback/connectivity?timeout=10s"

    headers = {
    'Authorization': 'Basic ZGV2b3BzOmZvb2Jhcg=='
    }

    response = requests.request("POST", url, headers=headers, data=payload)

    return response.status_code, response.text