/* func_020aa5d0 @ 0x020aa5d0, 0x90 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020ac8c8(void *);
extern void func_020ab30c(void *);
extern void func_020aa2f4(void *);
extern void func_020ac444(void *);
extern void func_020ac424(void *);
extern void func_020ac3ec(void *);
extern void func_020ac8a8(void *);
extern int func_0209d368(void);
extern void func_020ac39c(void *, int, int);
extern void func_020ac384(void *);

void func_020aa5d0(void *self)
{
    int *p = (int *) self;
    p[2] = 1;
    func_020ac8c8((char *) self + 0xc);
    func_020ab30c((char *) self + 0x84);
    func_020aa2f4(self);
    func_020ac444((char *) self + 0xc);
    func_020ac424((char *) self + 0xc);
    func_020ac3ec((char *) self + 0xc);
    func_020ac8a8((char *) self + 0xc);
    asm {
        mov r0, #0x64
        mov r1, #2
    }
    p[0x2f] = func_0209d368() + 3;
    asm {
        mov r0, #0x64
        mov r1, #4
    }
    p[0x2d] = func_0209d368() + 5;
    asm {
        mov r0, #0x64
        mov r1, #5
    }
    p[0x2e] = func_0209d368() - 5;
    func_020ac39c((char *) self + 0xc, p[0x2d], p[0x2e]);
    func_020ac384((char *) self + 0xc);
}
