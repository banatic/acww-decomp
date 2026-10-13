/* func_ov003_0221bcfc @ 0x0221bcfc, 0x38 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0221bcfc {
    int unk_00;
    int unk_04;
};

struct UnkStruct_0221bcfc_2 {
    char pad_00[0x12c];
    struct UnkStruct_0221bcfc *unk_12C;
};

extern void func_020ae3b8(void *);
extern int func_020ae5f4(void);
extern void func_0206fbd8(int, int);
extern void func_ov003_0221bfa8(void *, int);

extern unsigned char data_021f3b30[];

void func_ov003_0221bcfc(struct UnkStruct_0221bcfc_2 *param)
{
    if (param->unk_12C->unk_04 == 5) {
        func_020ae3b8((void *) data_021f3b30);
        func_0206fbd8(0xe, func_020ae5f4());
        func_ov003_0221bfa8(param, 5);
    }
}
