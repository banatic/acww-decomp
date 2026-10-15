/* func_ov052_022619a8 @ 0x022619a8, 0x5c bytes, Thumb, module ov052
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x71e];
    unsigned short unk_71E;
    unsigned short unk_720[3];
} UnkStruct_022619a8;

extern int func_0202ec58(UnkStruct_022619a8 *s);
extern int func_020b65b8(void);
extern int func_02030864(int x);
extern void func_ov052_02261908(UnkStruct_022619a8 *s, int flag);

int func_ov052_022619a8(UnkStruct_022619a8 *s)
{
    int r;
    int i;

    r = func_0202ec58(s);
    if (r == 0) {
        return 0;
    }
    if (func_020b65b8() != 0) {
        func_ov052_02261908(s, 1);
    } else {
        func_ov052_02261908(s, 0);
    }
    func_02030864(0);
    s->unk_71E = 0xfff1;
    for (i = 0; i < 3; i++) {
        s->unk_720[i] = 0xfff1;
    }
    return 1;
}
