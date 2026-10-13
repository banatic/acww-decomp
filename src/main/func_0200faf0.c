/* func_0200faf0 @ 0x0200faf0, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0200faf0 {
    char pad_00[0x8E];
    short unk_8E;
} UnkStruct_0200faf0;

extern int func_02011404(void *, int, int, int, int);
extern void func_020110a0(UnkStruct_0200faf0 *, short *);

int func_0200faf0(UnkStruct_0200faf0 *p, int arg2)
{
    int localB;
    short localA;
    int result;
    localA = p->unk_8E;
    localB = 0x000C0000;
    if (func_02011404(&localA, 0, arg2, 0x01770000, localB) == 0) {
        result = 1;
    } else {
        result = 0;
    }
    func_020110a0(p, &localA);
    return result;
}
