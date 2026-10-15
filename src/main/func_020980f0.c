/* func_020980f0 @ 0x020980f0, 0x104 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_020980f0 {
    int pad_00[0x41];
};

extern int func_020984e8(void);
extern int func_020992fc(int);
extern int func_02099020(int, int);
extern int func_020983c4(int);
extern void func_02066694(struct UnkStruct_020980f0 *);
extern int func_02099870(int);
extern void func_02066024(struct UnkStruct_020980f0 *, u8 *, void *, void *, void *, int);
extern unsigned short func_02065ed0(struct UnkStruct_020980f0 *, int, int);
extern int func_02097a54(struct UnkStruct_020980f0 *);
extern void func_02098fd0(int, int);
extern void func_02066688(struct UnkStruct_020980f0 *);

extern u8 data_020e3114[];
extern u8 data_020e3118[];
extern u8 data_020e3100[];

void func_020980f0(int a)
{
    u8 c;
    struct UnkStruct_020980f0 s;
    int p, q, v, msg;

    p = func_020984e8();
    q = func_020992fc(p);
    if (a > 0 && func_02099020(p, 0x16)) {
        v = func_020983c4(q);
        func_02066694(&s);
        c = (u8) v;
        func_02066024(&s, &c, data_020e3118, data_020e3100, data_020e3114, func_02099870(p));
        msg = 0xfff1;
        switch (v) {
            case 1:
                msg = 0x13fe;
                break;
            case 4:
                msg = 0x13ff;
                break;
            case 7:
                msg = 0x1400;
                break;
            case 10:
                msg = 0x1401;
                break;
            case 13:
                msg = 0x1402;
                break;
            case 16:
                msg = 0x1403;
                break;
            case 20:
                msg = 0x1404;
                break;
        }
        if (msg != 0xfff1) {
            func_02065ed0(&s, msg, 1);
        }
        if (func_02097a54(&s)) {
            func_02098fd0(p, 0x16);
        }
        func_02066688(&s);
    }
}
