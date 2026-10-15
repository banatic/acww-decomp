/* func_ov003_0220d880 @ 0x0220d880, 0x3c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x5a0];
    char unk_5A0;
    char pad_5A1[0x7d4 - 0x5a1];
    int unk_7D4;
} STR_0205A0;

extern void func_020109a0(int, int b, int c, unsigned short d);
extern void func_0205eae0(void *, int, int, int);
extern int func_0200f328(void *, int);

void func_ov003_0220d880(STR_0205A0 *self, void *message, int previous)
{
    self->unk_7D4 = -1;
    func_020109a0((int) (self), (int) (125), (int) (3), 0);
    func_0205eae0(&self->unk_5A0, 42, 0, 0);
    func_0200f328(self, 0x85d);
}
