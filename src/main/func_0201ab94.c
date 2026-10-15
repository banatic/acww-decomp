/* func_0201ab94 @ 0x0201ab94, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern short func_0201abe8(int, void *, void *, int);
extern int func_0201ab70(char *object, int angle);

int func_0201ab94(int a, void *argument1, void *argument2, int argument3)
{
    int r4;
    int r0;
    int r1;

    r4 = a;
    r0 = func_0201abe8((int) a, (void *) argument1, (void *) argument2, (int) argument3);
    r1 = r0;
    r0 = r4;
    return func_0201ab70((char *) r0, r1);
}
