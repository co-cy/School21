# Linux Network
## Part 1

### 1.1
1) 192.167.38.54/13 <br/>
192.160.0.0 <br/>
2) 255.255.255.0<br/>
24 = 11111111.11111111.11111111.00000000<br/>
3) /15<br/>
255.254.0.0 = 11111111.11111110.00000000.00000000
4) 11111111.11111111.11111111.11110000<br/>
 255.255.255.240 = 28
5) 12.167.38.4/8<br/>
HostMin:   12.0.0.1<br/>
HostMax:   12.255.255.254<br/>
6) 12.167.38.4/11111111.11111111.00000000.00000000<br/>
HostMin:   12.0.0.1<br/>
HostMax:   12.167.255.254<br/>
7) 12.167.38.4/255.255.254.0<br/>
HostMin:   12.0.38.1<br/>
HostMax:   12.167.39.254<br/>
8) 12.167.38.4/4<br/>
HostMin:   0.0.0.1<br/>
HostMax:   15.255.255.254<br/>

### 1.2
127.0.0.1/8<br/>

TRUE<br/>
- 127.0.0.2
- 127.1.0.1

FALSE<br/>
- 194.34.23.100
- 128.0.0.1

### 1.3
Private:
- 10.0.0.45
- 192.168.4.2
- 172.20.250.4
- 172.16.255.255
- 10.10.10.10

Public:
- 134.43.0.2
- 172.0.2.1
- 192.172.0.1
- 172.68.0.2
- 192.169.168.1


Possible:
- 10.10.0.2
- 10.10.10.10
- 10.10.1.255

Impossible:
- 10.0.0.1
- 10.10.100.1

## Part 2

ip a (ws1)
![](images/part2/ip_a_ws1.png)

ip a (ws2)
![](images/part2/ip_a_ws2.png)

etc/netplan/00-installer-config.yaml (ws1)
![](images/part2/netplan_ws1.png)

etc/netplan/00-installer-config.yaml (ws2)
![](images/part2/netplan_ws2.png)

sudo netplan apply (ws1)
![](images/part2/netplan_apply_ws1.png)

sudo netplan apply (ws2)
![](images/part2/netplan_apply_ws2.png)

### Part 2.1

ip r add (ws1)
![](images/part2/ping_ws1_ws2.png)

ip r add (ws2)
![](images/part2/ping_ws2_ws1.png)

### Part 2.2

new_netplan (ws1)
![](images/part2/new_netplan_ws1.png)

ping new_netplan
![](images/part2/ping_new_netplan_ws1.png)

new_netplan (ws2)
![](images/part2/new_netplan_ws2.png)

ping new_netplan
![](images/part2/ping_new_netplan_ws2.png)


## Part 3

### Part 3.1
8 Mbps в MB/s = 1MB/s, <br/>
100 MB/s в Kbps = 800 000 Kbps, <br/>
1 Gbps в Mbps = 1000 Mbps <br/>

### Part 3.2

iperf3 -s - Создание сервера
iperf3 -c <ip> - Подключиться к серверу тестирования
![](images/part3/iperf3.png)

## Part 4

firewall for ws1
![](images/part4/firewall_ws1.png)

firewall for ws2
![](images/part4/firewall_ws2.png)

Apply firewall ws1
![](images/part4/apply_firewall_ws1.png)

Apply firewall ws2
![](images/part4/apply_firewall_ws2.png)

Разница между стратегиями: <br/>
В 1-й стратегии мы разрешаем, а потом пытаемся перезаписать запрещающим правилом. (Но этого не происходит, потому что перезаписывать нельзя)<br/>
Во 2-й мы с начало запрещаем, а потом разрешаем (Но этого не происходит, потому что перезаписывать нельзя)<br/>

### Part 4.2
nmap
![](images/part4/nmap.png)

## Part 5 