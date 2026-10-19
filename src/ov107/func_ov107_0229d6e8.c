/* func_ov107_0229d6e8 @ 0x0229d6e8, 0x38 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *addr);
extern void *func_ov002_0220a720(void *addr, int n);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_0200467c(int cmd);

void func_ov107_0229d6e8(char *param)
{
    if (func_0208e484(param + 0x22b4)) {
        func_ov002_0220a720(param + 0x2828, 9);
        func_ov002_02208098((void *) (param), 0xf);
        func_0200467c(0x28);
    }
}
