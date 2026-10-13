/* func_ov098_022a2fc0 @ 0x022a2fc0, 0xa0 bytes, Thumb, module ov098
 * mwccarm 1.2/base -O4,s
 */

extern int func_020961a8(int);
extern int func_0204f658(int, int, int);
extern int func_0203162c(void *a, void *b, int c, int d, int e, int f);
extern int data_021c80bc;

typedef struct {
    int a;
    int pad1;
    int b;
} UnkStruct_022a2fc0;

typedef struct {
    unsigned char pad_00[0x5c];
    UnkStruct_022a2fc0 sub;
    unsigned char pad1[0x8e - 0x68];
    short c;
} UnkStruct_022a2fc0_2;

int func_ov098_022a2fc0(char *p, int flag)
{
    UnkStruct_022a2fc0_2 *obj;
    int period;
    UnkStruct_022a2fc0 *sub;
    int result;

    obj = (UnkStruct_022a2fc0_2 *) func_020961a8(4);
    sub = &obj->sub;
    period = 0xa00;
    result = func_0204f658(data_021c80bc, obj->sub.a >> 17, sub->b >> 17);

    if (flag) {
        if ((result & 0x7f000) == 0 && (result & 8) == 0) {
            return 0;
        }
        period = 0x1b58;
    } else {
        if ((result & 0x7f000) != 0 || (result & 8) != 0) {
            period += 0xe10;
        } else {
            period += 0x3e8;
        }
    }

    return func_0203162c(p + 0x2e14, sub, obj->c, 0x7800, period, 0xc);
}
