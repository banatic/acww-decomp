/* func_ov066_022677e0 @ 0x022677e0, 0x5c bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

extern void *func_ov066_0226a434(void *);

typedef struct {
    unsigned char pad_00[8];
    char *base;
} UnkStruct_022677e0;

typedef struct {
    unsigned char pad_00[9];
    unsigned char count;
} UnkStruct_022677e0_2;

extern UnkStruct_022677e0 *data_ov066_0226bdf0;
extern UnkStruct_022677e0_2 *data_ov066_0226bdec;

void *func_ov066_022677e0(unsigned int arg)
{
    if (data_ov066_0226bdf0 == 0) {
        goto fail;
    }
    if (arg >= data_ov066_0226bdec->count) {
        goto fail;
    }
    return func_ov066_0226a434(data_ov066_0226bdf0->base + (arg << 4));
fail:
    return 0;
}
