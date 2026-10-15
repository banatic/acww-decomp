/* func_ov048_02262618 @ 0x02262618, 0x40 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a0194(void);
extern void func_020a01b4(void);
extern void func_02074b44(int, int, int);

void func_ov048_02262618(int p1, unsigned int p2, int p3)
{
    switch (p2) {
        case 0:
            break;
        case 3:
        case 4:
            func_020a0194();
            break;
        case 1:
        case 2:
            func_020a01b4();
            break;
    }
    func_02074b44(p2, 4, p3);
}
