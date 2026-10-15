/* func_020c247c @ 0x020c247c, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_020c80f8;
extern unsigned int data_020c814c;

void func_0201ad18(void *a, int b, int c, int d, void *e, int f, int g, int h);
int func_02019c20(void *a, int b, int c, int d, int e, int f);

extern unsigned char data_021fbee8[];

int func_020c247c(char *self)
{
    func_0201ad18(self + 0x3b0, 0, 0, 0, (void *) data_021fbee8, 4, data_020c814c, 1);
    func_02019c20(self + 0x564, 1, 0xab, 1, data_020c80f8, 0);
    return 1;
}
