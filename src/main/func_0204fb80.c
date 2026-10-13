/* func_0204fb80 @ 0x0204fb80, 0xbc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;
extern int func_02073d90(void *);
extern int func_020644cc(int n);

struct UnkStruct_0204fb80 {
    unsigned char *data;
    unsigned char count;
};

extern struct UnkStruct_0204fb80 **data_020dc8b4[]; // g_020dc8b4

int func_0204fb80(int *outA, int *outB, int k, int n, int m)
{

    int i;
    int t;
    int limit;
    unsigned char *data;
    struct UnkStruct_0204fb80 ***tp;
    int acc;
    int count;
    int idx;
    struct UnkStruct_0204fb80 *ent;

    idx = -1;
    acc = 0;
    if (func_02073d90(data_020ccf94) != 0) {
        t = 3;
        limit = func_020644cc(0x60);
    } else {
        t = 0;
        limit = func_020644cc(0x64);
    }
    i = 0;
    tp = &data_020dc8b4[n - 1];
    ent = &data_020dc8b4[n - 1][m][k];
    count = ent->count - t;
    for (; (int) i < (int) count; i++) {
        data = (*tp)[m][k].data;
        t = i;
        t = 3 * t;
        acc = acc + (data + t)[2];
        if (acc > limit) {
            idx = i;
            break;
        }
    }
    if (idx == -1) {
        return 0;
    }
    idx = 3 * idx;
    *outA = (&data_020dc8b4[n - 1][m][k])->data[idx];
    *outB = ((*tp)[m][k].data + idx)[1];
    return 1;
}
