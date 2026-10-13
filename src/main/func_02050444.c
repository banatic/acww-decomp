/* func_02050444 @ 0x02050444, 0x144 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct Entry Entry;
struct Entry {
    u8 pad_00[0x40];
    int unk_40;
    u32 unk_44;
    u8 pad_48[0x44];
    int unk_8C[3];
    u8 unk_98[0x9c];
    u8 unk_134[0x30];
    int unk_164;
    u8 pad_168;
    u8 unk_169;
    u8 pad_16A[3];
};

extern Entry *data_021c8184;
extern int data_020dcd78;

extern void func_0205066c(void *self, int i);
extern void func_02050210(void *self, void *p, Entry *entry);
extern void func_02050140(void *self, void *p, Entry *entry);
extern void func_0205027c(void *self, void *p, Entry *entry);
extern void func_02055124(void *addr);
extern int func_0209d088(void *addr);
extern void NNS_G3dMdlSetMdlAlpha(int r, int a, int b);
extern void func_020044d0(void *a, int *b);
extern int func_02056f28(void *addr, int x);
extern void func_020044c0(void *a, int b, int c, int d);
extern void func_02050394(void *self, Entry *entry);
extern void func_020505f4(void *self, int i);

int func_02050444(void *self)
{
    Entry *entry;
    int i, a, b, zero;
    int tmp[3], *ptr;

    if (data_021c8184 == 0) {
        return 0;
    }
    entry = (Entry *) ((char *) data_021c8184 + 0x50);
    i = 0;
    a = 0;
    b = 0;
    zero = 0;

    while (i < data_020dcd78) {
        switch (entry->unk_44) {
            case 0:
                break;
            case 1:
                if (entry->unk_40 != ~zero) {
                    func_0205066c(self, i);
                }
                break;
            case 2:
                if ((unsigned) (entry->unk_40 - 0x38) <= 2) {
                    func_02050210(self, (char *) self + 0x600, entry);
                } else if (entry->unk_40 == 0x3b) {
                    func_02050140(self, (char *) self + 0x600, entry);
                } else {
                    func_0205027c(self, (char *) self + 0x600, entry);
                }
                break;
            case 3:
                if (entry->unk_40 == 0x3b) {
                    func_02055124((char *) entry + 0x98);
                    NNS_G3dMdlSetMdlAlpha(func_0209d088((char *) entry + 0x4c), a, entry->unk_164);
                } else {
                    if (entry->unk_40 != 0x38 && entry->unk_40 != 0x39 && entry->unk_40 != 0x3a) {
                        func_02055124((char *) entry + 0x98);
                        if (entry->unk_169 != 0) {
                            ptr = entry->unk_8C;
                            tmp[0] = ptr[0];
                            tmp[1] = ptr[1];
                            tmp[2] = ptr[2];
                            func_020044d0(entry, tmp);
                            if (func_02056f28((char *) entry + 0x134, 1) != 0) {
                                func_020044c0(entry, 0x84d, 0x7f, b);
                            }
                        }
                    }
                }
                func_02050394(self, entry);
                break;
            case 4:
                func_020505f4(self, i);
                break;
            default:
                break;
        }
        entry = (Entry *) ((char *) entry + 0x16c);
        i++;
    }
    return 1;
}