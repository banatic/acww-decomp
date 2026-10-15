/* func_0201abd0 @ 0x0201abd0, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201ac10(int, int, int, int);
extern int func_0201abac(void *a, int b);

int func_0201abd0(int a, int position, int target, int angleOffset)
{
    int angle = func_0201ac10(a, position, target, angleOffset);
    return func_0201abac((void *) a, angle);
}
