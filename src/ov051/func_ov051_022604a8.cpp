/* func_ov051_022604a8 @ 0x022604a8, 0x140 bytes, Thumb, module ov051
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_022604a8;
typedef void (UnkStruct_022604a8::*PMF)(int);

struct Entry {
    int key;
    PMF pmf;
};

extern PMF data_ov051_0226168c;
extern PMF data_ov051_022616cc;
extern PMF data_ov051_022616dc;
extern PMF data_ov051_02261664;
extern PMF data_ov051_022615dc;
extern PMF data_ov051_022615cc;
extern PMF data_ov051_022615d4;
extern PMF data_ov051_022615fc;
extern PMF data_ov051_02261614;
extern PMF data_ov051_022616a4;
extern PMF data_ov051_0226172c;
extern PMF data_ov051_02261654;
extern PMF data_ov051_022615ec;
extern PMF data_ov051_0226166c;

extern "C" unsigned int func_0206837c(unsigned int a);
extern "C" int func_020ab504(unsigned int a);

extern "C" void func_ov051_022604a8(UnkStruct_022604a8 *self)
{
    static Entry table[14] = {
        {0, data_ov051_0226168c}, {0, data_ov051_022616cc}, {0, data_ov051_022616dc}, {0, data_ov051_02261664},
        {0, data_ov051_022615dc}, {0, data_ov051_022615cc}, {0, data_ov051_022615d4}, {0, data_ov051_022615fc},
        {0, data_ov051_02261614}, {0, data_ov051_022616a4}, {0, data_ov051_0226172c}, {0, data_ov051_02261654},
        {0, data_ov051_022615ec}, {0, data_ov051_0226166c},
    };

    int i = 0;
    unsigned char *p = (unsigned char *) self + 0x1e;
    int offset;

    while ((unsigned int) i < 14) {
        offset = i * 12;
        int key = table[i].key;
        if (key == *p) {
            int arg = func_020ab504(func_0206837c(*(unsigned int *) ((char *) self + 0x40)));
            PMF *pmf = (PMF *) ((char *) table + offset + 4);
            (self->**pmf)(arg);
        }
        i++;
    }
}
