/* func_0204f934 @ 0x0204f934, 0xb8 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

struct Entry {
    u8 type;
    u8 count;
    u8 unk_02;
    u32 unk_04;
    u32 unk_08;
};

extern struct Entry data_021c80f4[12];

extern void func_0204fa5c(void *, u8);
extern void FS_GetOverlayFileID(void *, void *);
extern void func_0204f9ec(struct Entry *);
extern void OS_Terminate(void);
extern void func_0204fa18(struct Entry *, u8);

void func_0204f934(u8 id)
{
    struct Entry *found = 0;
    unsigned int i;
    char path[8];
    char buffer[44];
    u32 f4;
    u32 sum;
    for (i = 0; i < 0xc; i++) {
        struct Entry *e = &data_021c80f4[i];
        if (e->type == id) {
            e->count++;
            return;
        }
        if (*(volatile u8 *) &e->type == 0xff && found == 0) {
            found = e;
        }
    }
    func_0204fa5c(buffer, id);
    FS_GetOverlayFileID(path, buffer);
    {
        unsigned int j;
        u32 f4;
        u32 sum;
        j = 0;
        f4 = *(u32 *) (buffer + 4);
        sum = *(u32 *) (buffer + 8) + *(u32 *) (buffer + 0xc) + f4;
        for (; j < 0xc; j++) {
            struct Entry *e = &data_021c80f4[j];
            if (e->type == id) {
                continue;
            }
            if (*(volatile u8 *) &e->type == 0xff) {
                continue;
            }
            {
                u32 lo = e->unk_04;
                u32 hi = e->unk_08;
                if (lo + hi <= f4) {
                    continue;
                }
                if (sum <= lo) {
                    continue;
                }
                if (e->count == 0) {
                    func_0204f9ec(e);
                    if (found == 0) {
                        found = e;
                    }
                } else {
                    OS_Terminate();
                }
            }
        }
    }
    if (found != 0) {
        func_0204fa18(found, id);
    }
}
