/* func_0207de70 @ 0x0207de70, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x7b0];
    unsigned short arr[1];
} UnkStruct_0207de70;

extern int func_0207deb4(UnkStruct_0207de70 *p);
extern void func_0207df88(UnkStruct_0207de70 *p);
extern int func_0207dfd4(UnkStruct_0207de70 *p, int a);
extern void func_020782d8(UnkStruct_0207de70 *p, int a);

int func_0207de70(UnkStruct_0207de70 *p)
{
    int idx;
    idx = func_0207deb4(p);
    if (idx == -1) {
        goto error;
    }
    p->arr[idx] = 0xfff1;
    func_0207df88(p);
    func_020782d8(p, func_0207dfd4(p, 0));
    return 1;
error:
    return 0;
}
