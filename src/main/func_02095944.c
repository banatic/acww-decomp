/* func_02095944 @ 0x02095944, 0x66 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02096718(int);
extern int func_0200fbe0(void *);
extern unsigned int *func_0200f27c(void *, int);
extern int func_0200c3b0(void *, int, int, int);
extern int func_ov003_02217c5c(void *, int, unsigned int, int, int, int, int, int);

typedef struct {
    char pad_00[0x5c];
    int unk_5C;
    char pad_60[4];
    int unk_64;
    char pad_68[0x26];
    short unk_8E;
} UnkStruct_02095944;

void func_02095944(unsigned int arg)
{
    void *p;
    int v;

    p = func_02096718(4);
    if (p == 0) {
        return;
    }

    v = func_0200fbe0(p);
    if (v == 0 || (v == 10 && arg == 1) || arg >= 2) {
        func_0200f27c(p, 1);
        func_0200c3b0(p, 3, 5, -1);
    } else {
        func_ov003_02217c5c(p, 0x10, arg, ((UnkStruct_02095944 *) p)->unk_5C, ((UnkStruct_02095944 *) p)->unk_64,
                            ((UnkStruct_02095944 *) p)->unk_8E, 6, -1);
    }
}
