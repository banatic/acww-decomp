/* func_ov004_02246848 @ 0x02246848, 0x68 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned short id;
    unsigned short unk_02;
} UnkStruct_02246848;

extern void func_02061e2c(UnkStruct_02246848 *out, int a);
extern int func_0204bcdc(UnkStruct_02246848 *a);
extern int func_0204c4e8(UnkStruct_02246848 *a);
extern int func_0204c520(UnkStruct_02246848 *a);

int func_ov004_02246848(int a)
{
    UnkStruct_02246848 t;
    unsigned short v;
    int f;

    func_02061e2c(&t, a);
    if (func_0204bcdc(&t) != 0) {
        return 0x19;
    }
    if (func_0204c4e8(&t) != 0) {
        goto r42;
    }
    f = 0;
    v = t.id;
    if (v >= 0x156c && v <= 0x156c) {
        f = 1;
    }
    if (f != 0) {
    r42:
        return 0x42;
    }
    if (v >= 0x13a8 && v <= 0x13c7) {
        return 9;
    }
    return func_0204c520(&t);
}
