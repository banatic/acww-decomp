/* func_ov054_022620cc @ 0x022620cc, 0x64 bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
 */

struct S020682e0 {
    int pad_00;
    int unk_04;
};
extern struct S020682e0 *func_020682e0(int);
extern void func_020b22f4(void);
extern int func_0204e414(void);
extern int func_0204e188(int, void *, void *, void *);
extern int func_020b5e10(void);
extern void func_020b63f4(int, int, void *, int, int, int, int);
extern void func_ov054_02262528(void *, int);

int func_ov054_022620cc(void *obj)
{
    int local2;
    int local3;
    int t;
    struct {
        int a;
        int b;
        int c;
    } local1;

    if (func_020682e0(0)->unk_04 == 5) {
        func_020b22f4();
        t = func_0204e414();
        if (t != 0) {
            if (func_0204e188(t, &local1.a, &local2, &local3) != 0) {
                local1.c += 0x1000;
                func_020b63f4(func_020b5e10(), 0, &local1.a, 0x0ec00000, 0, 2, 2);
            }
        }
        func_ov054_02262528(obj, 5);
    }
    return 1;
}
