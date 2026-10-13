/* func_ov079_02279528 @ 0x02279528, 0x64 bytes, Thumb, module ov079
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    void (*fn)(void *self);
    int adj;
} Pair;

extern void func_ov079_02279374(void *self);
extern void func_ov079_0227936c(void *self);
extern void func_ov079_02278d58(void *self);

void func_ov079_02279528(int arg0, Pair *out, int idx)
{
    static Pair arr[3];
    static const Pair src0 = {func_ov079_02279374, 0};
    static const Pair src1 = {func_ov079_0227936c, 0};
    static const Pair src2 = {func_ov079_02278d58, 0};
    static int flag = 0;
    if (!(flag & 1)) {
        arr[0] = src0;
        arr[1] = src1;
        arr[2] = src2;
        flag |= 1;
    }
    *out = arr[idx];
}
