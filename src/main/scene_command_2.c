/* scene_command_2: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02014d04 @ 0x02014d04, 0x18 bytes, Thumb
 * func_02014cb0 @ 0x02014cb0, 0x54 bytes, Thumb
 * func_02014c60 @ 0x02014c60, 0x50 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x40];
    unsigned int unk_40;
    unsigned char pad_44[8];
    unsigned int unk_4C;
    unsigned char pad_50[0x5c];
    unsigned char unk_AC;
} UnkStruct_02014cb0;

typedef struct UnkStruct_02014c60 {
    char pad_00[0x40];
    void *unk_40;
    char pad_44[0x4c - 0x44];
    char *unk_4C;
    char pad_50[0xac - 0x50];
    char unk_AC;
} UnkStruct_02014c60;

extern int func_0201596c(int, int);
extern int func_02019d0c(unsigned int, int, int, int, int, int, int, int, int, unsigned short, int);
extern void func_02068440(unsigned int);
extern unsigned short data_020c80f8;
extern int func_02019e00(void *);
extern int func_02019de8(void *);
extern void func_02068434(void *);
extern void func_02016004(void *);

int func_02014d04(int a)
{
    int ret = 0;
    if (func_0201596c(a, 9)) {
        ret = 1;
    }
    return ret;
}

int func_02014cb0(UnkStruct_02014cb0 *p)
{
    if (p->unk_4C != 0 && p->unk_40 != 0) {
        if (func_02019d0c(p->unk_4C + 0x564, 0x13, 4, 0, 0, 0, 0, 0, 0, data_020c80f8, 0)) {
            func_02068440(p->unk_40);
            p->unk_AC = 1;
        }
    }
    return 0;
}

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
