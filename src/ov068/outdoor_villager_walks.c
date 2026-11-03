/* outdoor_villager_walks: 3 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_0226afb8 @ 0x0226afb8, 0xc8 bytes, Thumb
 * func_ov068_0226af70 @ 0x0226af70, 0x48 bytes, Thumb
 * func_ov068_0226af6c @ 0x0226af6c, 0x2 bytes, Thumb
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
extern int func_02014868(void *);
extern void func_0201cc48(void *);
extern int func_0203e020(void *);
extern void func_0201ce5c(void *, int);
extern void func_0201ce44(void *, int);

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

void func_ov068_0226af70(unsigned char *arg0, char *arg1)
{
    if (func_02014868((char *) arg1 + 0x618) != 0) {
        return;
    }
    func_0201cc48((char *) arg1 + 0x83c);
    func_0203e020((char *) arg1);
    func_0201ce5c((char *) arg1, 0);
    func_0201ce44((char *) arg1, 0);
    arg0[0x1c] = 1;
}

void func_ov068_0226af6c(void *object, int event) {}
