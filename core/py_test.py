
from socket import *
import json
import time

HOST = '0.0.0.0'
PORT = 6002
s = socket(AF_INET,SOCK_DGRAM)
s.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
s.bind((HOST,PORT))

while True:
    data, addr = s.recvfrom(1024)
    print(json.loads(str(data, encoding='utf-8')))
    time.sleep(2)

s.close()


