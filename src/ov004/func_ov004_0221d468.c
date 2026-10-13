/* func_ov004_0221d468 @ 0x0221d468, 0x58 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204bcdc(void *it);
extern int func_0204bc64(void *it);

int func_ov004_0221d468(void *it, int k)
{
    unsigned short empty;
    int ok;

    if (k == 0) {
        if (func_0204bcdc(it) != 0) {
            empty = 0xfff1;
            ok = (func_0204bc64(it) == func_0204bc64(&empty)) ? 1 : 0;
        } else {
            ok = (*(unsigned short *) it == 0xfff1) ? 1 : 0;
        }
        if (ok == 0) {
            return 1;
        }
    }
    return 0;
}
