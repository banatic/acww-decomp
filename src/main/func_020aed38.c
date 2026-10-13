/* func_020aed38 @ 0x020aed38, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020aed38 {
    int unk_00;
    int unk_04;
};

extern int func_020aefd4(struct UnkStruct_020aed38 *a, int b);
extern int func_020b0164(int *p, int b, int c, int d, int e, int f, int g);

int func_020aed38(struct UnkStruct_020aed38 *a, int b)
{
    int v;
    v = func_020aefd4(a, b);
    return func_020b0164(&a->unk_04, b, 0, 0, v, 0x25, 0);
}
