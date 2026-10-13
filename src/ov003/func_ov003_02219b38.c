/* func_ov003_02219b38 @ 0x02219b38, 0x58 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02096718(int);
extern int func_ov003_0220d498(void *, void *, int, int, int);
extern int func_ov003_02213ae4(void *, int, int, int, int, int);

typedef struct {
    char pad_00[0x7f0];
    int unk_7F0;
} UnkStruct_02219b38;
typedef struct {
    unsigned char unk_00;
    char pad_01[11];
} Arg;

int func_ov003_02219b38(Arg a)
{
    UnkStruct_02219b38 *x = (UnkStruct_02219b38 *) func_02096718(4);
    if (x != 0) {
        if (a.unk_00 != 0) {
            unsigned int f;
            if (x->unk_7F0 == 5) {
                f = 1;
            } else {
                f = 0;
            }
            return func_ov003_0220d498(x, &a, f, 6, -1);
        }
        return func_ov003_02213ae4(x, 1, 0, 0, 6, -1);
    }
    return 0;
}
