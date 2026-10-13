/* func_0205d7b8 @ 0x0205d7b8, 0xdc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct Work {
    int pad_00;
} data_021c9d7c;

extern int func_0205daac(int);
extern int func_0205d968(struct Work *, unsigned char, int);
extern int func_0205d978(struct Work *, int, int);
extern int func_0205d918(struct Work *, int);
extern int func_0205d908(struct Work *, int, int);
extern int func_0205dad0(void);
extern int func_0205dab8(void);
extern void MI_CpuCopy8(int, int, int);
extern void func_0205d950(struct Work *, unsigned char, int, int);
extern void func_0205d8f4(struct Work *, unsigned char, int, int);
extern int func_0205dad8(int);
extern int func_02064af4(int, int, int);

void func_0205d7b8(unsigned char *p, int a1, int a2, int a3)
{
    unsigned char b;
    int r4, sp8, sp4, r7, v;

    b = *p;
    r4 = func_0205daac(a1);
    if (a3 == 0) {
        if (func_0205d968(&data_021c9d7c, b, r4) == a1) {
            return;
        }
    }
    sp8 = func_0205d978(&data_021c9d7c, b, r4);
    if (r4 == 0) {
        sp4 = func_0205dad0();
    } else {
        sp4 = func_0205dab8() - func_0205dad0();
    }
    if (a2 != 0) {
        r7 = func_0205d918(&data_021c9d7c, a1);
        if (r7 != 9) {
            v = func_0205d978(&data_021c9d7c, r7, r4);
            r7 = func_0205d908(&data_021c9d7c, r7, r4);
            if (v != 0 && r7 != 0) {
                MI_CpuCopy8(v, sp8, r7);
                func_0205d950(&data_021c9d7c, b, r4, a1);
                func_0205d8f4(&data_021c9d7c, b, r4, r7);
            }
        }
    }
    r7 = func_02064af4(func_0205dad8(a1), sp8, sp4);
    if (r7 != 0) {
        func_0205d950(&data_021c9d7c, b, r4, a1);
        func_0205d8f4(&data_021c9d7c, b, r4, r7);
    }
}
