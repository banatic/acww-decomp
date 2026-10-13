/* func_ov049_02261960 @ 0x02261960, 0x9c bytes, Thumb, module ov049
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02261960;
typedef void (UnkStruct_02261960::*PMF)(int);

extern PMF data_ov049_02263168;
extern PMF data_ov049_02263130;
extern void *data_ov049_02263298;

extern "C" int func_ov049_02262084(void);
extern "C" int func_020a12e8(void);
extern "C" int strlen(void *p);
extern "C" int strncmp(void *a, void *b, int c);

extern "C" void func_ov049_02261960(UnkStruct_02261960 *self, int arg)
{
    if (func_ov049_02262084() == 2) {
        if (func_020a12e8() != 0) {
            return;
        }
    }

    static PMF tbl[2] = {data_ov049_02263168, data_ov049_02263130};

    void *p = data_ov049_02263298;
    int r = strlen(p);
    int s = strncmp((char *) self + 4, p, r);
    int idx = (s != 0);
    (self->*tbl[idx])(arg);
}
