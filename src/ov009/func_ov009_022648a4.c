/* func_ov009_022648a4 @ 0x022648a4, 0x40 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int lo, hi;
} Pair;

typedef struct {
    Pair p[6];
} Buf;

typedef struct {
    char pad_00[0xC4];
    int unk_C4;
    int unk_C8;
    int unk_CC;
    short unk_D0;
} SomeObj;

extern void func_020e96c8(Buf *out, int a, int b, int c);
extern void func_020e9774(Buf *out, int val);

void func_ov009_022648a4(SomeObj *obj, Buf *dst)
{
    Buf local;
    func_020e96c8(&local, obj->unk_C4, obj->unk_C8, obj->unk_CC);
    func_020e9774(&local, obj->unk_D0);
    *dst = local;
}
