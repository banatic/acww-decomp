/* taxi_driver_talk_3: 2 functions, module ov051
 * mwccarm 1.2/base -O4,s
 * func_ov051_02261008 @ 0x02261008, 0x12 bytes, Thumb
 * func_ov051_02260fd8 @ 0x02260fd8, 0x30 bytes, Thumb
 */

typedef struct {
    int unk_00;
    unsigned char unk_04;
} UnkStruct_02260fd8;

extern int func_ov068_02273088(void);
extern int data_ov051_022615c0;
extern int func_020a12d4(void);
extern int func_020a12ac(void);

void func_ov051_02261008(int param1, int param2)
{
    if (param2 == 0) {
        func_ov068_02273088();
    }
}

void func_ov051_02260fd8(int arg, UnkStruct_02260fd8 *ptr)
{
    ptr->unk_00 = data_ov051_022615c0;
    if (func_020a12d4() || func_020a12ac()) {
        ptr->unk_04 = 0;
    } else {
        ptr->unk_04 = 0x28;
    }
}
