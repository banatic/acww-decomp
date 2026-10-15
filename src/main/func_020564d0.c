/* func_020564d0 @ 0x020564d0, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020dd144[];
extern void *func_02056548(void *, void *, int);

typedef struct {
    unsigned char pad_00[0x18];
    void *unk_18;
    void *unk_1C;
} UnkStruct_020564d0;

int func_020564d0(UnkStruct_020564d0 *param0, void *param1, int argument2)
{
    if (param0->unk_18 || param0->unk_1C) {
        return 0;
    }
    param0->unk_18 = func_02056548(param1, data_020dd144, (int) argument2);
    param0->unk_1C = param1;
    return param0->unk_18 ? 1 : 0;
}
