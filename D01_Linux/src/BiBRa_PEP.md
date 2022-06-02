
## Part 1. Installation of the OS
<div style="text-align:center">
    <p>Выполняем установу Ubuntu 20.4</p>
    <img src="./images/ricardo-milos.gif" title="Flex_Install" alt="Gashi" width="25%" height="25%"/>
    <img src="./images/ubuntu_mxuj2d96.gif" title="INFO_Install" alt="Install ubuntu" width="25%" height="25%"/>
</div>
<div style="text-align:center">
    <p>Убеждаемся что установили нужную версию Ubuntu</p>
    <img alt="Убеждаемся что установили нужную версию Ubuntu" height="600px" src="./images/T1.png"/>
</div>

## Part 2. Creating a user

<div style="text-align:center">
    <p>Выполняем команду для создания пользователя</p>
    <img alt="Выполняем команду для создания пользователя" height="600px" src="./images/T2.png"/>
</div>
<div style="text-align:center">
    <p>Выполняем команду для выдачи прав новому пользователю</p>
    <img alt="Выполняем команду для выдачи прав новому пользователю" height="600px" src="./images/T3.png"/>
</div>
<div style="text-align:center">
    <p>ФОТО ПО ТЗ</p>
    <img alt="ФОТО ПО ТЗ" height="600px" src="./images/T4.png"/>
</div>

## Part 3. Setting up the OS network
<div style="text-align:center">
    <p>Устанавливаем название машине</p>
    <img alt="Устанавливаем название машине" height="600px" src="./images/T5.png"/>
</div>
<div style="text-align:center">
    <p>Настраиваем и синхронизируем время</p>
    <img alt="Настраиваем и синхронизируем время" height="600px" src="./images/T6.png"/>
</div>
<div style="text-align:center">
    <p>Вывод сетевых интерфейсов с помощью консольной (синим цветом)</p>
    <img alt="Вывод сетевых интерфейсов с помощью консольной (синим цветом)" height="600px" src="./images/T7.png"/>
    <p>Loopback Interface - это специальный виртуальный сетевой интерфейс, который ваш компьютер использует для связи с самим собой. Он используется в основном для диагностики и устранения неполадок, а также для подключения к серверам, работающим на локальном компьютере. Интерфейс loopback также идентифицируется системой и имеет IP-адрес по умолчанию 127.0.0.1. Его можно просмотреть с помощью команды ip.</p>
</div>
<div style="text-align:center">
    <p>Вывод вывод нашего ip в сети DHCP</p>
    <img alt="Вывод вывод нашего ip в сети DHCP" height="600px" src="./images/T11.png"/>
    <p>DHCP - сетевая служба, которая позволяет хост-компьютерам автоматически назначать параметры с сервера, а не вручную настраивать каждый сетевой узел. Компьютеры, настроенные как DHCP-клиенты, не имеют никакого контроля над настройками, которые они получают от DHCP-сервера, и конфигурация прозрачна для пользователя компьютера.</p>
</div>
<div style="text-align:center">
    <p>ip-адрес шлюза (10.0.2.2)</p>
    <img alt="ip-адрес шлюза (10.0.2.2)" height="600px" src="./images/T25.png"/>
</div>
<div style="text-align:center">
    <p>Устанавливаю статический IP</p>
    <img alt="Устанавливаю статический IP" height="600px" src="./images/T26.png"/>
</div>
<div style="text-align:center">
    <p>Проверяю связь с серверами</p>
    <img alt="Проверяю связь с серверами" height="600px" src="./images/T27.png"/>
</div>

## Part 4. OS Update
<div style="text-align:center">
    <p>Обновлены все пакеты</p>         
    <img alt="Обновлены все пакеты</p>     " height="600px" src="./images/T8.png"/>
</div>

## Part 5. Using the sudo command
<div style="text-align:center">
    <p>Выданы права супер пользователя обычному пользователю</p>         
    <img alt="Выданы права супер пользователя обычному пользователю</p>     " height="600px" src="./images/T9.png"/>
</div>
<p><b>sudo</b> позволяет вызывать команды от другого лица. По умолчанию он вызывает от лица супер пользователя</p>
<div style="text-align:center">
    <p>Выданы права супер пользователя обычному пользователю</p>         
    <img alt="Выданы права супер пользователя обычному пользователю</p>     " height="600px" src="./images/T10.png"/>
</div>

## Part 6. Installing and configuring the time service
<div style="text-align:center">
    <p>Настраиваем и синхронизируем время</p>
    <img alt="Настраиваем и синхронизируем время" height="600px" src="./images/T6.png"/>
</div>

