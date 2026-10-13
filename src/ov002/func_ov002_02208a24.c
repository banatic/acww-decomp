/* func_ov002_02208a24 @ 0x02208a24, 0x52 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void func_02066514(int);
extern void func_02066560(int, int);
extern void func_0206658c(int, int);

int func_ov002_02208a24(int unused, int data, unsigned int type)
{
    switch (type) {
        case 0xf:
            return 3;
        case 0xe:
            return 2;
        case 0xd:
            func_02066514(data);
            return 1;
        default:
            if (type >= 1 && type < 5) {
                func_02066560(data, type - 1);
                return 1;
            } else if (type >= 5 && type < 0xd) {
                func_0206658c(data, type - 5);
                return 1;
            } else {
                return 0;
            }
    }
}
