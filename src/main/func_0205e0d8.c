/* func_0205e0d8 @ 0x0205e0d8, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205df54(unsigned int);
extern void func_0205c5a0(void);

extern unsigned char data_021c9e68[];

void func_0205e0d8(void)
{
    unsigned int sp;
    sp = (unsigned int) data_021c9e68;
    func_0205df54(sp);
    func_0205c5a0();
}
