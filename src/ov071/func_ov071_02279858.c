/* func_ov071_02279858 @ 0x02279858, 0xa0 bytes, Thumb, module ov071
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_020c80f8;
extern void *data_020c814c;
extern int func_02096190(int);
extern void func_02019c20(void *p, int a, int b, int c, int d, int e);
extern void func_02013c0c(void *p);
extern void func_0201ad18(void *p, int a, int b, int c, void *d, int e, void *f, int g);

extern unsigned char data_021fbee8[];

int func_ov071_02279858(void *self)
{
    *((unsigned int *) ((char *) self + 0x734)) = func_02096190(4);
    {
        unsigned int *src = (unsigned int *) ((char *) self + 0x5c);
        *((unsigned int *) ((char *) self + 0x738)) = *((unsigned int *) ((char *) self + 0x5c));
        *((unsigned int *) ((char *) self + 0x73c)) = src[1];
        *((unsigned int *) ((char *) self + 0x740)) = src[2];
    }
    func_02019c20((char *) self + 0x564, 1, 0xdf, 1, data_020c80f8, 0);
    func_02013c0c((char *) self + 0x558);
    func_0201ad18((char *) self + 0x3b0, 1, 0, 0, (void *) data_021fbee8, 4, data_020c814c, 1);
    *((unsigned char *) self + 0x729) = 0;
    return 1;
}
