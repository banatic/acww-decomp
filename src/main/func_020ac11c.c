/* func_020ac11c @ 0x020ac11c, 0x2a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200467c(int cmd);

void func_020ac11c(unsigned char *param0, unsigned char param1, int param2)
{
    unsigned char *ptr;
    unsigned char val;

    ptr = param0;
    val = param1;

    if (param2 != 0) {
        if (param0[0x74] == 0) {
            if (val != 0) {
                func_0200467c(0x3b);
            }
        }
    }

    param0[0x74] = val;
}
