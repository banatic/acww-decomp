/* func_02036be4 @ 0x02036be4, 0x140 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02036be4 UnkStruct_02036be4;

extern int func_02036648(UnkStruct_02036be4 *p, int flag);
extern int func_0203736c(int a, int b, int c, int d, int e, int f, int g);
extern void func_02036ab4(UnkStruct_02036be4 *p);
extern void func_02036b50(UnkStruct_02036be4 *p, int sel);
extern void func_02036a78(UnkStruct_02036be4 *p, int val);
extern void func_02036a5c(UnkStruct_02036be4 *p);

struct UnkStruct_02036be4 {
    char pad_00[0xe];
    unsigned short unk_0E;
};

void func_02036be4(UnkStruct_02036be4 *p, int flag)
{
    int a, sel;
    int res1, res2, res3, res4;
    int res5, res6, res7, res8;

    if (flag != 0) {
        a = func_02036648(p, flag);
        sel = 0xffff;

        res1 = func_0203736c(a, 0x17, 0, 0, 0x17, 0x1e, 0);
        res2 = func_0203736c(a, 0x17, 0x1e, 0, 0x17, 0x32, 0);
        res3 = func_0203736c(a, 0x17, 0x32, 0, 0x17, 0x37, 0);
        res4 = func_0203736c(a, 0x17, 0x37, 0, 0, 0, 0);

        if (res1) {
            sel = 0x31;
        } else if (res2) {
            sel = 0x32;
        } else if (res3) {
            sel = 0x33;
        } else if (res4) {
            sel = 0x34;
        }

        if (sel != 0xffff) {
            if (p->unk_0E != sel) {
                func_02036ab4(p);
                func_02036b50(p, sel);
            }
        } else {
            func_02036ab4(p);
        }

        res5 = func_0203736c(a, 0x17, 0x1d, 0x32, 0x17, 0x1e, 0);
        res6 = func_0203736c(a, 0x17, 0x31, 0x32, 0x17, 0x32, 0);
        res7 = func_0203736c(a, 0x17, 0x36, 0x32, 0x17, 0x37, 0);
        res8 = func_0203736c(a, 0x17, 0x3a, 0x32, 0, 0, 0);

        if (res5 || res6 || res7 || res8) {
            func_02036a78(p, 0xc8);
        } else {
            func_02036a5c(p);
        }
    } else {
        func_02036ab4(p);
        func_02036a5c(p);
    }
}
