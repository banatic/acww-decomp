/* func_ov081_0227916c @ 0x0227916c, 0x54 bytes, Thumb, module ov081
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int lo;
    unsigned int hi;
} Pair;

extern Pair data_ov081_022796b0;
extern Pair data_ov081_022796a8;
extern Pair data_ov081_022798a4[2];
extern unsigned int data_ov081_022798a0;

void func_ov081_0227916c(int unused, Pair *dst, int idx)
{
    unsigned int flag = data_ov081_022798a0;
    if ((flag & 1) == 0) {
        data_ov081_022798a4[0] = data_ov081_022796b0;
        data_ov081_022798a4[1] = data_ov081_022796a8;
        data_ov081_022798a0 = flag | 1;
    }
    *dst = data_ov081_022798a4[idx];
}
