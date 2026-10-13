/* func_ov128_0229c144 @ 0x0229c144, 0x78 bytes, Thumb, module ov128
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov127_02299b78(void *);
extern unsigned char func_ov127_02299d20(void *, unsigned char, unsigned char);
extern void func_ov127_02299c08(void *, int, int);
extern void func_ov128_0229bb20(void *);
extern void func_ov002_02208098(void *, int);

extern unsigned char data_021fbdd8; // at 0x021fbdd8
extern unsigned char data_021f6c60; // at 0x021f6c60
extern unsigned char data_021f6c5c; // at 0x021f6c5c

void func_ov128_0229c144(void *obj)
{
    if (!func_ov127_02299b78((char *) obj + 0x4a4)) {
        goto common;
    }
    if (!data_021fbdd8) {
        goto short_path;
    }
    {
        volatile unsigned char *p = (volatile unsigned char *) ((char *) obj + 0x2d6b);
        unsigned char v;

        *p = func_ov127_02299d20((char *) obj + 0x4a4, data_021f6c60, data_021f6c5c);
        v = *p;
        if (v == 4) {
            goto short_path;
        }
        func_ov127_02299c08((char *) obj + 0x4a4, v, 1);
        func_ov128_0229bb20(obj);
        func_ov002_02208098(obj, 1);
        return;
    }
short_path:
    func_ov002_02208098(obj, 0);
common:
    func_ov128_0229bb20(obj);
}
