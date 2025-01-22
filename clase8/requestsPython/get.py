"""
Este script hace lo siguiente:
1. Importa la biblioteca requests.
2. Realiza una solicitud a la API de DolarAPI para obtener datos del dólar.
3. Convierte la respuesta en formato JSON.
4. Imprime el precio de compra del dólar.
"""

import requests  # Importa la biblioteca requests para hacer solicitudes HTTP

# Realiza una solicitud GET a la API de DolarAPI
response = requests.get("https://dolarapi.com/v1/dolares/bolsa")

# Convierte la respuesta de la API a formato JSON
data = response.json()

# Imprime el valor de compra del dólar
print(data["compra"])