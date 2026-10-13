/* func_ov095_0229cd30 @ 0x0229cd30, 0x74 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov095_0229b16c(int);
extern int func_ov095_0229cf64(int, int);
extern void func_ov095_0229cef4(int, int);
extern void func_ov095_0229cc9c(int);
extern void func_ov095_022999a8(int, int);

typedef union {
    struct {
        unsigned int f0;
        unsigned int f4;
    } word;
    struct {
        unsigned int f0;
        unsigned short f4_low;
        unsigned short f4_high;
    } half;
} Entry;

void func_ov095_0229cd30(int param)
{
    Entry *arr;
    int i;

    arr = (Entry *) func_ov095_0229b16c(param);
    if (arr != 0) {
        for (i = 0; i < 100; i++) {
            arr[i].word.f4 = (arr[i].word.f4 & 0xffff0fff) | 0x0000c000;
            if (arr[i].half.f4_high == 0xffff) {
                i = 100;
            }
        }
    }
    for (i = 0; i < 14; i++) {
        if (func_ov095_0229cf64(param, i)) {
            func_ov095_0229cef4(param, i);
        }
    }
    func_ov095_0229cc9c(param);
    func_ov095_022999a8(param, 1);
}
