/* func_ov137_0229cd20 @ 0x0229cd20, 0x3c bytes, Thumb, module ov137
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;
extern unsigned char data_021f6c54;
extern void func_ov134_02299b18(void *, unsigned char);
extern void func_ov134_02299a84(void *);
extern void func_ov002_02208098(void *, int);

void func_ov137_0229cd20(void *p)
{
    if (data_021fbdd8) {
        func_ov134_02299b18((char *) p + 0x2c4, data_021f6c54);
    } else {
        func_ov134_02299a84((char *) p + 0x2c4);
        func_ov002_02208098(p, 1);
    }
}
