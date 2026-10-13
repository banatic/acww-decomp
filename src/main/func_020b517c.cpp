/* func_020b517c @ 0x020b517c, 0x160 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_020a8764(void *);
extern "C" int func_020a835c(void *);

class UnkStruct_020b517c {
  public:
    unsigned char pad_00[0x28];
    unsigned int unk_28; // offset 0x28
    unsigned int unk_2C; // offset 0x2c
    unsigned char pad_30[0x45 - 0x30];
    unsigned char unk_45; // offset 0x45
};

typedef void (UnkStruct_020b517c::*PMF)();

extern PMF data_0213dd98;
extern PMF data_020e5134;
extern PMF data_020e513c;
extern PMF data_020e5174;
extern PMF data_020e516c;
extern PMF data_020e517c;
extern PMF data_020e514c;
extern PMF data_020e5144;
extern PMF data_020e5184;
extern PMF data_020e515c;
extern PMF data_020e5164;
extern PMF data_020e5154;

extern "C" void func_020b517c(UnkStruct_020b517c *self)
{
    func_020a8764((char *) self + 0x28);
    unsigned int a = self->unk_28;
    unsigned int b = self->unk_2C;
    PMF pmf = data_0213dd98;

    if (a == 0 && b == 2) {
        pmf = data_020e5134;
    } else if (a == 0 && b == 3) {
        pmf = data_020e513c;
    } else if (a == 0 && b == 4) {
        pmf = data_020e5174;
    } else if (a == 0 && b == 5) {
        pmf = data_020e516c;
    } else if (a == 0 && b == 6) {
        pmf = data_020e517c;
    } else if (a == 0 && b == 9) {
        pmf = data_020e514c;
    } else if (a == 0 && b == 10) {
        pmf = data_020e5144;
    } else if (a == 0xff && b == 2) {
        pmf = data_020e5184;
    } else if (a == 4 && func_020a835c((char *) self + 0x28) != 0) {
        pmf = data_020e515c;
    } else if (a == 0xb && b == 0) {
        pmf = data_020e5164;
    } else if (a == 0xb && b == 3) {
        pmf = data_020e5154;
    }

    if (pmf != 0) {
        (self->*pmf)();
    } else {
        self->unk_45 = 0;
    }
}
