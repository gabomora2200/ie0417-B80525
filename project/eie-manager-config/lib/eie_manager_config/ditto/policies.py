import requests

def set_policy(policy_name, payload):

    url = f"http://localhost:8080/api/2/policies/{policy_name}"


    headers = {
        'Authorization': 'Basic ZGl0dG86ZGl0dG8=',
        'Content-Type': 'application/json'
    }

    response = requests.request("PUT", url, headers=headers, data=payload)

    return response.status_code, response.text
