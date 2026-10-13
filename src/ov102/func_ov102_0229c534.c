/* func_ov102_0229c534 @ 0x0229c534, 0x2c bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x23f4];
    char arr[2][0x6c];
    char pad_24CC[0xdc];
    char flag;
} UnkStruct_0229c534;

extern void func_02070b84(void *);

void func_ov102_0229c534(UnkStruct_0229c534 *self)
{
    int i;

    self->flag = 0;

    for (i = 0; i < 2; i++) {
        func_02070b84(self->arr[i]);
    }
}
