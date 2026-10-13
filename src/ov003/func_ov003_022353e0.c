/* func_ov003_022353e0 @ 0x022353e0, 0x74 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_022353e0;
extern UnkStruct_022353e0 *data_020ccf94;
extern int func_02073dd4(void *a, int b);
extern int func_ov003_02219d8c(void *a, int b);

int func_ov003_022353e0(char *self, void *ctx)
{
    // i is declared before p.
    signed char i;
    signed char *p = (signed char *) (self + 0x24e);
    if (*p <= 0) {
        if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64)) {
            for (i = 0; i < 4; i++) {
                *p = (signed char) func_ov003_02219d8c(ctx, i);
                if (*p > 0) {
                    break;
                }
            }
        } else {
            *p = (signed char) func_ov003_02219d8c(ctx, 4);
        }
    }
    if (*p > 0) {
        *p = (signed char) (*p - 1);
        if (*p == 0) {
            return 1;
        }
    }
    return 0;
}
