/* func_ov100_0229c2d8 @ 0x0229c2d8, 0x4c bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fc6c(void);
extern int func_ov100_0229c2c0(void *, int);
extern int func_02073d90(int);
extern int func_02074fec(int);
extern int data_020ccf94;

typedef struct {
    unsigned char pad_00[0x291a];
    short unk_291A;
} Obj_0229c2d8;

int func_ov100_0229c2d8(Obj_0229c2d8 *obj)
{
    if (func_0206fc6c() == 0) {
        return 1;
    }
    if (func_ov100_0229c2c0(obj, 8) == 0) {
        return 1;
    }
    if (func_02073d90(data_020ccf94) != 0 && func_02074fec(obj->unk_291A) == 0) {
        return 0;
    }
    return 1;
}
