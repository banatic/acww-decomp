/* func_ov135_0229cdf0 @ 0x0229cdf0, 0x3c bytes, Thumb, module ov135
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov134_02299b18(void *p, unsigned char c);
extern int func_ov134_02299a84(void *p);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

extern unsigned char data_021fbdd8;
extern unsigned char data_021f6c54;

void func_ov135_0229cdf0(void *p)
{
    if (data_021fbdd8) {
        func_ov134_02299b18((char *) p + 0x2c8, data_021f6c54);
    } else {
        func_ov134_02299a84((char *) p + 0x2c8);
        func_ov002_02208098((void *) (p), 3);
    }
}
