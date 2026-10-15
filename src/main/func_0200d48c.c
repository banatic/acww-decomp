/* func_0200d48c @ 0x0200d48c, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0200f748(unsigned char *);
extern void func_020109fc(unsigned char *, int, int, int);
extern void func_0200eebc(unsigned char *);
extern void func_0200f268(unsigned char *, int);
extern int func_02095518(int, int, int);

void func_0200d48c(unsigned char *self, unsigned char *other, int flag)
{
    unsigned short val;

    if (func_0200f748(self)) {
        return;
    }

    val = *(unsigned short *) (other + 0xc);

    self[0x7d4] = (flag == 4) ? 1 : 0;

    func_020109fc(self, 0, val, val);
    func_0200eebc(self);
    func_0200f268(self, 9);

    *(unsigned int *) (self + 0x168) = 0;
    self[0x16c] = 0;

    func_02095518(0, 0, 4);
}
