/* func_ov111_0229f430 @ 0x0229f430, 0x94 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x9e];
    unsigned char unk_9E;
} UnkStruct_0229f430;

extern int func_ov002_022088ac(int);
extern int func_ov002_0220889c(int);
extern int func_ov002_022088cc(int);
extern int func_ov002_022088bc(int);
extern int func_02051c8c_unk(void *, int);

int func_ov111_0229f430(UnkStruct_0229f430 *a, int b)
{
    if (b == 0) {
        return 0;
    }
    if (func_ov002_022088ac(b)) {
        if (a->unk_9E != 0) {
            a->unk_9E--;
            return 1;
        }
    } else {
        if (func_ov002_0220889c(b)) {
            int res = func_02051c8c_unk((char *) a + 0x3d16, 0x10);
            if (a->unk_9E + 1 > res) {
                goto ret_4;
            }
            a->unk_9E++;
            return 1;
        ret_4:
            return 4;
        }
    }
    if (func_ov002_022088cc(b)) {
        return 2;
    }
    if (func_ov002_022088bc(b)) {
        return 3;
    }
    return 0;
}
