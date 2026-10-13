/* func_ov004_0222a504 @ 0x0222a504, 0x448 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#define PTR(o, k) (*(char **) ((o) + (k)))
#define BYTE(o, k) (*(u8 *) ((o) + (k)))
#define HALF(o, k) (*(u16 *) ((o) + (k)))
#define WORD(o, k) (*(int *) ((o) + (k)))
extern char data_ov004_02254b10[], data_ov004_02254b00[];
extern int func_02056f94(char *);
extern int func_02099fe8(void);
extern int func_0204bcdc(char *);
extern int func_0204bc64(void *);
extern int func_0203e1c4(void);
extern void func_020109fc(char *, int, int, int);
extern int func_0200fbe0(char *);
extern void func_0205eae0(char *, int, int, int);
extern int func_0203ee14(char *, char *);
extern int func_0203ee08(char *, char *);
extern void func_0200f27c(char *, int);
extern void func_0200f268(char *, int);
extern void func_020a8164(char *, char *);
extern int func_0209a110(void *);
extern int func_02043540(char *, u16);
extern int func_0206f6d4(u16);
extern int func_0206fbc0(void);
extern int func_0206fc6c(void);
extern void func_0203e19c(void);
extern u8 func_02008258(char *, int);
extern void func_0200d4e8(char *, int, int, int);
#define CALL_BASE(fn)                                                                                                         \
    {                                                                                                                         \
        char *base = self;                                                                                                    \
        if (self)                                                                                                             \
            base += 0xec;                                                                                                     \
        fn(self, base);                                                                                                       \
    }
#define START_DIALOG(n, res, k)                                                                                               \
    {                                                                                                                         \
        *state = (n);                                                                                                         \
        CALL_BASE(func_0203ee14);                                                                                             \
        func_0200f27c(self, 0x11);                                                                                            \
        func_020a8164(self + 0xec, (res));                                                                                    \
        BYTE(self, 0x10a) = (k);                                                                                              \
        WORD(PTR(self, 0x12c), 8) = 1;                                                                                        \
    }
#define CLOSE_DIALOG()                                                                                                        \
    {                                                                                                                         \
        CALL_BASE(func_0203ee08);                                                                                             \
        func_0200f268(self, 0x11);                                                                                            \
        func_0203e19c();                                                                                                      \
    }
#define START_ITEM()                                                                                                          \
    {                                                                                                                         \
        if (WORD(self, 0x810) == -1) {                                                                                        \
            *state = 4;                                                                                                       \
            func_020109fc(self, 0, 6, 6);                                                                                     \
            WORD(self, 0x810) = func_02043540(PTR(self, 0x800), HALF(self, 0x820));                                           \
        }                                                                                                                     \
    }
#define FINISH_ITEM()                                                                                                         \
    {                                                                                                                         \
        WORD(self, 0x7fc) = func_02008258(self, WORD(self, 0x7f0));                                                           \
        func_0200d4e8(self, 3, 1, -1);                                                                                        \
    }
void func_ov004_0222a504(char *self)
{
    u8 *state = (u8 *) (self + 0x7d9);
    // The ROM stores the two address-taken items at sp+4 and sp+6;
    // the leading word is never accessed.
    struct {
        unsigned int reserved;
        u16 copied, sentinel;
    } scratch;
    unsigned equal;
    int mode;
    switch (*state) {
        case 0:
            if (!func_02056f94(self + 0x2d0)) {
                break;
            }
            if (func_02099fe8() == -1) {
                if (func_0204bcdc(self + 0x820)) {
                    scratch.sentinel = 0xfff1;
                    equal = func_0204bc64(self + 0x820) == func_0204bc64(&scratch.sentinel) ? 1 : 0;
                } else {
                    equal = HALF(self, 0x820) == 0xfff1 ? 1 : 0;
                }
                if (!equal) {
                    if (!func_0203e1c4()) {
                        break;
                    }
                    func_020109fc(self, 0x6c, 3, 0);
                    mode = func_0200fbe0(self);
                    if (mode == 4) {
                        func_0205eae0(self + 0x5a0, 0, 9, 0);
                    } else if (mode == 3) {
                        func_0205eae0(self + 0x5a0, 0x13, 3, 0);
                    }
                    START_DIALOG(1, data_ov004_02254b10, 2);
                    break;
                }
            }
            scratch.copied = HALF(self, 0x820);
            func_0209a110(&scratch.copied);
            *state = 5;
            break;
        case 1:
            if (PTR(self, 0x12c) && WORD(PTR(self, 0x12c), 4)) {
                *state = 2;
                WORD(self, 0x81c) = 3;
            }
            break;
        case 2:
            if (WORD(self, 0x81c) >= 15) {
                *state = 3;
                START_ITEM();
            } else if (PTR(self, 0x12c) && !WORD(PTR(self, 0x12c), 4)) {
                if (WORD(self, 0x81c) == 5) {
                    if (func_0206f6d4(HALF(self, 0x820))) {
                        WORD(self, 0x81c) = 6;
                    }
                } else if (WORD(self, 0x81c) == 6) {
                    if (func_0206fbc0()) {
                        WORD(self, 0x81c) = 15;
                        WORD(self, 0x2e0) = 0x1000;
                        if (func_0206fc6c()) {
                            *state = 5;
                            CLOSE_DIALOG();
                        } else {
                            *state = 3;
                            START_ITEM();
                        }
                    }
                }
            }
            break;
        case 3:
            START_ITEM();
            break;
        case 4:
            if (PTR(self, 0x12c) && !WORD(PTR(self, 0x12c), 4)) {
                CLOSE_DIALOG();
                *state = 5;
                func_020109fc(self, 0, 6, 6);
            }
            break;
        case 5:
            FINISH_ITEM();
            func_0200f268(self, 13);
            WORD(self, 0x81c) = 15;
            break;
        case 6:
            if (func_0203e1c4()) {
                START_DIALOG(7, data_ov004_02254b10, 0);
            }
            break;
        case 7:
            if (PTR(self, 0x12c) && WORD(PTR(self, 0x12c), 4)) {
                *state = 8;
            }
            break;
        case 8:
            if (PTR(self, 0x12c) && !WORD(PTR(self, 0x12c), 4)) {
                CLOSE_DIALOG();
                *state = 9;
            }
            break;
        case 9:
            FINISH_ITEM();
            func_0200f268(self, 13);
            break;
        case 10:
            if (func_0203e1c4()) {
                START_DIALOG(11, data_ov004_02254b00, 1);
            }
            break;
        case 11:
            if (PTR(self, 0x12c) && WORD(PTR(self, 0x12c), 4)) {
                *state = 12;
            }
            break;
        case 12:
            if (PTR(self, 0x12c) && !WORD(PTR(self, 0x12c), 4)) {
                CLOSE_DIALOG();
                FINISH_ITEM();
            }
            break;
    }
}
