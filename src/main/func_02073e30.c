/* func_02073e30 @ 0x02073e30, 0xd0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_02073044(void);
extern int func_020ebeb8(int a, int b, int c, int d, int e, int f, unsigned short g, int h, int i, int j, unsigned short k,
                         int l);
extern int func_02073d70(void *a);
extern int func_02077b28(int a);
extern void func_02073180(void *a, int b);
extern int func_02077a64(void);
extern void func_02073168(void *a, int b);

int func_02073e30(void *p1, int p2, int p3, int p4, int p5, int p6, unsigned short p7, int p8, int p9, unsigned short p10)
{
    func_02073044();
    if (func_020ebeb8(p2, p3, p4, 0, p5, p6, p7, 0, p8, p9, p10, 0) != 0) {
        if (func_02073d70(p1) != 2) {
            if (p2 != 0 || p5 != 0 || p8 != 0) {
                if (p3 != 0 || p6 != 0 || p9 != 0) {
                    if (p2 != 0 && p3 != 0) {
                        func_02077b28(p2);
                    }
                    if (p5 != 0 && p6 != 0) {
                        func_02077b28(p5);
                    }
                    if (p8 != 0 && p9 != 0) {
                        func_02077b28(p8);
                    }
                    func_02073180(p1, 0);
                    func_02077a64();
                    func_02073168(p1, 0x258);
                }
            }
        } else {
            func_02073180(p1, 0);
            func_02073168(p1, 0);
        }
        return 1;
    }
    return 0;
}
