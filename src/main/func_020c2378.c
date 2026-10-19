/* func_020c2378 @ 0x020c2378, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020c814c;
extern void func_0201ad18(void *a, int b, int c, int d, void *e, int f, int g, int h);
extern int func_02016104(void *a);
extern int func_0201c314(void *a, int b);
extern void func_0201b38c(void *a, int b);
extern void func_0201b388(void *a, int b);
extern int func_020147fc(void *a, int b, int c, int d);

extern unsigned char data_021fbee8[];

int func_020c2378(void *self)
{
    int ret;
    int size;

    func_0201ad18((char *) self + 0x3b0, 1, 0, 0, (void *) data_021fbee8, 4, data_020c814c, 1);
    size = func_02016104((char *) self + 0x658);
    ret = 0;
    if (size != 0) {
        ret = func_0201c314(self, size);
    }
    func_0201b38c((char *) self + 0x2a0, 0xac);
    func_0201b388((char *) self + 0x2a0, 0xac);
    func_020147fc((char *) self + 0x618, 0, ret, 0);
    return 1;
}
