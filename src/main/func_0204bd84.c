/* func_0204bd84 @ 0x0204bd84, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204be10(const void *);
extern int func_0204bde8(const void *);
extern int func_0204bdd0(int);
extern void func_0204b3cc(void *, int);
extern int func_0204be38(void *);
extern void func_020051b0(void *);

int func_0204bd84(void *p)
{
    int x, y;
    int local[2];

    if (func_0204be10(p) != 0) {
        x = func_0204bde8(p);
        if (x != 0x1e) {
            y = func_0204bdd0(x);
            func_0204b3cc(local, y);
            if (func_0204be38(local) != 0) {
                func_020051b0(local);
                return 0;
            }
            func_020051b0(local);
            return 1;
        }
    }
    return 0;
}
