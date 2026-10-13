/* func_ov004_0220e224 @ 0x0220e224, 0x1cc bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int words[26];
} Archive;
#define P(p, o) (*(u8 **) ((p) + (o)))
#define W(p, o) (*(unsigned int *) ((p) + (o)))
#define H(p, o) (*(u16 *) ((p) + (o)))
extern void *data_021fbe94;
extern char *data_ov004_0224fd4c;
extern char data_ov004_0224ff90[], data_ov004_0224ff94[], data_ov004_0224ffa4[], data_ov004_0224ffb4[], data_ov004_0224ffc4[],
    data_ov004_0224ffd4[];
extern char *func_ov004_0220e3f0(void *, int), *func_ov004_0220e41c(void *, int);
extern u8 *func_02064b2c(char *, void *, int, int *), *func_020e9948(void *, int);
extern void *func_0209d324(void *);
extern void MI_CpuCopy8(void *, void *, unsigned int);
extern void func_ov004_0220da10(void *, void *);
extern int NNS_FndMountArchive(Archive *, char *, void *);
extern u8 *NNS_FndGetArchiveFileByName(char *), *func_02107828(void *);
extern int func_02064328(char *, char *, ...);
extern u8 *NNS_G3dGetJntAnmSet(void *), *func_02107b44(void *, unsigned int);
extern u8 *NNS_G3dGetMatCAnmSet(void *), *func_02107b80(void *, unsigned int);
extern u8 *NNS_G3dGetVisAnmSet(void *);
extern u8 *func_02107cf0(void *, unsigned int);
extern u8 *NNS_G3dGetTexSRTAnmSet(void *), *func_02107bbc(void *, unsigned int);
extern u8 *NNS_G3dGetTexPatAnmSet(void *), *func_02107bf8(void *, unsigned int);
extern void func_ov004_0220da44(void *, void *, unsigned int), func_ov004_0220da38(void *, void *, unsigned int),
    func_ov004_0220da2c(void *, void *, unsigned int), func_ov004_0220da20(void *, void *, unsigned int),
    func_ov004_0220da14(void *, void *, unsigned int);
extern int func_0210285c(Archive *);
int func_ov004_0220e224(u8 *self, void *context, int variant)
{
    int size, size2;
    char name[32];
    Archive archive;
    unsigned int i;
    u8 *file;
    if (!P(self, 0)) {
        P(self, 0) = func_02064b2c(func_ov004_0220e3f0(self, variant), data_021fbe94, -4, &size);
        if (self[0x72]) {
            u8 *copy = func_020e9948(func_0209d324(context), size);
            MI_CpuCopy8(P(self, 0), copy, size);
            func_ov004_0220da10(self + 0x44, copy);
        }
    }
    if (!P(self, 4)) {
        char *path = func_ov004_0220e41c(self, variant);
        P(self, 4) = func_02064b2c(path, func_0209d324(context), 4, &size2);
    }
    if (!P(self, 8) && P(self, 4)) {
        if (NNS_FndMountArchive(&archive, data_ov004_0224ff90, P(self, 4))) {
            file = func_02107828(NNS_FndGetArchiveFileByName(data_ov004_0224fd4c));
            P(self, 8) = file + W(file + H(file, 0xe), 0xc);
            for (i = 0; i < 2; i++) {
                func_02064328(name, data_ov004_0224ff94, i);
                file = NNS_FndGetArchiveFileByName(name);
                if (file) {
                    func_ov004_0220da44(self + 0x44, func_02107b44(NNS_G3dGetJntAnmSet(file), 0), i);
                }
                func_02064328(name, data_ov004_0224ffa4, i);
                file = NNS_FndGetArchiveFileByName(name);
                if (file) {
                    func_ov004_0220da38(self + 0x44, func_02107b80(NNS_G3dGetMatCAnmSet(file), 0), i);
                }
                func_02064328(name, data_ov004_0224ffb4, i);
                file = NNS_FndGetArchiveFileByName(name);
                if (file) {
                    func_ov004_0220da2c(self + 0x44, func_02107cf0(NNS_G3dGetVisAnmSet(file), 0), i);
                }
                func_02064328(name, data_ov004_0224ffc4, i);
                file = NNS_FndGetArchiveFileByName(name);
                if (file) {
                    func_ov004_0220da20(self + 0x44, func_02107bbc(NNS_G3dGetTexSRTAnmSet(file), 0), i);
                }
                func_02064328(name, data_ov004_0224ffd4, i);
                file = NNS_FndGetArchiveFileByName(name);
                if (file) {
                    func_ov004_0220da14(self + 0x44, func_02107bf8(NNS_G3dGetTexPatAnmSet(file), 0), i);
                }
            }
            func_0210285c(&archive);
        }
    }
    return P(self, 0) && P(self, 8);
}
