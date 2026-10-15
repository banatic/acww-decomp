/* func_ov004_02242a9c @ 0x02242a9c, 0x48 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_02244be0(void *, int);
void func_ov004_02242a9c(void *self, int v, int n)
{
    if (n % 4 == 0) {
        *(short *) ((char *) self + 0x192) = (short) (v + 0x71c);
    } else if (n % 2 == 0) {
        *(short *) ((char *) self + 0x192) = (short) (v - 0x71c);
    }
    func_ov004_02244be0(self, 0);
}
