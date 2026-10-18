/* func_ov070_02279820 @ 0x02279820, 0x4c bytes, Thumb, module ov070
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    void (*fn)(void *self);
    int adj;
} Pair;

extern void func_ov070_02279778(void *self);

// the table and its guard sit with the neighbouring functions' tables and guards in .bss
extern Pair data_ov070_02279f1c[8];
extern int data_ov070_02279f10;

void func_ov070_02279820(void *self, int idx)
{
    static Pair src0 = {func_ov070_02279778, 0};

    if (!(data_ov070_02279f10 & 1)) {
        data_ov070_02279f1c[0] = src0;
        data_ov070_02279f10 |= 1;
    }
    *(Pair *) ((char *) self + 0xb8) = data_ov070_02279f1c[idx];
}
