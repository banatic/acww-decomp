/* func_0205d724 @ 0x0205d724, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205c7b4(void);
extern void func_0205d5f0(void *);
extern void func_020e9abc(void);

extern unsigned char data_021c9af4[];
extern unsigned char data_021c9d1c[];

void func_0205d724(void)
{
    unsigned int *ptr;

    func_0205c7b4();
    func_0205d5f0((void *) data_021c9d1c);
    ptr = (unsigned int *) data_021c9af4;
    if (*ptr != 0) {
        func_020e9abc();
    }
}
