/* func_ov136_0229cd30 @ 0x0229cd30, 0x3c bytes, Thumb, module ov136
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;
extern unsigned char data_021f6c54;
extern void func_ov134_02299b18(char *, unsigned char);
extern int func_ov134_02299a84(char *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov136_0229cd30(char *p)
{
    if (data_021fbdd8 != 0) {
        func_ov134_02299b18(p + 0x2c4, data_021f6c54);
    } else {
        func_ov134_02299a84(p + 0x2c4);
        func_ov002_02208098((void *) (p), 3);
    }
}
