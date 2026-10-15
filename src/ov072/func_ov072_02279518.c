/* func_ov072_02279518 @ 0x02279518, 0x90 bytes, Thumb, module ov072
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x3b0];
    int unk_3B0;
    char pad_3B4[0x564 - 0x3b4];
    int unk_564;
    char pad_568[0x718 - 0x568];
    unsigned char unk_718;
    char pad_719[3];
    int unk_71C;
} UnkStruct_02279518;

extern int func_02019d0c(void *, int, int, int, int, int, int, int, int, int, int);
extern void func_0201ad18(void *, int, int, int, void *, int, int, int);
extern int func_020644cc(int);
extern unsigned short data_020c80f8;
extern int data_020c814c;
extern int data_021fbee8;

int func_ov072_02279518(UnkStruct_02279518 *obj)
{
    func_02019d0c(&obj->unk_564, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    func_0201ad18(&obj->unk_3B0, 1, 0, 0, &data_021fbee8, 4, data_020c814c, 1);
    if (obj->unk_718 != 0) {
        obj->unk_71C = 0x190;
        obj->unk_71C = obj->unk_71C + func_020644cc(0x258);
    }
    return 1;
}
