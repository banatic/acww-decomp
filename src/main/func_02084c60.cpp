/* func_02084c60 @ 0x02084c60, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02084c60;
typedef int (UnkStruct_02084c60::*Pmf)();
class UnkStruct_02084c60 {
  public:
    int m0();
    int m1();
    char pad_00[0x40];
};

struct UnkStruct_02084c60_2 {
    Pmf pmf;
    unsigned char prio;
};

extern UnkStruct_02084c60_2 data_020e1d08[];
extern unsigned char data_020e1ca8[];
extern "C" int func_020b65c4(void);
extern "C" int func_02084d08(int a, unsigned int b, int c, int d);

extern "C" int func_02084c60(UnkStruct_02084c60 *self)
{
    int k;
    int zero;
    UnkStruct_02084c60_2 *e;
    int i;
    int v;

    e = data_020e1d08;
    k = func_020b65c4();
    i = 0;
    zero = 0;
    while (i < 11) {
        if (e->prio <= data_020e1ca8[0xf]) {
            break;
        }
        if (e->pmf) {
            v = (self->*(e->pmf))();
            if (v != 0) {
                if (func_02084d08(v, e->prio, k, zero) != 0) {
                    return 1;
                }
            }
        }
        e++;
        i++;
    }
    return 0;
}
