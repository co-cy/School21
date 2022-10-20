FROM nginx

COPY nginx/nginx.conf /etc/nginx/nginx.conf

WORKDIR /home/fcgi_server
COPY server.c ./server.c
COPY start.sh ./start.sh

RUN apt-get update -y && \
    apt-get install -y gcc spawn-fcgi libfcgi-dev && \
    rm -rf /var/lib/apt/lists; \
    gcc server.c -lfcgi -o server; \
    usermod -aG sudo nginx

USER nginx

ENTRYPOINT ["bash", "./start.sh"]
