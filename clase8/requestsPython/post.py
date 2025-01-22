import requests

data = {
    "jsonrpc": "2.0",
    "id": 1,
    "method": "eth_getBalance",
    "params": ["0x7e2Bf2537086d1A22791CE00015BbE34Ed2D301c", "latest"]
}

response = requests.post("https://comunyt.co/repost.php", json=data)
print(response.json()["result"])