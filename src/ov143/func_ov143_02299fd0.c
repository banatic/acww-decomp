/* func_ov143_02299fd0 @ 0x02299fd0, 0x44 bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220a314(void *);
extern void func_ov002_0220a2b4(void *);
extern int func_ov143_0229a0b0(void *);
extern int func_ov143_0229a030(void *);
extern void func_ov143_02299fa0(void *, int, int);

struct UnkStruct_02299fd0 {
    char pad_00[0xa4];
    unsigned char unk_A4;
    char pad_A5[7];
    char unk_AC;
};

void func_ov143_02299fd0(struct UnkStruct_02299fd0 *p)
{
    int x, y;
    if (p->unk_A4 == 0x12) {
        goto then;
    }
    if (p->unk_A4 != 0x13) {
        goto els;
    }
then:
    func_ov002_0220a314(&p->unk_AC);
    goto after;
els:
    func_ov002_0220a2b4(&p->unk_AC);
after:
    x = func_ov143_0229a0b0(p);
    y = func_ov143_0229a030(p);
    func_ov143_02299fa0(p, x, y);
}
