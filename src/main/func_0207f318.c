/* func_0207f318 @ 0x0207f318, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0207f3a0(void *, void *, void *, int);
extern int func_0207ffa0(int, int);
extern int func_0207d608(int, int);

int func_0207f318(int p, void *argument1, void *argument2, int argument3)
{
    int v = func_0207f3a0((void *) p, (void *) argument1, (void *) argument2, (int) argument3);
    int r = func_0207ffa0(p, v);
    if (r != 0) {
        if (*(unsigned short *) ((char *) p + v * 2 + 0x78c) != 0xfff1) {
            if (func_0207d608(p, v) != 0) {
                return 1;
            }
        }
    }
    return 0;
}
