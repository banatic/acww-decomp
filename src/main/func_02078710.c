/* func_02078710 @ 0x02078710, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;
extern int func_02073d90(void *ptr);
extern int func_0207f294(int a);
extern int func_0207cf74(int x);
extern void func_02078748(int a, int b, int c);

void func_02078710(int a, int b, int c)
{
    if (func_02073d90(data_020ccf94) != 0) {
        int x = func_0207f294(a);
        if (func_0207cf74(x) != 0) {
            func_02078748(x, b, c);
        }
    }
}
