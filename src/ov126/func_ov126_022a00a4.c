/* func_ov126_022a00a4 @ 0x022a00a4, 0x6c bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xad];
    unsigned char unk_AD;
    unsigned char pad_AE[0x3dc4 - 0xad - 1];
    unsigned char unk_3DC4;
} UnkStruct_022a00a4;

extern int func_ov002_0220a620(unsigned char *ptr, int val);
extern int func_ov002_0220a784(unsigned char *ptr, int val);
extern void func_ov126_022a0ae0(UnkStruct_022a00a4 *p, int val);

int func_ov126_022a00a4(UnkStruct_022a00a4 *p)
{
    if (p->unk_AD == 3) {
        return 0;
    }
    if (func_ov002_0220a620(&p->unk_3DC4, 6) == 0) {
        if (func_ov002_0220a784(&p->unk_3DC4, 6) != 0) {
            func_ov126_022a0ae0(p, 0);
            return 1;
        }
    }
    if (p->unk_AD != 0) {
        return 0;
    }
    if (func_ov002_0220a784(&p->unk_3DC4, 7) != 0) {
        func_ov126_022a0ae0(p, 1);
        return 1;
    }
    return 0;
}
