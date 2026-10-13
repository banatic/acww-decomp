/* func_020c0440 @ 0x020c0440, 0x4a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020644cc(int);

struct UnkStruct_020c0440 {
    char pad_00[0x0c];
    int unk_0C;
    char pad_10[0x34 - 0x10];
    int arr[3];
    char pad_40[0x58 - 0x40];
    int unk_58;
};

void func_020c0440(struct UnkStruct_020c0440 *s)
{
    int a;
    int v;
    int *p;

    a = func_020644cc(0x80);
    a = (a * (func_020644cc(2) * 2 - 1) + 0x80) << 12;
    v = (func_020644cc(0x50) + 0x50) << 12;
    p = &s->arr[0];
    p[0] = a;
    p[1] = v;
    p[2] = 0;
    s->unk_0C = func_020644cc(8) + 8;
    s->unk_58 = 2;
}
