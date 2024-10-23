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
RUN chmod +x ./universe2

USER ctf
EXPOSE 1006


ENTRYPOINT socat -T10 TCP-LISTEN:1006,reuseaddr,fork EXEC:/home/ctf/universe2
