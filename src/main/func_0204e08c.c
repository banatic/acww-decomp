/* func_0204e08c @ 0x0204e08c, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0204e204(void *, int, int, int, int, int, int, int);
extern int func_0204bcdc(void *);
extern int func_0204bc64(void *);

int func_0204e08c(int p0, int p1, int p2, int p3)
{
    unsigned short local[4];
    int result;

    func_0204e204(local, p0, p1, p2, p3, 0x500b, 0x500b, 0x400);

    if (func_0204bcdc(local) != 0) {
        local[1] = 0xfff1;
        if (func_0204bc64(local) == func_0204bc64(&local[1])) {
            result = 1;
        } else {
            result = 0;
        }
    } else {
        if (local[0] == 0xfff1) {
            result = 1;
        } else {
            result = 0;
        }
    }

    if (result == 0) {
        return 1;
    } else {
        return 0;
    }
}
