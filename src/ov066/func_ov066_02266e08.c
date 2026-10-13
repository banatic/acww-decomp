/* func_ov066_02266e08 @ 0x02266e08, 0x5c bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

typedef struct UnkStruct_02266e08 {
    unsigned char pad_00[0x16];
    unsigned char unk_16;
    unsigned char pad_17[0x25];
    unsigned long bits0 : 10;
    signed long bit10 : 1;
    unsigned long bits11 : 21;
} UnkStruct_02266e08;

extern UnkStruct_02266e08 *data_ov066_0226bdec;
extern void func_ov066_02266dbc(void);

int func_ov066_02266e08(void)
{
    int result = 0;
    UnkStruct_02266e08 *p = data_ov066_0226bdec;
    if (p->bit10) {
        result = 1;
    } else if (p->unk_16 == 1) {
        func_ov066_02266dbc();
        result = 1;
    }
    return result;
}
