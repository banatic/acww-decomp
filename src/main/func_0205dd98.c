/* func_0205dd98 @ 0x0205dd98, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0205c760(int);
extern void func_0205dd10(int);
extern int func_020e9abc(void *);

extern unsigned char data_021c9af0[];

extern unsigned char data_021c9e24[];

void func_0205dd98(int val)
{
    int *ptr;

    func_0205c760(val);
    func_0205dd10((unsigned int) data_021c9e24);
    ptr = (int *) data_021c9af0;
    val = *ptr;
    if (val != 0) {
        func_020e9abc((void *) val);
    }
}
