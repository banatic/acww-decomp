/* func_ov135_0229cdb4 @ 0x0229cdb4, 0x3c bytes, Thumb, module ov135
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov134_02299af0(void *p0, unsigned char p1);
extern void func_ov134_02299a84(void *p0);
extern void func_ov002_02208098(void *p0, int p1);

extern unsigned char data_021fbdd8;
extern unsigned char data_021f6c54;

void func_ov135_0229cdb4(void *p0)
{
    if (data_021fbdd8 != 0) {
        func_ov134_02299af0((char *) p0 + 0x2c8, data_021f6c54);
    } else {
        func_ov134_02299a84((char *) p0 + 0x2c8);
        func_ov002_02208098(p0, 3);
    }
}
