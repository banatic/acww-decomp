/* func_020c327c @ 0x020c327c, 0xc4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern int func_02099020(int a, int b);
extern int func_0202ea80(int a, int b);
extern void func_020c3348(void *p, int k);
extern unsigned int func_020c3340(void *p);
extern void func_02098ff8(int a, int b);
extern int func_020644cc(int x);
extern int data_020e7d0c;

typedef struct {
    int val;
    unsigned char c;
} UnkStruct_020c327c;

void func_020c327c(void *p, UnkStruct_020c327c *out)
{
    int a;
    unsigned int idx;

    a = func_020984e8();
    out->val = data_020e7d0c;

    if (func_02099020(a, 0x33) == 0) {
        if (func_02099020(a, 0x39) == 0) {
            func_020c3348(p, 0);
        } else {
            func_020c3348(p, 1);
        }
    } else {
        if (func_0202ea80(0x2a, 0) == 0) {
            func_020c3348(p, 2);
        } else {
            func_020c3348(p, 3);
        }
    }

    idx = func_020c3340(p);
    switch (idx) {
        case 0:
            func_02098ff8(a, 0x33);
            out->c = 0;
            break;
        case 1:
            func_02098ff8(a, 0x33);
            out->c = (unsigned char) (func_020644cc(3) + 1);
            break;
        case 2:
            out->c = (unsigned char) (func_020644cc(3) + 4);
            func_0202ea80(0x2a, 1);
            break;
        case 3:
            out->c = (unsigned char) (func_020644cc(3) + 7);
            break;
    }
}
