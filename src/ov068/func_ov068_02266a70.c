/* func_ov068_02266a70 @ 0x02266a70, 0x30 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_02227608(int a, int b);
extern int func_020ea990(int a, int b);

int func_ov068_02266a70(int unused, int p1, int p2, int p3, int p4)
{
    if (func_ov003_02227608(p1, p2) != 0 && func_020ea990(p3, p1) < p4) {
        return 1;
    }
    return 0;
}
