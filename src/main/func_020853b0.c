/* func_020853b0 @ 0x020853b0, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_020853b0 {
    int unk_00;
    int unk_04;
    int unk_08;
} UnkStruct_020853b0;

extern unsigned char data_021d213c[];
extern void func_02077a54(void *, int, int);
extern void func_020779b8(void *, int, int);
extern void MI_CpuCopy8(const void *, void *, unsigned int);

int func_020853b0(unsigned short *a0, int a1, UnkStruct_020853b0 *a2, int a3, const void *a4, const void *a5)
{
    unsigned char *e;
    unsigned int v;
    unsigned int off;
    v = *a0 & 0xfff;
    if (v >= 8) {
        goto fail;
    }
    off = v * 0x1e;
    e = &data_021d213c[off];
    data_021d213c[off] = 1;
    func_02077a54(e + 3, a1, 0);
    func_020779b8(e + 4, a2->unk_00, a2->unk_08);
    MI_CpuCopy8(&a3, e + 9, 2);
    MI_CpuCopy8(a4, e + 0xf, 0xf);
    MI_CpuCopy8(a5, e + 0xb, 4);
    return 1;
fail:
    return 0;
}
