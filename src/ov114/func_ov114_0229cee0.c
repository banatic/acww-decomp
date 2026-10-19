/* func_ov114_0229cee0 @ 0x0229cee0, 0x38 bytes, Thumb, module ov114
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov114_0229cf58(unsigned char *p);
extern void func_0200467c(int cmd);

int func_ov114_0229cee0(unsigned char *p)
{
    if (p[0x12b5] != 0) {
        p[0x12b5]--;
        p[0x12af] = 5;
        func_ov114_0229cf58(p);
        func_0200467c(0x39);
        return 1;
    } else {
        return 0;
    }
}