## Part 7. Installing and using text editors
<div style="text-align:center">
    <p>Установка всех 3-х редакторов</p>
    <img alt="Установка всех 3-х редакторов" height="600px" src="./images/T12.png"/>
</div>

### Part 7.1
<div style="text-align:center">
    <p>VIM (ESC + ":" + "q" + "w")</p>
    <img alt="VIM (ESC + ':' + 'q' + 'w')" height="600px" src="./images/T13.png"/>
</div>

<div style="text-align:center">
    <p>NANO (CTRL + X -> CTRL + Y -> ENTER)</p>
    <img alt="NANO (CTRL + X -> CTRL + Y -> ENTER)" height="600px" src="./images/T14.png"/>
</div>

<div style="text-align:center">
    <p>JOE (CTRL + K -> CTRL + X)</p>
    <img alt="JOE (CTRL + K -> CTRL + X)" height="600px" src="./images/T15.png"/>
</div>

### Part 7.2

<div style="text-align:center">
    <p>VIM (I + "ENTER MESSAGE" + ESC + ":" + "q" + "!")</p>
    <img alt="VIM (I + 'ENTER MESSAGE' + ESC + ':' + 'q' + '!')" height="600px" src="./images/T16.png"/>
</div>

<div style="text-align:center">
    <p>NANO ("ENTER MESSAGE" -> CTRL + X -> CTRL + N)</p>
    <img alt="NANO ('ENTER MESSAGE' -> CTRL + X -> CTRL + N)" height="600px" src="./images/T17.png"/>
</div>

<div style="text-align:center">
    <p>JOE (CTRL + C -> Y)</p>
    <img alt="JOE (CTRL + C -> Y)" height="600px" src="./images/T18.png"/>
</div>

### Part 7.3

<div style="text-align:center">
    <p>VIM (ESC + ":s/.old_word./.new_word.")</p>
    <img alt="VIM (ESC + ':s/.old_word./.new_word.')" height="600px" src="./images/T19.png"/>
</div>

<div style="text-align:center">
    <p>NANO (CTRL + \ -> .old_word. -> ENTER -> .new_word. -> ENTER -> Y)</p>
    <img alt="NANO (CTRL + \ -> .old_word. -> ENTER -> .new_word. -> ENTER -> Y)" height="600px" src="./images/T20.png"/>
</div>

<div style="text-align:center">
    <p>JOE (CTRL + K + F -> .old_word. -> ENTER -> R -> ENTER -> .new_word. -> ENTER -> Y -> ENTER)</p>
    <img alt="JOE (CTRL + K + F -> .old_word. -> ENTER -> R -> ENTER -> .new_word. -> ENTER -> Y -> ENTER)" height="600px" src="./images/T21.png"/>
</div>

## Part 8. Installing and basic setup of the SSHD service

<div style="text-align:center">
    <p>Установка и настройка SSHD</p>
    <img alt="Установка и настройка SSHD" height="600px" src="./images/T22.png"/>
</div>

<div style="text-align:center">
    <p>Проверяем наличие процесса sshd</p>
    <img alt="Проверяем наличие процесса sshd" height="600px" src="./images/T23.png"/>
    <p>ps - показывает процессы</p>
    <p>ps u - показывает процессы пользователя</p>
    <p>ps u -A - показывает абсолютно все процессы пользователя</p>
</div>

<div style="text-align:center">
    <p>Вывод netstat -tan</p>
    <img alt="Вывод netstat -tan" height="600px" src="./images/T24.png"/>
    <p>-t - вывод только tcp портов</p>
    <p>-a - все порты (как я понял как активные так и пассивные)</p>
    <p>-n - вывод ip в числовом виде (localhost -> 127.0.0.1)</p>
    <p>protocol - протокол по которому происходит общение</p>
    <p>Recv-Q - Счётчик байт не скопированных программой пользователя из этого сокета.</p>
    <p>Send-Q - Счётчик байтов, не подтверждённых удалённым узлом.</p>
    <p>Local address - Адрес и номер порта локального конца сокета. Если не указана опция --numeric (-n), адрес сокета преобразуется в каноническое имя узла (FQDN), и номер порта преобразуется в соответствующее имя службы.</p>
    <p>Foreign address - Адрес и номер порта удалённого конца сокета. Аналогично "Local Address."</p>
    <p>protocol - протокол по которому происходит общение</p>
    <p>state - состояние программы на этом порту</p>
    <p>0.0.0.0 - абсолютно любой адрес сети</p>
</div>

## Part 9. Installing and using the top, htop utilities

<div style="text-align:center">
    <p>TOP</p>
    <img alt="TOP" height="600px" src="./images/T28.png"/>
