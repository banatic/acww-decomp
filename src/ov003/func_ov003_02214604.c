/* func_ov003_02214604 @ 0x02214604, 0x40 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char unk_00;
    char pad_01;
    short unk_02;
    unsigned char unk_04;
} Sub7D4;

typedef struct {
    char pad_00[0x7d4];
    Sub7D4 sub;
} UnkStruct_02214604;

extern void func_020109a0(void *, int, int, int);
extern void func_0205eae0(void *, int, int, int);

void func_ov003_02214604(UnkStruct_02214604 *self, char *other)
{
    int idx = 0xc;
    Sub7D4 *p = &self->sub;
    p->unk_00 = 0;
    p->unk_02 = *(short *) (other + idx);
    p->unk_04 = 0xff;
    func_020109a0(self, 0x5b, 3, 0);
    func_0205eae0((char *) self + 0x5a0, 3, 3, 0);
}
