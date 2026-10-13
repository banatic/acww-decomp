/* func_020540c0 @ 0x020540c0, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200240c(void);
extern void func_02002f68(void);

extern unsigned char data_021c8c9c[];
extern unsigned char data_021c8ca0[];

void func_020540c0(void)
{
    unsigned int *addr0;
    unsigned int *addr1;
    unsigned int value;

    addr0 = (unsigned int *) data_021c8ca0;
    addr1 = (unsigned int *) data_021c8c9c;
    value = 0;

    *addr0 = value;
    *addr1 = value;

    func_0200240c();
    func_02002f68();
}
