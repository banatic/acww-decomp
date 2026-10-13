/* func_ov146_02299b80 @ 0x02299b80, 0x28 bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e930(char *p);
extern void func_ov002_0220a580(char *p);

int func_ov146_02299b80(char *p)
{
    if (func_0208e930(p + 0x1fb4) != 0) {
        func_ov002_0220a580(p + 0x1fb4);
        return 1;
    }
    return 0;
}
