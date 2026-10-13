/* func_ov004_02223704 @ 0x02223704, 0x20c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

class Action {
  public:
    virtual void slot0() = 0;
    virtual void slot1() = 0;
    virtual void reset() = 0;
};
extern "C" {
extern char *data_020ccf94;
extern void func_0201c054(char *, int, int, int);
extern void func_ov004_022249b4(char *, int);
extern int func_0201c0e0(char *);
extern int func_0201c2a4(char *, int);
extern void func_02016108(char *, int);
extern int func_02073d90(char *);
extern short *func_0209d358(u16, u16);
extern int func_020a7278(void);
extern int func_0201c014(char *);
extern int func_0201c040(char *, int *, int *);
extern void func_0201b6e4(char *, int, int);
}
#define OWNER (*(int *) (data_020ccf94 + 0x64))
extern "C" void func_ov004_02223704(char *self, int event, int player)
{
    switch (event) {
        case 3:
            *(u8 *) (self + 0x560) = player;
            if (player != 4) {
                func_0201c054(self, 1, OWNER, player);
                func_ov004_022249b4(self, 7);
            } else if (func_0201c0e0(self)) {
                func_0201c054(self, 1, OWNER, OWNER);
                func_ov004_022249b4(self, 7);
            }
            break;
        case 1:
            *(u8 *) (self + 0x560) = player;
            if (player != 4 && player != OWNER) {
                func_0201c054(self, 1, player, player);
                func_ov004_022249b4(self, 6);
            } else if (func_0201c0e0(self)) {
                char *context = data_020ccf94;
                func_0201c054(self, 1, *(int *) (context + 0x64), *(int *) (context + 0x64));
                ((Action *) (self + 0x658))->reset();
                func_02016108(self + 0x658, func_0201c2a4(self, 4));
                if (func_02073d90(context) || *func_0209d358(0, 0x4a) != 0) {
                    func_ov004_022249b4(self, 1);
                } else {
                    func_ov004_022249b4(self, 4);
                }
            }
            break;
        case 0:
            *(u8 *) (self + 0x560) = player;
            if (player != 4 && player != OWNER) {
                func_0201c054(self, 1, player, player);
                func_ov004_022249b4(self, 6);
            } else if (func_0201c0e0(self)) {
                func_0201c054(self, 1, OWNER, OWNER);
                ((Action *) (self + 0x658))->reset();
                func_02016108(self + 0x658, func_0201c2a4(self, 4));
                func_ov004_022249b4(self, 1);
            }
            break;
        case 8:
            if (player == 4) {
                if (func_020a7278()) {
                    func_0201c054(self, 1, OWNER, 4);
                    func_ov004_022249b4(self, 3);
                } else {
                    func_0201c054(self, 1, 4, OWNER);
                    func_ov004_022249b4(self, 5);
                }
            }
            break;
        case 4:
            if (func_0201c014(self) && func_0201c0e0(self)) {
                int a = 4, b = 4;
                if (func_0201c040(self, &a, &b)) {
                    if ((player != 4 && player == b) || player == 4) {
                        func_0201c054(self, 1, OWNER, 4);
                        func_ov004_022249b4(self, 0);
                    }
                }
            }
            break;
    }
    func_0201b6e4(self, event, player);
}
