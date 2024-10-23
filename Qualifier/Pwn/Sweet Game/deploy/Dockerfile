FROM ubuntu:latest

LABEL author="BUG|PWN TEAM"
LABEL desc="challenge author: RAVEN"

RUN apt update
RUN apt install -y socat

RUN useradd -d /home/ctf/ -m -p ctf -s /bin/bash ctf
RUN echo "ctf:ctf" | chpasswd

WORKDIR /home/ctf

COPY source .
RUN chown -R ctf:ctf /home/ctf
RUN chmod +x ./sweet_game

USER ctf
EXPOSE 1001

ENTRYPOINT socat TCP-LISTEN:1001,reuseaddr,fork EXEC:"stdbuf -i0 -o0 -e0 ./sweet_game && /bin/bash"
