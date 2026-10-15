/* func_ov143_0229a16c @ 0x0229a16c, 0x38 bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 */

typedef struct Func_ov143_0229a16c_s {
    unsigned char pad_00[0x9C];
    short unk_9C;
} Func_ov143_0229a16c_t;

extern void *data_020ccf94;
extern int func_0206fc6c(void);
extern int func_02073d90(void *);
extern int func_02074fec(int);

int func_ov143_0229a16c(Func_ov143_0229a16c_t *self)
{
    if (func_0206fc6c() == 0) {
        return 1;
    }
    if (func_02073d90(data_020ccf94) != 0) {
        if (func_02074fec(self->unk_9C) == 0) {
            return 0;
        }
    }
    return 1;
}
