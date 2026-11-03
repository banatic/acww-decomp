/* room_object_02253058_8: 6 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_022183a0 @ 0x022183a0, 0x2 bytes, Thumb
 * func_ov004_02218394 @ 0x02218394, 0xa bytes, Thumb
 * func_ov004_02218384 @ 0x02218384, 0x10 bytes, Thumb
 * func_ov004_02218374 @ 0x02218374, 0x10 bytes, Thumb
 * func_ov004_02218364 @ 0x02218364, 0x10 bytes, Thumb
 * func_ov004_02218354 @ 0x02218354, 0x10 bytes, Thumb
 */

typedef struct {
    int a, b;
} UnkStruct_02218394;

extern char *func_ov004_022183a4(int);

void func_ov004_022183a0(void) {}

UnkStruct_02218394 *func_ov004_02218394(UnkStruct_02218394 *p, int i)
{
    return &p[i & 1];
}

int func_ov004_02218384(int arg)
{
    func_ov004_022183a4(arg);
    return arg;
}

int func_ov004_02218374(int arg)
{
    func_ov004_022183a0();
    return arg;
}

int func_ov004_02218364(int arg)
{
    func_ov004_022183a4(arg);
    return arg;
}

int func_ov004_02218354(int arg)
{
    func_ov004_022183a0();
    return arg;
}
