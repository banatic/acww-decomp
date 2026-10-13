/* func_02039b90 @ 0x02039b90, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209d368(int, int);
extern void func_020399c8(void *);
extern void func_0203990c(void *);
extern void func_02039e34(void *);

struct UnkStruct_02039b90 {
    char pad_00[0xc];
    int c;
    char pad_10[0x3c];
    int unk_4C;
    char pad_50[0x58];
    int a8;
    int ac;
};

void func_02039b90(struct UnkStruct_02039b90 *p)
{
    int r;

    if (p->c == 0) {
        r = func_0209d368(0x138, 3) + 0xb;
    } else {
        r = func_0209d368(0x12e, 3) - 0xb;
    }
    p->unk_4C += r;

    p->a8--;
    if (p->a8 > 0) {
        goto out;
    }

    func_020399c8(p);
    func_0203990c(p);
    func_02039e34(p);

    if (p->c == 0) {
        r = func_0209d368(0x138, 4);
    } else {
        r = func_0209d368(0x12e, 4) + 0xa;
    }
    p->ac = r;

out:
    return;
}
