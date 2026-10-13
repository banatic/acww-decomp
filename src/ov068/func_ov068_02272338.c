/* func_ov068_02272338 @ 0x02272338, 0x7c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x2db];
    unsigned char byte_at_2db;
} UnkStruct_02272338;

typedef struct {
    unsigned char pad_00[0x5c];
    unsigned int unk_5C;
    unsigned int unk_60;
    unsigned int unk_64;
} RetStruct;

extern int func_ov003_02220174(int);
extern int func_ov009_022630a0(void);
extern RetStruct *func_020961a8(int);
extern int func_02095ab0(const unsigned int *, int, int);
extern void func_ov068_02272a7c(UnkStruct_02272338 *, int);

void func_ov068_02272338(UnkStruct_02272338 *self)
{
    unsigned int arr[3];
    RetStruct *p;
    unsigned int *fp;

    if (func_ov003_02220174(0x5000) == 0) {
        return;
    }
    if (func_ov009_022630a0() == 0) {
        return;
    }

    p = func_020961a8(4);
    if (p != 0) {
        if (self->byte_at_2db == 0) {
            fp = &p->unk_5C;
            arr[0] = *fp;
            arr[1] = fp[1];
            arr[2] = fp[2];
            arr[2] += 0x4000;
            if (func_02095ab0(arr, 0x400, 4) != 0) {
                func_ov068_02272a7c(self, 0xc);
            }
        }
    }

    if (self->byte_at_2db != 0) {
        self->byte_at_2db--;
    }
}
