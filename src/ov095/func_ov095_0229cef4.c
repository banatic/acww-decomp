/* func_ov095_0229cef4 @ 0x0229cef4, 0x70 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov095_0229cb5c(void *, int, int);
extern void func_ov095_0229ca64(void *, int, int);
extern void func_ov095_0229c974(void *, int, int);
extern void func_ov095_022999a8(void *, int);
extern int data_ov095_0229d050[];
extern int data_ov095_0229d088[];
extern int data_ov095_0229d0c0[];

typedef struct {
    char pad_00[0x16];
    unsigned char switch_val;
    char pad_17[9];
    unsigned int flags;
} UnkStruct_0229cef4;

void func_ov095_0229cef4(UnkStruct_0229cef4 *obj, int bit)
{
    obj->flags |= (1 << bit);
    switch (obj->switch_val) {
        case 0:
        case 3:
            break;
        case 1:
            func_ov095_0229cb5c(obj, data_ov095_0229d050[bit], 14);
            break;
        case 2:
            func_ov095_0229ca64(obj, data_ov095_0229d088[bit], 14);
            break;
        case 4:
            func_ov095_0229c974(obj, data_ov095_0229d0c0[bit], 14);
            break;
    }
    func_ov095_022999a8(obj, 1);
}
