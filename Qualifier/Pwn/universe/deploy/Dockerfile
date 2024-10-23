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
RUN chmod +x ./universe
RUN export TERM=xterm
RUN mv flag.txt /

USER ctf
EXPOSE 1004


ENTRYPOINT socat -T10 TCP-LISTEN:1004,reuseaddr,fork EXEC:/home/ctf/universe
