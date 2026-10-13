/* func_ov050_02262618 @ 0x02262618, 0x10 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xb4];
    void *unk_B4;
} FuncOvlStruct;

void *func_ov050_02264834(void *arg0, int arg1);

void *func_ov050_02262618(FuncOvlStruct *self)
{
    return func_ov050_02264834(self->unk_B4, 0x11);
}
