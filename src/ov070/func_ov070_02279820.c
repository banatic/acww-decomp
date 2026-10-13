/* func_ov070_02279820 @ 0x02279820, 0x4c bytes, Thumb, module ov070
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    void (*fn)(void *self);
    int adj;
} Pair;

extern void func_ov070_02279778(void *self);

void func_ov070_02279820(void *self, int idx)
{
    static Pair table[8];
    static const Pair src0 = {func_ov070_02279778, 0};
    static int flag = 0;

    if (!(flag & 1)) {
        table[0] = src0;
        flag |= 1;
    }
    *(Pair *) ((char *) self + 0xb8) = table[idx];
}
