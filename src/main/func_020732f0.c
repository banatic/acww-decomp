/* func_020732f0 @ 0x020732f0, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02073d28(void *a, int b);
extern void MI_CpuCopy8(int a, int b, int c);
typedef struct {
    char pad_00[0x118];
    int unk_118;
} UnkStruct_020732f0;
inline UnkStruct_020732f0 *inline_fn(UnkStruct_020732f0 *arg0)
{
    return arg0;
}

void func_020732f0(UnkStruct_020732f0 *a, int b, int c)
{
    int dst = func_02073d28(a, 4);

    dst += a->unk_118;

    MI_CpuCopy8(b, dst, c);
    a->unk_118 += c;
}
