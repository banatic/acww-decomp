/* func_02084058 @ 0x02084058, 0x108 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int a, b;
} UnkStruct_02084058;

typedef struct {
    u8 pad_00[0x64];
    int unk_64;
} UnkStruct_02084058_2;

extern void func_0209e474(UnkStruct_02084058 *);
extern int func_02084af0(void);
extern int func_02084ad0(void);
extern int func_020b65c4(void);
extern int func_02073dd4(UnkStruct_02084058_2 *, int);
extern int func_02085d2c(int, UnkStruct_02084058 *);
extern int func_020881c4(void *);
extern int func_02084d5c(u16 *, void *, int);

extern volatile u8 data_020e54a8;
extern UnkStruct_02084058_2 *data_020ccf94;
extern u8 data_021f3278[];
extern u8 data_020e1d8c[];
extern int data_020d0644;

int func_02084058(int a)
{
    u16 h;
    UnkStruct_02084058 t;
    int c;

    t.a = 0;
    t.b = 0;
    func_0209e474(&t);
    if (!func_02084af0() && !func_02084ad0()) {
        if (a == 0 || ((c = (data_020e54a8 == 0)) != 0 && func_020b65c4() != 0x2c)) {
            if (!func_02073dd4(data_020ccf94, data_020ccf94->unk_64) && !func_02085d2c(0x3b, &t) && !func_02085d2c(0x3c, &t) &&
                !func_02085d2c(0x3d, &t) && !func_02085d2c(0x3e, &t) && !func_02085d2c(0x3f, &t) && !func_02085d2c(0x40, &t) &&
                !func_02085d2c(0x41, &t) && !func_02085d2c(0x42, &t) && !func_02085d2c(0x43, &t) && !func_02085d2c(0x44, &t) &&
                func_020881c4(data_021f3278)) {
                h = 0xd020;
                return func_02084d5c(&h, data_020e1d8c, data_020d0644);
            }
        }
    }
    return 0;
}
