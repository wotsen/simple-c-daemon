from socket import *
import struct
import json
import time

HOST = '127.0.0.1'
PORT = 6002
s = socket(AF_INET, SOCK_DGRAM)
s.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
s.bind((HOST, PORT))
s.setsockopt(SOL_SOCKET, SO_SNDTIMEO, struct.pack('LL', 3, 0))
s.setsockopt(SOL_SOCKET, SO_RCVTIMEO, struct.pack('LL', 3, 0))

_TEST_DATA = """{'head': {'os_type': 'Linux', 'hostname': 'ubuntu', 'os_release': '4.13.0-43-generic', 'os_version': '#48-Ubuntu SMP Wed May 16 12:18:48 UTC 2018', 'os_machine': 'x86_64', 'cur_time': '2018 8 3 friday 16:12:1'}, 'module': {'src': 'none', 'dest': 'none', 'module-name': 'network', 'module-id': 3, 'module-len': 1, 'module-ack': 255, 'module-cmd': 3}, 'key-1': {'key-name': 'heart beat', 'key-id': 1, 'key-len': 4096, 'key-type': 13, 'key-ack': 255, 'key-cmd': 3, 'context': 'daemon heart beat'}, 'key-end': {'key': 'end'}}"""

while True:
    s.sendto(bytes(_TEST_DATA, encoding="utf-8"), (HOST, 6000))
    #print("send")
    time.sleep(2)
    try:
        data, addr = s.recvfrom(1024)
    except:
        pass
    else:
        if data:
            #print(data)
            print(json.loads(str(data, encoding='utf-8')))

s.close()


