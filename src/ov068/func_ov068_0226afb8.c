/* func_ov068_0226afb8 @ 0x0226afb8, 0xc8 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov068_0226cfd4(unsigned char *);
extern void func_02013aac(unsigned char *);
extern int func_0201ce18(unsigned char *);
extern int func_020147e0(void *, int, int);
extern void func_ov068_02266c34(void *, void *, int, int, int, const void *, int, int, int);
extern int func_02016104(void *);
extern int func_0201c314(unsigned char *, int);
extern int func_020147fc(void *, int, int, int);

extern const int data_021fbee8[];
extern int data_020c814c;

int func_ov068_0226afb8(void *self, unsigned char *obj)
{
    int a, b;

    func_ov068_0226cfd4(obj);
    func_02013aac(obj);
    if (func_0201ce18(obj) != 0) {
        func_020147e0(obj + 0x618, 1, 0);
        goto out;
    }
    if (obj[0xa04] != 0) {
        func_020147e0(obj + 0x618, 0, 0);
        func_ov068_02266c34(obj + 0x898, obj, 1, 0, 0, data_021fbee8, 4, data_020c814c, 1);
        goto out;
    }
    a = func_02016104(obj + 0x680);
    b = 0;
    if (a != 0) {
        b = func_0201c314(obj, a);
    }
    func_ov068_02266c34(obj + 0x898, obj, 1, 0, 0, data_021fbee8, 4, data_020c814c, 1);
    func_020147fc(obj + 0x618, 0, b, 0);
out:
    return 1;
}
