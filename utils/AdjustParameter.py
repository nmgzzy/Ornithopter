import json
import socket



parameter = {
    'pp': 1, 'pi': 0.2, 'pd': 3.5, 'pil': 100, 'poul': 1000, 'podl': 0,
    'rp': 1, 'ri': 0.2, 'rd': 3.5, 'ril': 100, 'roul': 1000, 'rodl': 0,
    'yp': 1, 'yi': 0.2, 'yd': 3.5, 'yil': 100, 'youl': 1000, 'yodl': 0,
    }
address = "127.0.0.1"
port = 12345


def postPar():
    parJson = json.dumps(parameter)
    if len(parJson.encode()) >= 600:
        print(len(parJson.encode()))
        return
    # client = socket.socket(type=socket.SOCK_DGRAM)
    # client.sendto(parJson.encode(),(address,port))
    # re_Data,address = client.recvfrom(1024)
    # print('server>>',re_Data.decode('utf-8'))
    # client.close()
    # pass

# def getPar():
    
#     pass

postPar()