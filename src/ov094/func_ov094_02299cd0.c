/* func_ov094_02299cd0 @ 0x02299cd0, 0x64 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov094_02299c5c(void);
extern void func_ov094_02299c74(void *, void *);
extern void func_02004658(int);

typedef struct {
    int unk_00;
    int unk_04;
    char pad_08[11];
    unsigned char unk_13;
} UnkStruct_02299cd0;

void func_ov094_02299cd0(UnkStruct_02299cd0 *p, UnkStruct_02299cd0 *q)
{
    int a;
    int diff;
    a = func_ov094_02299c5c();
    if (a == p->unk_00) {
        return;
    }
    if (a > p->unk_00) {
        diff = a - p->unk_00;
    } else {
        diff = p->unk_00 - a;
    }
    if (diff < 30) {
        p->unk_13 = 1;
        return;
    }
    p->unk_13 = 14;
    p->unk_04 = diff / 13;
    if (p->unk_04 % 5 == 0) {
        p->unk_04--;
    }
    if (p->unk_04 <= 1) {
        p->unk_13 = 1;
    }
    func_ov094_02299c74(p, q);
    func_02004658(0x2d);
}
