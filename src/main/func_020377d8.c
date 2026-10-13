/* func_020377d8 @ 0x020377d8, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020da37c[];
extern unsigned char data_020da390[];
extern unsigned char data_020da3a4[];
extern void *data_021fbe94;

extern void func_02064328(void *, void *, int, int);
extern int func_02064b2c(void *, void *, int, int);
extern int NNS_FndMountArchive(void *, void *, int);
extern void *NNS_FndGetArchiveFileByName(void *);
extern void func_0210285c(void *);
extern int func_020e9948(void *, int);
extern void MI_CpuCopy8(void *, int, int);
extern void func_020e9898(void *);

void *func_020377d8(int p0, void *p1)
{
    unsigned char buf[0x8c];
    int r5;
    void *r4;

    func_02064328(buf, data_020da37c, p0 >> 4, p0);
    r5 = func_02064b2c(buf, data_021fbe94, -4, 0);
    r4 = 0;

    if (NNS_FndMountArchive(buf + 0x20, data_020da390, r5) != 0) {
        void *r7 = NNS_FndGetArchiveFileByName(data_020da3a4);
        func_0210285c(buf + 0x20);
        r4 = (void *) func_020e9948(p1, 0x180);
        MI_CpuCopy8(r7, (int) r4, 0x180);
    }

    if (r5 != 0) {
        func_020e9898((void *) r5);
    }

    return r4;
}