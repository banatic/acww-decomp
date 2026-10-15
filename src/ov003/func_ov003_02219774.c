/* func_ov003_02219774 @ 0x02219774, 0x50 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02096718(int);
extern int func_0203e140(void);
extern int func_02008258(void *, int);
extern int func_0200d4e8(void *, int, int, int);
extern int func_02095518(int, int, int);

typedef struct {
    char pad_00[0x7f0];
    int unk_7F0;
    char pad_7F4[8];
    int unk_7FC;
} UnkStruct_02219774;

int func_ov003_02219774(void)
{
    UnkStruct_02219774 *x = (UnkStruct_02219774 *) func_02096718(4);
    int v;
    if (x != 0) {
        func_0203e140();
        v = x->unk_7F0;
        if (v != 0x77) {
            x->unk_7FC = func_02008258(x, v);
            func_0200d4e8(x, 3, 1, -1);
        }
        func_02095518(0, 0, 4);
        return 1;
    }
    return 0;
}
