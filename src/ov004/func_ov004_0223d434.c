/* func_ov004_0223d434 @ 0x0223d434, 0xf8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b67d4(void);
extern int func_020b6680(void);
extern int func_ov004_0223c10c(void);
extern unsigned int func_ov004_0223c130(void);
extern int func_ov004_0223cec4(void *, int);
extern void *func_ov004_0223cd50(void);
extern void func_ov004_0223cd04(void *);
extern void *func_ov004_0223cb10(void);
extern void func_ov004_0223c7b8(void *);
extern int func_020b66d8(void);
extern int func_0209d180(void *object, unsigned int count, int a, int b, int c, int (*allocate)(int, int),
                         void (*cleanup)(void));
extern void func_ov004_0223c108(void);
extern void func_ov004_0223aad4(void *);
extern void func_ov004_0223b158(void *);
extern void *func_ov004_0223d03c(void);
extern void func_ov004_0223d248(void *);
extern void func_ov004_0223c080(void);
extern int func_0205ca98(int size, int heapword);
extern void func_0205ca7c(void);
extern char data_ov004_022595b8;
extern char data_ov004_022595b4;
extern char data_ov004_022595c4;
extern void *data_ov004_022595c0;
extern char data_ov004_02256188;
extern char data_ov004_02259698;

int func_ov004_0223d434(char *self)
{
    int sz;
    volatile unsigned int outgoing[4];
    register unsigned int count;
    if (func_020b67d4() != 0 || func_020b6680() != 0) {
        data_ov004_022595b8 = 1;
    }
    self[0x2a9] = 1;
    self[0x2a8] = 0;
    *(int *) (self + 0x2ac) = 0;
    self[0x2b0] = 0;
    data_ov004_022595b4 = func_ov004_0223c10c();
    func_ov004_0223cec4(&data_ov004_022595c4, func_ov004_0223c130());
    data_ov004_022595c0 = self;
    func_ov004_0223cd04(func_ov004_0223cd50());
    func_ov004_0223c7b8(func_ov004_0223cb10());
    sz = 0x1cc4;
    if (func_020b66d8() != 0) {
        sz = 0x1c00;
    }
    count = func_ov004_0223c130();
    outgoing[0] = sz;
    outgoing[1] = (unsigned int) func_0205ca98;
    outgoing[2] = (unsigned int) func_0205ca7c;
    outgoing[3] = (unsigned int) &data_ov004_02256188;
    asm {
        ldr r0, =data_ov004_02259698
        mov r1, count
        ldr r2, =0x2000
        mov r3, #0x80
        bl func_0209d180
        mov r0, self
    }
    func_ov004_0223c108();
    if (func_ov004_0223c130() > 1) {
        func_ov004_0223aad4(self + 0x64);
    }
    func_ov004_0223b158(self + 0x1c4);
    func_ov004_0223d248(func_ov004_0223d03c());
    asm {
        mov r0, self
    }
    func_ov004_0223c080();
    return 1;
}
