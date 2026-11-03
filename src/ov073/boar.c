/* boar: 2 functions, module ov073
 * mwccarm 1.2/base -O4,s
 * func_ov073_02278a28 @ 0x02278a28, 0x2c bytes, Thumb
 * func_ov073_02278a00 @ 0x02278a00, 0x28 bytes, Thumb
 */

extern void *func_ov073_02278e9c(void *p);
extern void *func_0202ee5c(void *p);
extern void func_020edf54(void *p);
extern unsigned char data_ov073_02279b00[];

void *func_ov073_02278a28(void *p)
{
    *(void **) p = ((int *) data_ov073_02279b00);
    func_ov073_02278e9c((char *) p + 0x658);
    func_0202ee5c(p);
    func_020edf54(p);
    return p;
}

void *func_ov073_02278a00(void *this)
{
    *(void **) this = (void *) data_ov073_02279b00;
    func_ov073_02278e9c((char *) this + 0x658);
    func_0202ee5c(this);
    return this;
}
