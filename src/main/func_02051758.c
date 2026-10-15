/* func_02051758 @ 0x02051758, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020e9898(void *);
extern int FS_CloseFile(void *);

typedef struct {
    void *unk_00;
    void *unk_04;
    void *unk_08;
    char pad_0C[8];
    char unk_14;
} UnkStruct_02051758;

void func_02051758(UnkStruct_02051758 *p)
{
    if (p->unk_00) {
        func_020e9898(p->unk_00);
        p->unk_00 = 0;
    }
    if (p->unk_04) {
        func_020e9898(p->unk_04);
        p->unk_04 = 0;
    }
    if (p->unk_08) {
        func_020e9898(p->unk_08);
        p->unk_08 = 0;
    }
    FS_CloseFile(&p->unk_14);
}
