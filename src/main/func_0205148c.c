/* func_0205148c @ 0x0205148c, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021c8194;
extern void func_02050e24(void);
extern int func_020e9fc8(int x);
extern void func_02051758(const void *addr);

extern unsigned char data_021c81d4[];
extern unsigned char data_021c8230[];
extern unsigned char data_021c828c[];
extern unsigned char data_021c82e8[];

void func_0205148c(void)
{
    if (data_021c8194 != 0) {
        func_02050e24();
        func_020e9fc8(data_021c8194);
        data_021c8194 = 0;
    }
    func_02051758((const void *) data_021c8230);
    func_02051758((const void *) data_021c828c);
    func_02051758((const void *) data_021c82e8);
    func_02051758((const void *) data_021c81d4);
}
