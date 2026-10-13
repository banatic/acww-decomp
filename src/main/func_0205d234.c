/* func_0205d234 @ 0x0205d234, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205c6b0(void);
extern void func_0205d12c(void *);
extern void func_020e9abc(void);

extern int data_021c9ae8;
extern unsigned char data_021c9c2c[];

void func_0205d234(void)
{
    func_0205c6b0();
    func_0205d12c((void *) data_021c9c2c);
    if (data_021c9ae8) {
        func_020e9abc();
    }
}
