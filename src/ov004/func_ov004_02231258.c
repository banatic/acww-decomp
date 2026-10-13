/* func_ov004_02231258 @ 0x02231258, 0x1fc bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#define W(p, o) (*(int *) ((p) + (o)))
extern u8 data_ov004_022478cc[], data_ov004_022478c8[], data_021dc7a8[], data_ov004_022478dc[];
extern void *func_0206837c(void *);
extern int func_020ab504(void *);
extern int func_020b65c4(void);
extern int func_0209f150(void *, int);
extern void func_0209f100(void *, int), func_0209f128(void *, int);
extern void func_0203d480(int), func_0203d448(int), func_0203d41c(int);
extern int func_0203d438(void), func_02004634(int);
extern void func_0203d394(void), func_0206844c(void *, u8 *, void *);
void func_ov004_02231258(u8 *self)
{
    void *context = *(void **) (self + 0x2d0);
    int choice = func_020ab504(func_0206837c(context));
    int response = 0;
    switch (self[0x2ae]) {
        case 0xe:
        case 0x1f:
            if (func_020b65c4() == 6) {
                response = data_ov004_022478cc[choice];
            } else {
                response = data_ov004_022478c8[choice];
            }
            if (response == 0x17) {
                if (func_0209f150(data_021dc7a8, 0x13) && func_0209f150(data_021dc7a8, 0x14)) {
                    response = 0x42;
                } else if (!func_0209f150(data_021dc7a8, 0x13) && func_0209f150(data_021dc7a8, 0x14)) {
                    response = 0x41;
                } else if (func_0209f150(data_021dc7a8, 0x13) && !func_0209f150(data_021dc7a8, 0x14)) {
                    response = 0x40;
                } else if (!func_0209f150(data_021dc7a8, 0x13) && !func_0209f150(data_021dc7a8, 0x14)) {
                    response = 0x3f;
                }
            }
            break;
        case 0x14:
            switch (choice) {
                case 0:
                    func_0203d480(response);
                    break;
                case 1:
                    func_0203d480(1);
                    break;
            }
            break;
        case 0x17:
            switch (choice) {
                case 0:
                    func_0209f100(data_021dc7a8, 0x13);
                    break;
                case 1:
                    func_0209f128(data_021dc7a8, 0x13);
                    break;
            }
            break;
        case 0x1a:
            switch (choice) {
                case 0:
                    func_0209f100(data_021dc7a8, 0x14);
                    break;
                case 1:
                    func_0209f128(data_021dc7a8, 0x14);
                    break;
            }
            break;
        case 0x1b:
            switch (choice) {
                case 0:
                    func_0203d448(1);
                    func_02004634(response);
                    response = 0x1c;
                    break;
                case 1:
                    func_0203d448(response);
                    func_02004634(1);
                    response = 0x1e;
                    break;
            }
            break;
        case 0x11:
            W(self, 0x640) = func_0203d438();
            switch (choice) {
                case 0:
                    func_0203d41c(response);
                    break;
                case 1:
                    func_0203d41c(1);
                    break;
                case 2:
                    func_0203d41c(2);
                    break;
            }
            break;
        case 0x2a:
        case 0x2b:
        case 0x2c:
            if (choice == 1) {
                func_0203d41c(W(self, 0x640));
            }
            break;
    }
    if (func_020b65c4() != 6) {
        func_0203d394();
    }
    if (response != 0) {
        u8 byte = response;
        func_0206844c(context, &byte, data_ov004_022478dc);
    }
}
