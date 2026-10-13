/* func_ov110_0229e0f8 @ 0x0229e0f8, 0x54 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;
extern void func_ov002_02208098(void *p, int a);
extern void func_ov002_02207ce4(void *p, int size);
extern void func_ov002_02207d00(void *p);
extern int func_ov110_0229c2c8(void *p, int a);
extern int func_ov110_0229cf54(void *p);
extern void func_ov110_0229d770(void *p, unsigned char b);

void func_ov110_0229e0f8(void *p)
{
    if (data_021fbdd8 == 0) {
        func_ov002_02208098(p, 0);
        func_ov002_02207ce4((char *) p + 0x21f8, 0x3c);
    } else {
        if (func_ov110_0229c2c8(p, 4) != 0 && func_ov110_0229cf54(p) != 0) {
            func_ov110_0229d770(p, *(unsigned char *) ((char *) p + 0xf2));
        } else {
            func_ov002_02207d00((char *) p + 0x21f8);
        }
    }
}
