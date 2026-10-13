/* func_02098c2c @ 0x02098c2c, 0x94 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

// The empty destructor keeps the eight bytes the ROM reserves for this local.
class Scope {
  public:
    Scope() {}
    ~Scope() {}
    int a, b;
};

extern "C" unsigned short *func_02098f48(int, int);
extern "C" int func_02098e8c(int, int);

extern "C" int func_02098c2c(int arg0, int arg1)
{
    Scope scope;
    unsigned short *arr;
    int i;
    int candidate;
    int threshold;
    int l1;
    int l2;
    int l3;
    int l4;
    int n;
    arr = func_02098f48(arg0, 0);
    if (arg1 == 1) {
        threshold = 0x6b;
    } else {
        threshold = 0x6a;
    }

    i = 0;
    candidate = ~i;
    l2 = i;
    l3 = candidate;
    l1 = i;
    l4 = i;

    do {
        if (l1 | (*arr >= 0x1492 && *arr <= 0x14fd)) {
            if (func_02098e8c(arg0, i) == 0) {
                if (l2 | (*arr >= 0x1492 && *arr <= 0x14fd)) {
                    n = *arr - 0x1492;
                } else {
                    n = l3;
                }
                if (n < threshold || (candidate == ~l4 && n == threshold)) {
                    threshold = n;
                    candidate = i;
                }
            }
        }
        arr++;
        i++;
    } while (i < 15);

    return candidate;
}
