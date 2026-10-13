/* func_0205df54 @ 0x0205df54, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00[4];
    struct {
        char data[20];
    } inner[4];
    char pad_60[0x70];
    char unk_D0[4];
} UnkStruct_0205df54;

extern void func_02055b40(void *);
extern void func_020e9b9c(void *);
extern void *data_021c9adc;

void func_0205df54(UnkStruct_0205df54 *self)
{
    int i;

    for (i = 0; i < 4; i++) {
        func_02055b40(&self->inner[i]);
    }
    for (i = 0; i < 4; i++) {
        self->unk_00[i] = 0;
    }
    if (data_021c9adc) {
        func_020e9b9c(data_021c9adc);
    }
    for (i = 0; i < 4; i++) {
        self->unk_D0[i] = 0x4b;
    }
}
