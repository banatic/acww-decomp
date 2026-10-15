/* func_0209c988 @ 0x0209c988, 0xe4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209cb88(void *p, int n);
extern int func_0209ca6c(void *p, int a, int b);
extern int func_0209cc30(void *p, int a, int b);
extern int func_0209d030(int v);
extern int func_0209d01c(int v, int n);
extern int func_020644cc(int n);

int func_0209c988(void *arg, int p2)
{
    if (func_0209cb88(arg, 0xe) == 0) {
        return 0;
    }
    if (func_0209cb88(arg, 0xd) == 0) {
        return 0;
    }
    if (func_0209cb88(arg, 0xc) == 0) {
        return 0;
    }

    if (p2 == 1) {
        return func_0209ca6c(arg, 0xd, 0xb);
    }
    if (p2 == 2) {
        return func_0209ca6c(arg, 0xe, 0xb);
    }
    if (p2 == 3) {
        return func_0209ca6c(arg, 0xa, 0xb);
    }
    if (p2 == 4) {
        return func_0209ca6c(arg, 0xc, 0xb);
    }

    {
        unsigned int i;
        int count = 0;

        for (i = 1; i < 5; i++) {
            if (func_0209d030(func_0209cc30(arg, i, 3)) == 9) {
                count++;
            }
        }

        if (count != 0) {
            int pick = func_020644cc(count);
            int seen = 0;

            for (i = 1; i < 5; i++) {
                if (func_0209d030(func_0209cc30(arg, i, 3)) == 9) {
                    if (pick == seen) {
                        func_0209d01c(func_0209cc30(arg, i, 3), 0xb);
                        return 1;
                    }
                    seen++;
                }
            }
        }
    }

    return 0;
}
