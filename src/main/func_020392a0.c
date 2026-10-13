/* func_020392a0 @ 0x020392a0, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_020ccf94;
extern int func_02073d90(void *);
extern int func_02073dd4(void *, int);
extern int func_020771cc(int, int, int, int);

void func_020392a0(int param1, int param2)
{
    int r5 = param1;
    int r4 = param2;
    void *r6;
    int r0;

    if (r5 < 4) {
        r6 = (void *) data_020ccf94;
        r0 = func_02073d90(r6);
        if (r0 != 0) {
            r0 = func_02073dd4(r6, r5);
            if (r0 != 0) {
                r5 += 0x14;
                func_020771cc(r5, r4, 0, 1);
            }
        }
    }
}
