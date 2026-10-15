/* func_ov049_02261cb0 @ 0x02261cb0, 0x9c bytes, Thumb, module ov049
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02261cb0 {
  public:
    void method(void *);
};

typedef void (UnkStruct_02261cb0::*PMF)(void *);

extern "C" int func_ov049_02262084(void *unused0);
extern "C" int func_020a12e8(void);
extern "C" int strlen(void *);
extern "C" int strncmp(void *, void *, int);

extern void *data_ov049_02263298; // 0x02263298
extern PMF data_ov049_02263158;   // 0x02263158
extern PMF data_ov049_02263128;   // 0x02263128

extern "C" void func_ov049_02261cb0(UnkStruct_02261cb0 *self, void *arg)
{
    if (func_ov049_02262084(self) == 2) {
        if (func_020a12e8() != 0) {
            return;
        }
    }

    static PMF table[2] = {data_ov049_02263158, data_ov049_02263128};

    void *p = data_ov049_02263298;
    int tmp = strlen(p);
    int idx = strncmp((char *) self + 4, p, tmp) != 0 ? 1 : 0;

    (self->*table[idx])(arg);
}
