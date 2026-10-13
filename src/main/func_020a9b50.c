/* func_020a9b50 @ 0x020a9b50, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    void *unk_00;
    int unk_04;
    unsigned char unk_08;
    unsigned char unk_09;
} UnkStruct_020a9b50;

extern char data_020e3d24;
extern unsigned char data_021f43ec;

void func_020a9b50(UnkStruct_020a9b50 *p)
{
    p->unk_00 = &data_020e3d24;
    p->unk_04 = -1;
    p->unk_08 = data_021f43ec;
    p->unk_09 = data_021f43ec;
}
