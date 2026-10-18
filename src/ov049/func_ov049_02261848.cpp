/* func_ov049_02261848 @ 0x02261848, 0x118 bytes, Thumb, module ov049
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02261848;
typedef void (UnkStruct_02261848::*PMF)(int);

struct Entry {
    int key;
    PMF pmf;
};

extern PMF data_ov049_022631d0;
extern PMF data_ov049_02263270;
extern PMF data_ov049_02263090;
extern PMF data_ov049_02263098;
extern PMF data_ov049_022630a8;
extern PMF data_ov049_022630b8;
extern PMF data_ov049_02263180;
extern PMF data_ov049_02263120;
extern PMF data_ov049_02263288;
extern PMF data_ov049_02263278;
extern PMF data_ov049_022630a0;

extern "C" unsigned int func_0206837c(unsigned int a);
extern "C" int func_020ab504(unsigned int a);

extern "C" void func_ov049_02261848(UnkStruct_02261848 *self)
{
    static Entry table[11] = {
        {0x04, data_ov049_022631d0}, {0x15, data_ov049_02263270}, {0x1a, data_ov049_02263090}, {0x0b, data_ov049_02263098},
        {0x10, data_ov049_022630a8}, {0x1b, data_ov049_022630b8}, {0x17, data_ov049_02263180}, {0x28, data_ov049_02263120},
        {0x2d, data_ov049_02263288}, {0x2e, data_ov049_02263278}, {0x38, data_ov049_022630a0},
    };

    int i = 0;
    unsigned char *p = (unsigned char *) self + 0x1e;
    int offset;

    while ((unsigned int) i < 11) {
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
