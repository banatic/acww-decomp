/* func_02010ecc @ 0x02010ecc, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02056778(void *p);

typedef struct {
    char pad_00[0x73c];
    char unk_73C;
    char pad_73D[0x770 - 0x73c - 1];
    int unk_770;
} UnkStruct_02010ecc;

void func_02010ecc(UnkStruct_02010ecc *p)
{
    if (p->unk_770 != 0x16f) {
        func_02056778((void *) &p->unk_73C);
    }
}
