/* func_ov004_0223af18 @ 0x0223af18, 0x9c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02064b2c(void *, void *, int, int);
extern int NNS_FndMountArchive(void *, void *, void *);
extern void *NNS_FndGetArchiveFileByName(void *);
extern void *NNS_G3dGetJntAnmSet(void *);
extern void *func_02107b44(void *, int);
extern void func_0210285c(void *);
extern char data_ov004_02256114, data_ov004_02256128, data_ov004_0225612c, data_ov004_02256148, data_ov004_02256164;

int func_ov004_0223af18(char *self)
{
    char buf[0x68];
    void *p;
    if (*(void **) (self + 0x14) == 0) {
        *(void **) (self + 0x14) = func_02064b2c(&data_ov004_02256114, *(void **) (self + 0x10), 4, 0);
        if (*(void **) (self + 0x14) == 0) {
            return 0;
        }
        if (NNS_FndMountArchive(buf, &data_ov004_02256128, *(void **) (self + 0x14)) != 0) {
            p = NNS_FndGetArchiveFileByName(&data_ov004_0225612c);
            if (p != 0) {
                *(void **) (self + 0x18) = func_02107b44(NNS_G3dGetJntAnmSet(p), 0);
            }
            p = NNS_FndGetArchiveFileByName(&data_ov004_02256148);
            if (p != 0) {
                *(void **) (self + 0x1c) = func_02107b44(NNS_G3dGetJntAnmSet(p), 0);
            }
            p = NNS_FndGetArchiveFileByName(&data_ov004_02256164);
            if (p != 0) {
                *(void **) (self + 0x20) = func_02107b44(NNS_G3dGetJntAnmSet(p), 0);
            }
            func_0210285c(buf);
            return 1;
        }
    }
    return 0;
}
