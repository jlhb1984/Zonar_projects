import csv
import random
from urllib import request
import json
import datetime
import requests

def get_api_information():
    
    try:
        url=f'https://api.tsomobile.com/rest/Authentication/ValidateUser'
        payload={
        "login": "jhurtado",
        "password": "Azul1984"
        }
        response=requests.post(url,json=payload)
        
    except Exception as e:
        print("Trouble while try to connect!")   

    return response.json();

if __name__== '__main__':
    cad=get_api_information()
    print(cad)