/* func_0209cb88 @ 0x0209cb88, 0x88 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209cc30(int a, int b, int c);
extern int func_0209d030(int *);
extern int func_020644cc(int a);
extern int func_0209d01c(int a, int b);

int func_0209cb88(int p1, int p2)
{
    unsigned int count = 0;
    unsigned int outer1, outer2;
    unsigned int inner1, inner2;
    unsigned int one = 1;
    unsigned int one2 = 1;
    unsigned int result, counter;

    outer1 = 1;
    do {
        inner1 = one;
        do {
            if (func_0209d030((int *) func_0209cc30(p1, inner1, outer1)) == 9) {
                count++;
            }
            inner1++;
        } while (inner1 < 5);
        outer1++;
    } while (outer1 < 5);

    result = func_020644cc(count);

    counter = 0;
    outer2 = 1;
    while (outer2 < 5) {
        inner2 = one2;
        while (inner2 < 5) {
            if (func_0209d030((int *) func_0209cc30(p1, inner2, outer2)) == 9) {
                if (result == counter) {
                    func_0209d01c(func_0209cc30(p1, inner2, outer2), p2);
                    return 1;
                } else {
                    counter++;
                }
            }
            inner2++;
        }
        outer2++;
    }
    return 0;
}
