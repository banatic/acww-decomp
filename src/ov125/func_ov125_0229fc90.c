/* func_ov125_0229fc90 @ 0x0229fc90, 0x74 bytes, Thumb, module ov125
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_ov002_02208d30(char *p, int a);
extern unsigned int func_0206fca4(unsigned int a);
extern void func_ov002_02208d4c(char *p, int a, int b);

void func_ov125_0229fc90(char *self)
{
    unsigned int v;
    v = func_0206fca4(func_ov002_02208d30(self + 0x568, 1)) - 4;
    switch (v) {
        case 1:
        case 4:
        case 5:
            func_ov002_02208d4c(self + 0x568, 0x91, 0);
            break;
        case 0:
        case 3:
        case 6:
            func_ov002_02208d4c(self + 0x568, 0x72, 0);
            break;
        case 2:
        default:
            func_ov002_02208d4c(self + 0x568, 0x28, 0);
            break;
    }
    func_ov002_02208d4c(self + 0x568, 2, 1);
}
