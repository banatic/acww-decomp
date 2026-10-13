/* func_ov117_02299ab8 @ 0x02299ab8, 0x24 bytes, Thumb, module ov117
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov117_02299c9c(unsigned int);
extern void func_ov117_02299c68(unsigned int);

void func_ov117_02299ab8(unsigned int r0, int r1)
{
    if (r1 == 0) {
        func_ov117_02299c9c(r0 + 0x2000);
    } else {
        func_ov117_02299c68(r0 + 0x2000);
    }
}
