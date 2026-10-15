/* func_ov004_0222050c @ 0x0222050c, 0x1b4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 message;
    u16 item;
} UnkStruct_0222050c;
#define W(p, o) (*(int *) ((p) + (o)))
#define P(p, o) (*(u8 **) ((p) + (o)))
extern void *func_020160b4(void *);
extern void *func_0208150c(void *);
extern void *func_020984e8(void);
extern void *func_02099734(void *);
extern int func_020ab504(void *);
extern int func_0200366c(void *, void *, int, void *);
extern int func_02015828(void *, int);
extern int func_020644cc(int);
extern int func_0201b3c0(void *, int, int);
extern int func_0204c120(int, int, void *);
extern int func_02098a6c(void *, int, int, int);
extern void func_020157c8(void *, int, int);
extern void func_ov004_02220c34(void *, int);
extern int func_ov004_022206c0(void *);
extern void func_0201b3a4(void *, int);
extern void func_ov004_022209b4(void *);
extern void func_0206844c(void *, u8 *, void *);
extern int func_020154b4(void *, u16 *, int, int, int);
extern u8 data_ov004_02257e18[], data_ov004_02253ed0[];
void func_ov004_0222050c(u8 *self)
{
    int status;
    u8 message;
    UnkStruct_0222050c local;
    status = func_020ab504(func_020160b4(self));
    message = 255;
    if (P(self, 0x1a4)[0xac8] == 2) {
        switch (self[0x1e]) {
            case 6:
            case 7:
            case 10:
            case 11:
                func_0200366c(func_0208150c(P(P(self, 0x1a4), 0x830)), data_ov004_02257e18, 40, data_ov004_02253ed0);
                if (status == 0) {
                    func_020157c8(self, 0x38, 0);
                    func_02015828(self, 2);
                    func_ov004_02220c34(self, 1);
                } else {
                    message = func_020644cc(2) + 8;
                    func_ov004_022206c0(self);
                }
                break;
            case 12:
            case 13:
                func_0200366c(func_0208150c(P(P(self, 0x1a4), 0x830)), data_ov004_02257e18, 40, data_ov004_02253ed0);
                if (status == 0) {
                    void *inventory = func_02099734(func_020984e8());
                    int type = func_0201b3c0(P(self, 0x1a4), W(self, 0x1a8), 0);
                    local.item = func_0204c120(W(self, 0x1a8), 0, 0);
                    if (local.item == 0xfff1) {
                        local.item = 0x1492;
                    }
                    if (!func_02098a6c(inventory, W(self, 0x1a8), 1, 0)) {
                        message = func_020644cc(2) + 18;
                    } else {
                        switch (type) {
                            case 0:
                                func_020154b4(self, &local.item, 0, 5, 0);
                                func_0201b3a4(P(self, 0x1a4), W(self, 0x1a8));
                                message = func_020644cc(2) + 14;
                                func_ov004_022209b4(self);
                                break;
                            case 1:
                                func_020154b4(self, &local.item, 0, 5, 0);
                                message = func_020644cc(2) + 14;
                                func_0201b3a4(P(self, 0x1a4), W(self, 0x1a8));
                                func_ov004_022209b4(self);
                                break;
                            case 2:
                            default:
                                break;
                        }
                    }
                } else {
                    message = func_020644cc(2) + 16;
                    func_ov004_022206c0(self);
                }
                break;
        }
        if (message != 255) {
            local.message = message;
            func_0206844c(P(self, 0x40), &local.message, data_ov004_02257e18);
        }
    }
}
