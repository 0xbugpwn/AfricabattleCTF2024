FROM kalilinux/kali-rolling

LABEL author="BUG|PWN TEAM"
LABEL desc="challenge author: RAVEN"

RUN apt-get update
RUN apt-get install -y qemu-user socat libc6-arm64-cross gdb-multiarch

RUN useradd -d /home/ctf/ -m -p ctf -s /bin/bash ctf
RUN echo "ctf:ctf" | chpasswd

WORKDIR /home/ctf

COPY source .
RUN chown -R ctf:ctf /home/ctf
RUN chmod +x /home/ctf/kami
RUN mv /home/ctf/libc.so.6 /usr/aarch64-linux-gnu/lib/libc.so.6
RUN mv /home/ctf/ld-linux-aarch64.so.1 /usr/aarch64-linux-gnu/lib/ld-linux-aarch64.so.1

USER ctf
EXPOSE 1000

ENTRYPOINT socat TCP-LISTEN:1000,reuseaddr,fork EXEC:"stdbuf -i0 -o0 -e0 qemu-aarch64 -L /usr/aarch64-linux-gnu ./kami && /bin/bash"
