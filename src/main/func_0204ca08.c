/* func_0204ca08 @ 0x0204ca08, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204bcdc(void *);
extern int func_0204bc64(int);

int func_0204ca08(int a, int b)
{
    int r5 = a;
    int r4 = b;
    if (func_0204bcdc((void *) a)) {
        r5 = func_0204bc64(r5);
        if (r5 == func_0204bc64(r4)) {
            return 1;
        } else {
            return 0;
        }
    } else {
        if (*(unsigned short *) r5 == *(unsigned short *) r4) {
            return 1;
        } else {
            return 0;
        }
    }
}
