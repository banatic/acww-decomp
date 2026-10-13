/* func_020b3bd4 @ 0x020b3bd4, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_02064b2c(const char *, int, int, int);
extern void func_02064328(void *, const char *, int);
extern int NNS_FndMountArchive(void *, const char *, void *);
extern void func_0210285c(void *);
extern int NNS_FndGetArchiveFileByName(void *);
extern const char data_020e5110[];
extern int data_021fbe94;
extern void *data_021f4b44;
extern const char data_020e5120[];
extern const char data_020e5124[];
extern int data_021f4bf4[];

void func_020b3bd4(void)
{
    u8 name[0x20];
    u8 file[0x6c];
    unsigned int i;
    void *p;

    p = func_02064b2c(data_020e5110, data_021fbe94, 4, 0);
    data_021f4b44 = p;
    if (p != 0) {
        if (NNS_FndMountArchive(file, data_020e5120, p) != 0) {
            for (i = 0; i < 0x22; i++) {
                func_02064328(name, data_020e5124, i);
                data_021f4bf4[i] = NNS_FndGetArchiveFileByName(name);
            }
            func_0210285c(file);
        }
    } else {
        for (i = 0; i < 0x22; i++) {
            data_021f4bf4[i] = 0;
        }
    }
}
