/* func_ov138_0229cd94 @ 0x0229cd94, 0x3c bytes, Thumb, module ov138
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov134_02299b18(void *p0, unsigned char p1);
extern int func_ov134_02299a84(void *p0);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern unsigned char data_021fbdd8;
extern unsigned char data_021f6c54;

void func_ov138_0229cd94(void *p0)
{
    if (data_021fbdd8) {
        func_ov134_02299b18((char *) p0 + 0x2c8, data_021f6c54);
    } else {
        func_ov134_02299a84((char *) p0 + 0x2c8);
        func_ov002_02208098((void *) (p0), 1);
    }
}
