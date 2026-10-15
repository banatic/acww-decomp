/* func_ov004_02222b54 @ 0x02222b54, 0x184 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#define W(p, o) (*(int *) ((p) + (o)))
typedef struct UnkStruct_02222b54 UnkStruct_02222b54;
struct UnkStruct_02222b54 {
    void (**vt)(UnkStruct_02222b54 *);
};
extern u8 *data_020ccf94;
extern void func_0201c054(void *self, int mode, int first, int second);
extern void func_ov004_02223388(void *self, int state);
extern void func_02016108(void *self, void *target);
extern void func_0201b6e4(void *self, int event, int participant);
extern void *func_0201c2a4(void *self, int participant);
extern int func_0201c0e0(void *self);
extern int func_020a7278(void);
extern int func_0201c014(void *self);
extern int func_0201c040(void *self, int *first, int *second);

void func_ov004_02222b54(u8 *self, int event, int who)
{
    switch (event) {
        case 3:
            self[0x560] = who;
            if (who != 4) {
                func_0201c054(self, 1, W(data_020ccf94, 0x64), who);
                func_ov004_02223388(self, 6);
            } else if (func_0201c0e0(self)) {
                int player = W(data_020ccf94, 0x64);
                func_0201c054(self, 1, player, player);
                func_ov004_02223388(self, 6);
            }
            break;
        case 0:
            self[0x560] = who;
            if (who != 4 && who != W(data_020ccf94, 0x64)) {
                func_0201c054(self, 1, who, who);
                func_ov004_02223388(self, 5);
            } else if (func_0201c0e0(self)) {
                int player = W(data_020ccf94, 0x64);
                func_0201c054(self, 1, player, player);
                ((UnkStruct_02222b54 *) (self + 0x658))->vt[2]((UnkStruct_02222b54 *) (self + 0x658));
                func_02016108(self + 0x658, func_0201c2a4(self, 4));
                func_ov004_02223388(self, 1);
            }
            break;
        case 8:
            if (who == 4) {
                if (func_020a7278()) {
                    func_0201c054(self, 1, W(data_020ccf94, 0x64), 4);
                    func_ov004_02223388(self, 3);
                } else {
                    func_0201c054(self, 1, 4, W(data_020ccf94, 0x64));
                    func_ov004_02223388(self, 4);
                }
            }
            break;
        case 4:
            if (func_0201c014(self) && func_0201c0e0(self)) {
                int first = 4, second = 4;
                if (func_0201c040(self, &first, &second)) {
                    if ((who != 4 && who == second) || who == 4) {
                        func_0201c054(self, 1, W(data_020ccf94, 0x64), 4);
                        func_ov004_02223388(self, 0);
                    }
                }
            }
            break;
    }
    func_0201b6e4(self, event, who);
}
