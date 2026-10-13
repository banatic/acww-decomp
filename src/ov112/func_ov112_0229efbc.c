/* func_ov112_0229efbc @ 0x0229efbc, 0x2c bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern int func_02073d90(void *);
extern int func_02074fec(int);
extern void *data_020ccf94;

typedef struct {
    char pad_00[0xb4];
    short unk_B4;
} UnkStruct_0229efbc;

int func_ov112_0229efbc(UnkStruct_0229efbc *p)
{
    if (func_02073d90(data_020ccf94) != 0 && func_02074fec(p->unk_B4) == 0) {
        return 0;
    } else {
        return 1;
    }
}