</div>
<p>Parameters:</p>
<li>uptime - 5 min</li>
<li>users - 1</li>
<li>total system load - 0.00 / 1m , 0.06 / 5m, 0.04 / 15m</li>
<li>total process -  95</li>
<li>CPU Usage - 0%</li>
<li>Memory Usage - 150 + 336 cached</li>
<li>PID memory - 1</li>
<li>PID cpu - (null)</li>

<div style="text-align:center">
    <p>HTOP - sorted PID</p>
    <img alt="HTOP - sorted PID" height="600px" src="./images/T29.png"/>
</div>

<div style="text-align:center">
    <p>HTOP - sorted CPU</p>
    <img alt="HTOP - sorted CPU" height="600px" src="./images/T30.png"/>
</div>

<div style="text-align:center">
    <p>HTOP - sorted Memory</p>
    <img alt="HTOP - sorted Memory" height="600px" src="./images/T31.png"/>
</div>

<div style="text-align:center">
    <p>HTOP - sorted Time</p>
    <img alt="HTOP - sorted Time" height="600px" src="./images/T32.png"/>
</div>

<div style="text-align:center">
    <p>HTOP - filter: sshd</p>
    <img alt="HTOP - filter: sshd" height="600px" src="./images/T33.png"/>
</div>

<div style="text-align:center">
    <p>HTOP - search: syslog</p>
    <img alt="HTOP - search: syslog" height="600px" src="./images/T34.png"/>
</div>

<div style="text-align:center">
    <p>HTOP - with gashi style</p>
    <img alt="HTOP - with gashi style" height="600px" src="./images/T35.png"/>
</div>

## Part 10. Using the fdisk utility

<div style="text-align:center">
    <p>sudo fdisk -l</p>
    <img alt="sudo fdisk -l" height="600px" src="./images/T36.png"/>
    <p>Name - VBOX HARDDISK</p>
    <p>SIZE - 10 GiB</p>
    <p>Count sectors - 20971520</p>
    <p>Swap size (Файл подкачки) - EMPTY</p>
</div>

## Part 11. Using the df utility

<div style="text-align:center">
    <p>commnad: df</p>
    <img alt="commnad: df" height="600px" src="./images/T37.png"/>
    <p>ALL SIZE - 9336140 kbyte</p>
    <p>USED size - 2659336 byte</p>
    <p>Available size - 6182728 byte</p>
    <p>Percent - 31%</p>
</div>

<div style="text-align:center">
    <p>commnad: df -Th</p>
    <img alt="commnad: df -Th" height="600px" src="./images/T38.png"/>
    <p>ALL SIZE - 9.0 GiB</p>
    <p>USED size - 2.6 GiB</p>
    <p>Available size - 5.9 GiB</p>
    <p>Percent - 31%</p>
    <p>Type system - ext4</p>
</div>

## Part 12. Using the du utility

<div style="text-align:center">
    <p>Output the size of the /home, /var, /var/log folders (in bytes, in human readable format)</p>
    <img alt="Output the size of the /home, /var, /var/log folders (in bytes, in human readable format)" height="600px" src="./images/T39.png"/>
</div>

<div style="text-align:center">
    <p>Output the size of all contents in /var/log (not the total, but each nested element using *)</p>
    <img alt="Output the size of all contents in /var/log (not the total, but each nested element using *)" height="600px" src="./images/T40.png"/>
</div>

## Part 13. Installing and using the ncdu utility

<div style="text-align:center">
    <p>Output the size of the /home, /var, /var/log folders.</p>
    <img alt="Output the size of the /home" height="600px" src="./images/T41.png"/>
</div>

<div style="text-align:center">
    <img alt="/var" height="600px" src="./images/T42.png"/>
</div>

<div style="text-align:center">
    <img alt="/var/log" height="600px" src="./images/T43.png"/>
</div>

## Part 14. Working with system logs

<div style="text-align:center">
    <p>Write the last successful login time, user name and login method in the report.</p>
    <img alt="Write the last successful login time, user name and login method in the report." height="600px" src="./images/T44.png"/>
    <p>user - gashi_mushi, time - 12:50, method systemd-logind</p>
</div>

<div style="text-align:center">
    <p>Restart service</p>
    <img alt="Restart service" height="600px" src="./images/T45.png"/>
</div>

## Part 15. Using the CRON job scheduler

<div style="text-align:center">
    <p>Using the job scheduler, run the uptime command in every 2 minutes.</p>
    <img alt="Using the job scheduler, run the uptime command in every 2 minutes." height="600px" src="./images/T46.png"/>
</div>

<div style="text-align:center">
    <p>Remove all cron</p>
    <img alt="Remove all cron" height="600px" src="./images/T47.png"/>
</div>