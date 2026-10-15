/* func_ov129_0229c684 @ 0x0229c684, 0xd4 bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_ov002_0220a720(void *ptr, int x);
extern void func_ov002_02208090(void *ptr, int x);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern int func_ov129_0229b7ec(void *p, int x);
extern void func_0206fc4c(int x);
extern int func_0206fc8c(void);
extern int func_020b1a64(void *ptr);
extern void __register_global_object(void *object, void *destructor, void *node);
extern void func_020b1a24(void *ptr);
extern void func_020b1444(void *ptr);
extern void func_020b14ec(void *ptr, int a, int b);
extern void *func_020b1a54(void *object);
extern void RtcSendPxiCommand(int cmd);

extern u32 data_ov129_0229dcc0;
extern int data_ov129_0229dccc;

struct Dcd8 {
    u16 pad_00[15];
    u16 arr1[6];
    u16 arr2[16];
};
extern struct Dcd8 data_ov129_0229dcd8;

#define DestroyGlobal_020b1a54 ((void *) &func_020b1a54)

void func_ov129_0229c684(void *p)
{
    int i;
    int ret;

    func_ov002_0220a720((char *) p + 0x1d4, 3);
    func_ov002_02208090(p, 2);
    func_ov002_02208098((void *) (p), 10);

    if (func_ov129_0229b7ec(p, 4) != 0) {
        func_0206fc4c(0);
        RtcSendPxiCommand(0x28);
        return;
    }

    func_0206fc4c(1);
    ret = func_0206fc8c();

    if ((data_ov129_0229dcc0 & 1) == 0) {
        func_020b1a64(&data_ov129_0229dcd8);
        __register_global_object(&data_ov129_0229dcd8, DestroyGlobal_020b1a54, &data_ov129_0229dccc);
        data_ov129_0229dcc0 |= 1;
    }

    func_020b1a24(&data_ov129_0229dcd8);
    func_020b1444(&data_ov129_0229dcd8);

    for (i = 0; i < 16; i++) {
        data_ov129_0229dcd8.arr2[i] = ((u16 *) ((char *) p + 0x2f78))[i];
    }
    for (i = 0; i < 6; i++) {
        data_ov129_0229dcd8.arr1[i] = ((u16 *) ((char *) p + 0x2f6c))[i];
    }

    func_020b14ec(&data_ov129_0229dcd8, ret, 0);
    RtcSendPxiCommand(0x27);
}

#undef DestroyGlobal_020b1a54
