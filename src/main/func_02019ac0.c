/* func_02019ac0 @ 0x02019ac0, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a;
    int b;
    unsigned short c;
} UnkStruct_02019ac0;

extern void func_020779b8(void *, int, int);
extern void MI_CpuCopy8(void *, void *, int);

void func_02019ac0(unsigned char *out, int x, int y, int z, UnkStruct_02019ac0 s)
{
    func_020779b8(out, x, y);
    func_020779b8(out + 5, z, s.a);
    MI_CpuCopy8(&s.b, out + 10, 2);
    out[12] = (unsigned char) s.c;
}
