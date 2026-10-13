/* func_02078478 @ 0x02078478, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;
extern int func_02073d90(void *);
extern int func_0207f294(int);
extern int func_0207cf74(int);
extern void func_020784b0(int, int);

void func_02078478(int a, int b)
{
    if (func_02073d90(data_020ccf94)) {
        int v = func_0207f294(a);
        if (func_0207cf74(v)) {
            func_020784b0(v, b);
        }
    }
}
