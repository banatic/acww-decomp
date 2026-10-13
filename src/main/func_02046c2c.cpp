/* func_02046c2c @ 0x02046c2c, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

// The empty destructor keeps the eight bytes the ROM reserves for this local.
class Scope {
  public:
    Scope() {}
    ~Scope() {}
    int a, b;
};

extern "C" void func_02046d50(int);
extern "C" void func_02046d38(int);
extern "C" void func_02046d14(int);
extern "C" void func_02046cac(int);
extern "C" unsigned char data_021dc7a8[];

extern "C" void func_02046c2c(int p)
{
    unsigned short *cur;
    Scope scope;
    func_02046d50(p);
    func_02046d38(p);
    func_02046d14(p);
    func_02046cac(p);

    for (cur = (unsigned short *) ((int) data_021dc7a8 + 0x172c0); cur < (unsigned short *) ((int) data_021dc7a8 + 0x172de);
         cur++) {
        unsigned short val = *cur;
        if (val < 0x1531 || val > 0x153a) {
            continue;
        }
        {
            int r;
            if (val >= 0x1531 && val <= 0x153a) {
                r = val - 0x1531;
            } else {
                r = -1;
            }
            {
                unsigned short out;
                if ((unsigned int) r < 10) {
                    out = (unsigned short) (0x154a + r);
                } else {
                    out = 0x154a;
                }
                *cur = out;
            }
        }
    }
}
