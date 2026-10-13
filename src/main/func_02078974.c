/* func_02078974 @ 0x02078974, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02073d90(void *);
extern void *func_0207f294(void *);
extern int func_0207cf74(void *);
extern void func_020789ac(void *, int);
extern void *data_020ccf94;

void func_02078974(void *a, int b)
{
    void *c;

    if (func_02073d90(data_020ccf94) == 0) {
        return;
    }

    c = func_0207f294(a);
    if (func_0207cf74(c) == 0) {
        return;
    }

    func_020789ac(c, b);
}
