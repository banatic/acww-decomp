/* func_ov095_0229ce08 @ 0x0229ce08, 0x7c bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229ce08 {
    char pad_00[0x16];
    unsigned char type;
};

extern const int data_ov095_0229d050[];
extern const int data_ov095_0229d088[];
extern const int data_ov095_0229d0c0[];

extern int func_ov095_0229cf64(struct UnkStruct_0229ce08 *obj, int idx);

int func_ov095_0229ce08(struct UnkStruct_0229ce08 *obj, int id)
{
    int i;
    const int *table;

    if (id == -1) {
        return 0;
    }

    switch (obj->type) {
        case 0:
            return 0;
        case 1:
            table = data_ov095_0229d050;
            break;
        case 2:
            table = data_ov095_0229d088;
            break;
        case 3:
            return 0;
        case 4:
            table = data_ov095_0229d0c0;
            break;
        default:
            return 0;
    }

    for (i = 0; i < 14; i++) {
        if (id == table[i]) {
            return func_ov095_0229cf64(obj, i) != 0;
        }
    }

    return 0;
}
