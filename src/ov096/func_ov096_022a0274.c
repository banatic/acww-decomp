/* func_ov096_022a0274 @ 0x022a0274, 0x78 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209d8c(char *p);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern int func_ov096_0229f800(void *p, unsigned char b);
extern int func_ov096_0229c2fc(void *p, int n);
extern int func_ov096_0229f290(void *p, unsigned char b);
extern int func_ov096_0229f200(void *p, unsigned char b);
extern void func_ov096_022a0218(void *p);
extern void func_ov096_0229ea34(void *p);

struct UnkStruct_022a0274 {
    char pad_00[0xa4];
    int a4;
    int a8;
    char pad_AC[8];
    unsigned char b4;
};

void func_ov096_022a0274(struct UnkStruct_022a0274 *p)
{
    if (func_ov002_02209d8c((char *) p + 0x24e8) != 0) {
        if (func_ov096_0229f800(p, p->b4) != 0 || func_ov096_0229c2fc(p, 0x2000) != 0) {
            p->a4 = func_ov096_0229f290(p, p->b4);
            p->a8 = func_ov096_0229f200(p, p->b4);
            func_ov002_02208098((void *) (p), 0x1c);
            return;
        } else {
            func_ov096_022a0218(p);
            return;
        }
    } else {
        func_ov096_0229ea34(p);
        return;
    }
}
