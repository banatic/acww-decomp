/* func_ov110_0229c2dc @ 0x0229c2dc, 0x48 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fc6c(void *);
extern int func_ov110_0229c2c8(void *, int);
extern int func_02073d90(int);
extern int func_02074fec(short);
extern int data_020ccf94;

typedef struct {
    char pad_00[0xEE];
    short unk_EE;
} UnkStruct_0229c2dc;

int func_ov110_0229c2dc(UnkStruct_0229c2dc *param)
{
    if (func_0206fc6c(param) == 0) {
        return 1;
    }
    if (func_ov110_0229c2c8(param, 8) == 0) {
        return 1;
    }
    if (func_02073d90(data_020ccf94) != 0 && func_02074fec(param->unk_EE) == 0) {
        return 0;
    }
    return 1;
}
