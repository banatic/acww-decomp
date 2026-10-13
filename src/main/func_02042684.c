/* func_02042684 @ 0x02042684, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuCopy8(void *src, void *dst, int size);
extern int func_0203fea0(void *a, void *b);
extern void func_02042798(int a, void *b, void *c);

void func_02042684(int a, char *b, void *src)
{
    struct UnkStruct_02042684 {
        int x;
        int y;
    } s0, s1, s2;
    char t4[84];

    s0.x = 0;
    s0.y = 0;

    MI_CpuCopy8(src, &s0, 8);
    MI_CpuCopy8(&s0, &s1, 8);
    if (func_0203fea0(t4, &s1) > 0) {
        MI_CpuCopy8(&s0, &s2, 8);
        func_02042798(a, t4, &s2);
    }
    b[0x17276] = 1;
}
