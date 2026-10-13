/* func_0205d5b0 @ 0x0205d5b0, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205d4e8(void *self);
extern void func_020e9b9c(void);
extern int data_021c9af4;

void func_0205d5b0(void *self)
{
    volatile unsigned char scratch[8];
    int i;

    (void) &scratch;
    func_0205d4e8((char *) self + 0x3c);
    for (i = 0; i < 10; i++) {
        ((int *) self)[i] = 0;
        *(unsigned short *) ((char *) self + i * 2 + 0x28) = 0xfff1;
    }
    if (data_021c9af4 != 0) {
        func_020e9b9c();
    }
}
