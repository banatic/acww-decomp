/* func_ov079_02279528 @ 0x02279528, 0x64 bytes, Thumb, module ov079
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    void (*fn)(void *self);
    int adj;
} Pair;

// The ROM keeps these with the neighbouring functions' copies of the same kind: the
// {fn, 0} pairs in .data, the array and its guard in .bss.
extern Pair data_ov079_02279fc0; // {func_ov079_02279374, 0}
extern Pair data_ov079_02279fc8; // {func_ov079_0227936c, 0}
extern Pair data_ov079_02279fe0; // {func_ov079_02278d58, 0}
extern Pair data_ov079_0227a20c[3];
extern int data_ov079_0227a1c4;

void func_ov079_02279528(int arg0, Pair *out, int idx)
{
    if (!(data_ov079_0227a1c4 & 1)) {
        data_ov079_0227a20c[0] = data_ov079_02279fc0;
        data_ov079_0227a20c[1] = data_ov079_02279fc8;
        data_ov079_0227a20c[2] = data_ov079_02279fe0;
        data_ov079_0227a1c4 |= 1;
    }
    *out = data_ov079_0227a20c[idx];
}
