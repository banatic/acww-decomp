/* func_ov047_02262360 @ 0x02262360, 0x30 bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

extern int func_02019e00(void *p);
extern int func_02019de8(void *p);
extern void func_ov047_022624f4(void *p, int a);

int func_ov047_02262360(void *self)
{
    if (func_02019e00((char *) self + 0x564) == 3 && func_02019de8((char *) self + 0x564) != 0) {
        func_ov047_022624f4(self, 0);
    }
    return 1;
}
