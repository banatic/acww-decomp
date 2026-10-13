/* func_02014c60 @ 0x02014c60, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02014c60 {
    char pad_00[0x40];
    void *unk_40;
    char pad_44[0x4c - 0x44];
    char *unk_4C;
    char pad_50[0xac - 0x50];
    char unk_AC;
} UnkStruct_02014c60;

extern int func_02019e00(void *);
extern int func_02019de8(void *);
extern void func_02068434(void *);
extern void func_02016004(void *);

int func_02014c60(UnkStruct_02014c60 *this)
{
    int result = 0;
    if (this->unk_4C != 0 && this->unk_40 != 0) {
        if (func_02019e00(this->unk_4C + 0x564) == 0x13 && func_02019de8(this->unk_4C + 0x564) != 0) {
            func_02068434(this->unk_40);
            func_02016004(this);
            this->unk_AC = 2;
            result = 1;
        }
    }
    return result;
}
