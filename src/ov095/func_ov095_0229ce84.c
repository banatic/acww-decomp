/* func_ov095_0229ce84 @ 0x0229ce84, 0x70 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x16];
    unsigned char unk_16;
    unsigned char pad_17[9];
    unsigned int unk_20;
} UnkStruct_0229ce84;

extern void func_ov095_0229cb5c(void *, int, int);
extern void func_ov095_0229ca64(void *, int, int);
extern void func_ov095_0229c974(void *, int, int);
extern void func_ov095_022999a8(void *, int);
extern unsigned int data_ov095_0229d050[];
extern unsigned int data_ov095_0229d088[];
extern unsigned int data_ov095_0229d0c0[];

void func_ov095_0229ce84(void *obj, int idx)
{
    UnkStruct_0229ce84 *self = (UnkStruct_0229ce84 *) obj;
    self->unk_20 &= ~(1 << idx);
    switch (self->unk_16) {
        case 0:
            break;
        case 1:
            func_ov095_0229cb5c(obj, data_ov095_0229d050[idx], 12);
            break;
        case 2:
            func_ov095_0229ca64(obj, data_ov095_0229d088[idx], 12);
            break;
        case 3:
            break;
        case 4:
            func_ov095_0229c974(obj, data_ov095_0229d0c0[idx], 12);
            break;
        default:
            break;
    }
    func_ov095_022999a8(obj, 1);
}
