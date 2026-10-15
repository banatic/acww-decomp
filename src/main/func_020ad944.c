/* func_020ad944 @ 0x020ad944, 0xd0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 b;
    u16 w;
} UnkStruct_020ad944;

extern int func_020ada14(void);
extern void func_02061e2c(void *d, void *s);
extern void *func_02062f90(void *d, void *s);
extern int func_0203d7c4(int x, void *p);
extern void func_02066694(void *p);
extern void *func_020984e8(void);
extern u8 func_020af028(void *p);
extern void *func_02099870(void *p);
extern void *func_0204c7f0(void *p);
extern int func_020979f0(void *p, int x);
extern void func_020af750(void *a, void *b, int c);
extern void *func_020996a0(void *p);
extern unsigned short *func_020adf50(void *record);
extern void func_020ade0c(void *a, void *b);
extern void func_02066688(void *p);
extern void *func_02062f4c(void *p);
extern void func_02066024(void *a, void *b, void *c, void *d, void *e, void *f);
extern unsigned short func_02065ed0(void *p, u16 v, int x);

extern u8 data_021f395c;
extern u8 data_020e4158;
extern u8 data_020e4180;
extern u8 data_020e415c;

int func_020ad944(void *arg)
{
    UnkStruct_020ad944 s1;
    u8 s2[0x28];
    u8 buffer[0x100];
    u8 *gptr;
    void *v1;
    void *v2;
    void *v3;

    if (func_020ada14() != 0) {
        func_02061e2c(&s1.w, arg);
        func_02062f90(s2, &s1.w);
        func_0203d7c4(1, s2);

        v1 = (((void *) (func_02066694(buffer), buffer)), func_020984e8());
        gptr = &data_021f395c;
        s1.b = func_020af028(gptr);
        v2 = func_02099870(v1);
        func_02066024(buffer, &s1, &data_020e4180, &data_020e415c, &data_020e4158, v2);
        func_02065ed0(buffer, s1.w, 1);

        v1 = func_0204c7f0(&s1.w);

        if (func_020979f0(buffer, 0) != 0) {
            v3 = func_020adf50(func_020996a0((((void *) (func_020af750(gptr, v1, 1), gptr)), func_020984e8())));
            func_020ade0c(v3, v1);
            func_02066688(buffer);
            func_02062f4c(s2);
            return 1;
        } else {
            func_02066688(buffer);
            func_02062f4c(s2);
        }
    }
    return 0;
}
