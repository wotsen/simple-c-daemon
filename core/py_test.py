
from socket import *
import json
import time

HOST = '0.0.0.0'
PORT = 6002
s = socket(AF_INET,SOCK_DGRAM)
s.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
s.bind((HOST,PORT))

_TEST_DATA = """{'head': {'os-type': 'Linux', 'hostname': 'ubuntu', 'os-release': '4.13.0-43-generic', 'os-version': '#48-Ubuntu SMP Wed May 16 12:18:48 UTC 2018', 'os-machine': 'x86_64', 'cur-time': '2018 8 3 friday 16:12:1'}, 'module': {'src': 'none', 'dest': 'none', 'module-name': 'network', 'module-id': 3, 'module-len': 1, 'module-ack': 255, 'module-cmd': 3}, 'key-1': {'key-name': 'heart beat', 'key-id': 1, 'key-len': 4096, 'key-type': 13, 'key-ack': 255, 'key-cmd': 3, 'context': 'daemon heart beat'}, 'key-end': {'key': 'end'}}"""

while True:
    #data, addr = s.recvfrom(1024)
    #print(json.loads(str(data, encoding='utf-8')))
    s.sendto(bytes(_TEST_DATA, encoding="utf-8"), (HOST, 6000))
    print("send")
    time.sleep(2)

s.close()


