/* func_020186b0 @ 0x020186b0, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x28];
    int unk_28;
} CFake;

typedef struct {
    char pad_00[0x190];
    unsigned int unk_190;
    char pad_194[0x380];
    char unk_514;
} BFake;

extern int func_02057bf0(int);
extern CFake *func_02019de4(void *);
extern void func_02057b90(int, void *);
extern int func_02057c20(int);
extern int func_ov004_0222bf50(int);
extern void func_0200442c(void *, int, int, int);

void func_020186b0(void *a, void *b)
{
    if (!func_02057bf0(1)) {
        CFake *c;
        int res;

        c = func_02019de4(a);
        func_02057b90(9, b);
        res = func_02057c20(c->unk_28);
        if (res != 0 && func_ov004_0222bf50(res) != 0) {
            *((unsigned char *) a + 0x98) = 2;
        }
    } else {
        BFake *bp = (BFake *) b;

        if (((bp->unk_190 << 4) >> 16) == 8) {
            func_0200442c(&bp->unk_514, 99, 127, 0);
        }
    }
}
