FROM nginx

COPY ./nginx/nginx.conf /etc/nginx/nginx.conf

WORKDIR /home/fcgi_server
COPY ./server.c ./server.c
COPY ./start.sh ./start.sh

RUN apt-get update; \
    apt-get upgrade; \
    apt-get install -y gcc spawn-fcgi libfcgi-dev; \
    gcc server.c -lfcgi -o server

ENTRYPOINT ["bash", "./start.sh"]
