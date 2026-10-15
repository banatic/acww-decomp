/* func_02099348 @ 0x02099348, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02099870(int);
extern int func_02094fec(int);
extern int func_02099380(int);
extern int func_02095074(int, int);

int func_02099348(int param1, int param2)
{
    int r;
    int v0;
    int v1;

    v0 = func_02099870(param1);
    r = 0;
    if (func_02094fec(v0) != -1) {
        v1 = func_02099380(param1);
        if (v1 != 0) {
            func_02095074(func_02099870(v1), param2);
            r = 1;
        }
    }
    return r;
}
