/* design_editor: 3 functions, module ov123
 * mwccarm 1.2/base -O4,s
 * func_ov123_02299684 @ 0x02299684, 0x58 bytes, Thumb
 * func_ov123_02299664 @ 0x02299664, 0x20 bytes, Thumb
 * func_ov123_02299650 @ 0x02299650, 0x12 bytes, Thumb
 */

struct UnkStruct_02299650 {
    char pad_00[0x9c];
    int unk_9C;
};

extern void func_ov123_02299930(void *p);
extern void func_ov123_02299640(void *p, int x);
extern void func_02001a7c(void);
extern void func_02001a1c(int x);
extern void func_ov002_0220a6b8(void *p);
extern void func_02001d60(int a, int b);
extern void func_02001b7c(int a);
extern void func_02001c58(int a, int b, int c, int d);
extern void func_02001a5c(void);
extern void func_02001b6c(int);
extern void func_ov002_0220a690(void *);

int func_ov123_02299650(struct UnkStruct_02299650 *s, int mask);

void func_ov123_02299684(void *self)
{
    if (func_ov123_02299650((struct UnkStruct_02299650 *) self, 0x20) != 0) {
        func_ov123_02299930(self);
        func_ov123_02299640(self, 0x00020000);
    }
    func_02001a7c();
    func_02001a1c(~5);
    func_ov002_0220a6b8((char *) self + 0x5030);
    func_02001d60(0x1f, 0);
    func_02001b7c(2);
    func_02001c58(0x40, 0x18, 0xc0, 0x98);
}

void func_ov123_02299664(void *arg0)
{
    func_02001a5c();
    func_ov002_0220a690((char *) arg0 + 0x5030);
    func_02001b6c(2);
}

int func_ov123_02299650(struct UnkStruct_02299650 *s, int mask)
{
    int tmp = s->unk_9C & mask;
    if (tmp != 0) {
        return 1;
    } else {
        return 0;
    }
}
