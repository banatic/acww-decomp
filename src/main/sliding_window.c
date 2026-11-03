/* sliding_window: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0208a4dc @ 0x0208a4dc, 0x32 bytes, Thumb
 * func_0208a490 @ 0x0208a490, 0x4a bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x0c];
    unsigned char unk_0C;
    unsigned char pad_0D[0x3c - 0x0d];
    int unk_3C;
    unsigned char pad_40[0x48 - 0x40];
    int unk_48;
    unsigned char pad_4C[0x50 - 0x4c];
    int unk_50;
    unsigned char pad_54[0x57 - 0x54];
    unsigned char flag;
} UnkStruct_0208a490;

extern void func_020a8fb8(void *);
extern int func_0208a1cc(void *);

void func_0208a4dc(void *arg0)
{
    void *condition_value0;
    void *condition_value1;
    if ((condition_value0 = (void *) (*(int *) ((char *) arg0 + 0xc0))) != 0) {
        func_020a8fb8(condition_value0);
        *(int *) ((char *) arg0 + 0xc0) = 0;
    }
    if ((condition_value1 = (void *) (*(int *) ((char *) arg0 + 0xc4))) != 0) {
        func_020a8fb8(condition_value1);
        *(int *) ((char *) arg0 + 0xc4) = 0;
    }
}

void func_0208a490(UnkStruct_0208a490 *obj)
{
    if (obj->flag) {
        int r, offset, sum, left, right;
        r = func_0208a1cc(&obj->unk_0C);
        offset = r * 4 + 0xc;
        sum = obj->unk_3C + obj->unk_48;
        left = sum - offset + 0x80;
        right = offset + sum - 0x80;
        if (left < 0) {
            obj->unk_50 = -left;
        } else {
            if (right > 0) {
                obj->unk_50 = -right;
            } else {
                obj->unk_50 = 0;
            }
        }
    } else {
        obj->unk_50 = 0;
    }
}
