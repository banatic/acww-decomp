/* func_ov075_0227944c @ 0x0227944c, 0x6c bytes, Thumb, module ov075
 * mwccarm 1.2/base -O4,s
 */

extern void func_0201ad18(void *a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8);
extern int func_02019c20(void *a1, int a2, int a3, int a4, int a5, int a6);
extern void func_0201b38c(void *a1, int a2);
extern int data_020c814c;
extern unsigned short data_020c80f8;

extern unsigned char data_021fbee8[];

int func_ov075_0227944c(void *param)
{
    func_0201ad18((char *) param + 0x3b0, 0, 0, 0, (unsigned int) data_021fbee8, 4, data_020c814c, 1);
    func_02019c20((char *) param + 0x564, 1, 0xef, 1, data_020c80f8, 0);
    func_0201b38c((char *) param + 0x2a0, 0xef);
    return 1;
}
