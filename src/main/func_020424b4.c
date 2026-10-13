/* func_020424b4 @ 0x020424b4, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020424b4 {
    char pad_00[0x20];
    void *unk_20;
};

struct R4Struct {
    char pad_00[0xC0];
    unsigned int unk_C0;
    unsigned int unk_C4;
    char pad_C8[0x1021];
    unsigned char unk_10E9;
};

extern struct UnkStruct_020424b4 data_021c779c;
extern void DC_FlushAll(void *p);
extern void func_0204714c(struct UnkStruct_020424b4 *base, void *a, void *b, unsigned int c, unsigned int d, unsigned int e);
extern int func_020ea584(unsigned int a, unsigned int b);
extern int OS_ExitThread(unsigned int a, unsigned int b);

void func_020424b4(void *p)
{
    struct R4Struct *r4;

    DC_FlushAll(p);

    r4 = (struct R4Struct *) data_021c779c.unk_20;

    func_0204714c(&data_021c779c, p, (char *) p + 8, *(unsigned int *) ((char *) p + 0x10),
                  *(unsigned char *) ((char *) p + 0x14), 1);

    func_020ea584(r4->unk_C0, r4->unk_C4);

    r4->unk_10E9 = 1;

    OS_ExitThread(0x10E9, 1);
}
