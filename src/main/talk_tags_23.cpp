/* talk_tags_23: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206ace4 @ 0x0206ace4, 0x180 bytes, Thumb
 * func_0206ac64 @ 0x0206ac64, 0x80 bytes, Thumb
 */

#include "cpp/main/Base_0206ac64.h"

struct UnkStruct_0206ace4;

typedef void (UnkStruct_0206ace4::*PMF)(void);

struct UnkStruct_0206ace4 {
    unsigned char pad_00[0x3c];
    int unk_3C;
};

extern PMF data_020de8fc;
extern PMF data_020de90c;
extern PMF data_020de91c;
extern PMF data_020dea14;
extern PMF data_020dea1c;
extern PMF data_020dea24;
extern PMF data_020dea34;
extern PMF data_020dea4c;
extern PMF data_020dea5c;
extern PMF data_020dea6c;
extern PMF data_020dea74;
extern PMF data_020dea8c;
extern PMF data_020dea94;
extern PMF data_020deaa4;
extern PMF data_020deaac;
extern PMF data_020dead4;
extern PMF data_020deaec;
extern PMF data_020deb04;
extern PMF data_020deb44;
extern PMF data_020deb8c;
extern PMF data_020debcc;
extern int data_021cda7c;
extern PMF data_021ce01c[21];

typedef void (Base_0206ac64::*Pmf)();

extern Pmf __ptmf_null;
extern int data_021cda74;
extern Pmf data_020dec64;
extern Pmf data_020deca4;
extern Pmf data_021cdad4[3];

extern "C" void func_0206ace4(UnkStruct_0206ace4 *obj)
{
    if (!(data_021cda7c & 1)) {
        data_021ce01c[0] = data_020de8fc;
        data_021ce01c[1] = data_020de90c;
        data_021ce01c[2] = data_020de91c;
        data_021ce01c[3] = data_020dea14;
        data_021ce01c[4] = data_020dea1c;
        data_021ce01c[5] = data_020dea24;
        data_021ce01c[6] = data_020dea34;
        data_021ce01c[7] = data_020dea4c;
        data_021ce01c[8] = data_020dea5c;
        data_021ce01c[9] = data_020dea6c;
        data_021ce01c[10] = data_020dea74;
        data_021ce01c[11] = data_020dea8c;
        data_021ce01c[12] = data_020dea94;
        data_021ce01c[13] = data_020deaa4;
        data_021ce01c[14] = data_020deaac;
        data_021ce01c[15] = data_020dead4;
        data_021ce01c[16] = data_020deaec;
        data_021ce01c[17] = data_020deb04;
        data_021ce01c[18] = data_020deb44;
        data_021ce01c[19] = data_020deb8c;
        data_021ce01c[20] = data_020debcc;
        data_021cda7c |= 1;
    }
    PMF f;

    f = data_021ce01c[obj->unk_3C];
    (obj->*f)();
}

extern "C" void func_0206ac64(Base_0206ac64 *self)
{
    if (!(data_021cda74 & 1)) {
        data_021cdad4[0] = data_020dec64;
        data_021cdad4[1] = __ptmf_null;
        data_021cdad4[2] = data_020deca4;
        data_021cda74 |= 1;
    }
    Pmf p = data_021cdad4[self->unk_3C];
    (self->*p)();
}
