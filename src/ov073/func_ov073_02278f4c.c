/* func_ov073_02278f4c @ 0x02278f4c, 0x4c bytes, Thumb, module ov073
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    void (*fn)(void *self);
    int adj;
} Pair;

extern void func_ov073_02278ecc(void *self);

// the table and its guard sit with the neighbouring functions' tables and guards in .bss
extern Pair data_ov073_02279bdc[8];
extern int data_ov073_02279bd0;

void func_ov073_02278f4c(void *self, int idx)
{
    static Pair src0 = {func_ov073_02278ecc, 0};

    if (!(data_ov073_02279bd0 & 1)) {
        data_ov073_02279bdc[0] = src0;
        data_ov073_02279bd0 |= 1;
    }
    *(Pair *) ((char *) self + 0xb8) = data_ov073_02279bdc[idx];
}
