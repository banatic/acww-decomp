/* func_020914dc @ 0x020914dc, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuFill8(void *p, int, int);

typedef struct {
    char pad_00[0xe];
    short unk_0E;
    short unk_10;
    int unk_14;
    short unk_18;
} UnkStruct_020914dc;

void func_020914dc(UnkStruct_020914dc *p)
{
    MI_CpuFill8(p, 0, 0x14);
    p->unk_0E = -1;
    p->unk_10 = 0x1000;
    p->unk_14 = -1;
    p->unk_18 = 0x66;
}
