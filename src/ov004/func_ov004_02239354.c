/* func_ov004_02239354 @ 0x02239354, 0x38 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char b[0x40];
} UnkStruct_02239354;
extern void func_02034270(UnkStruct_02239354 *, void *, int, int);
extern int func_020341c8(UnkStruct_02239354 *, int);
extern void func_0203423c(UnkStruct_02239354 *);

int func_ov004_02239354(void *a)
{
    UnkStruct_02239354 s;
    int r = 0;
    func_02034270(&s, a, r, r);
    if (func_020341c8(&s, r) == 0x800) {
        r = 1;
    }
    func_0203423c(&s);
    return r;
}
