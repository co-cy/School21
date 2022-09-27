# Linux Network

5.1 - [Инструмент ipcalc](#part-1) \
5.2 - [Статическая маршрутизация между двумя машинами](#part-2) \
5.3 - [Утилита iperf3](#part-3) \
5.4 - [Сетевой экран](#part-4) \
5.5 - [Статическая маршрутизация сети](#part-5) \
5.6 - [Динамическая настройка IP с помощью DHCP](#part-6) \
5.7 - [NAT](#part-7-nat) \
5.8 - [Допополнительно. Знакомство с SSH Tunnels](#part-8)


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

### Part 5.1
etc/netplan/00-installer-config.yaml для всех машин
![](images/part5/netplan.png)
![](images/part5/netplan2.png)

ws11 ip -4 a
![](images/part5/ip_4_a_ws11.png)
r1 ip -4 a
![](images/part5/ip_4_a_r1.png)
r2 ip -4 a
![](images/part5/ip_4_a_r2.png)
ws21 ip -4 a
![](images/part5/ip_4_a_ws21.png)
ws22 ip -4 a
![](images/part5/ip_4_a_ws22.png)

### Part 5.2
sudo sysctl -w net.ipv4.ip_forward=1
![](images/part5/sysctl_w_net.png)

sudo vim /etc/sysctl.conf
![](images/part5/edit_conf.png)

### Part 5.3
etc/netplan/00-installer-config.yaml для всех машин
(nameservers в ws21 ненужны, а скрин менять мне лень)
![](images/part5/netplan.png)
![](images/part5/netplan2.png)

ip r
![](images/part5/ip_r.png)

tcpdump
![](images/part5/tcpdump.png)

### Part 5.4
etc/netplan/00-installer-config.yaml для всех машин
(nameservers в ws21 ненужны, а скрин менять мне лень)
![](images/part5/netplan.png)
![](images/part5/netplan2.png)

ip r
![](images/part5/ip_r.png)

ip r list 10.10.0.0/[маска сети] и ip r list 0.0.0.0/0
![](images/part5/ip_r_list.png)
Если есть какой-то другой путь до сети, путь по умолчанию не будет выбран

### Part 5.5
traceroute
![](images/part5/traceroute.png)
Как работает traceroute. \
1. Traceroute отправляет пакет к точке назначения, устанавливая TTL равным 1;
2. Каждый роутер в маршруте уменьшает значение TTL на единицу, пока TTL не достингнет нуля;
3. Когда TTL становится == 0 то роутер, который отбрасывает этот пакет, отправляет отправителю сообщение ICMP TTL Exceeded , в которое включаются первые 28 байт оригинального “зондирующего” пакета; 
4. Traceroute получает это сообщение и использует разницу во времени между отправкой оригинального пакета и полученным в ответ пакетом ICMP для посчета задержки доставки к этому роутеру/хопу;
5. Процесс повторяется с п. 1, но с TTL увеличенным на 1, пока…. 
6. Окончательный получатель получает пакет от traceroute и отправляет в ответ сообщение, отличное от ICMP TTL Exceeded . Тогда traceroute считает, что трассировка завершена и заверает процесс. 

### Part 5.6
ping -c 1 10.30.0.111
![](images/part5/ping_c.png)

## Part 6
/etc/dhcp/dhcpd.conf
![](images/part6/dhcpd.png)
resolv.conf
![](images/part6/resolv.png)
systemctl restart isc-dhcp-server && ip a
![](images/part6/systemctl.png)
ping ws21 - ws22
![](images/part6/ping21-22.png)
macaddress: 10:10:10:10:10:BA, dhcp4: true
![](images/part6/fixed_mac.png)

r1 dhcp
![](images/part6/r1_dhcp.png)
r1 resolv
![](images/part6/r1_resolve.png)

r1 restart and ws11 ip a
![](images/part6/r1_restart_ws11_ip_a.png)

ws11 dhcp update
![](images/part6/ws11_dhcp_update.png)

## Part 7

apache2 ws22 && r1
![](images/part7/apache.png)

ping ws22 && r1
![](images/part7/ping.png)

apply icmp
![](images/part7/apply_ping.png)

SNAT and DNAT
![](images/part7/snat_dnat.png)

telnet
![](images/part7/telnet.png)