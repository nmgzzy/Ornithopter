import json
import socket
import time

parameter = {
    'pp': 1, 'pi': 0.2, 'pd': 3.5, 'pil': 100, 'poul': 1000, 'podl': 0,
    'rp': 1, 'ri': 0.2, 'rd': 3.5, 'ril': 100, 'roul': 1000, 'rodl': 0,
    'yp': 1, 'yi': 0.2, 'yd': 3.5, 'yil': 100, 'youl': 1000, 'yodl': 0,
    'ssid': 'jmi11', 'pswd': 'babababa'
    }
address = "192.168.41.197"
port = 12345


def postPar():
    parJson = json.dumps(parameter)
    print(len(parJson.encode(encoding='ascii')))
    client = socket.socket(type=socket.SOCK_DGRAM)
    client.sendto(parJson.encode(encoding='ascii'),(address,port))
    re_Data, addr = client.recvfrom(1024)
    print('ESP32>>',re_Data.decode('utf-8'))
    client.close()

def listen():
    client = socket.socket(type=socket.SOCK_DGRAM)
    count = 60 * 5
    while True and count > 0:
        re_Data, addr = client.recvfrom(1024)
        print('ESP32>>',re_Data.decode('utf-8'))
        time.sleep(0.2)
        count -= 1
    client.close()


# def getPar():
    
#     pass

# listen()
postPar()