/* func_ov004_0222c3f4 @ 0x0222c3f4, 0x128 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    void *file, *model, *jnt[13], *mat[13], *srt[13];
} RmoHolder;
extern void *data_021c9b24;
extern char data_ov004_02254b90[], data_ov004_02254b94[], data_ov004_02254ba4[], data_ov004_02254bb4[], data_ov004_02254bc4[];
extern void *func_02064b2c(const char *, void *, int, int);
extern int NNS_FndMountArchive(void *, const char *, void *);
extern void *NNS_FndGetArchiveFileByName(const char *);
extern char *func_02107828(void *);
extern int func_02064328(char *, const char *, ...);
extern void *NNS_G3dGetJntAnmSet(void *), *NNS_G3dGetMatCAnmSet(void *), *NNS_G3dGetTexSRTAnmSet(void *);
extern void *func_02107b44(void *, int), *func_02107b80(void *, int), *func_02107bbc(void *, int);
extern void func_0210285c(void *);
int func_ov004_0222c3f4(RmoHolder *self, const char *name)
{
    // Preserve the ROM sprintf scratch and archive frame offsets.
    struct {
        char buf[0x24];
        int arc[0x68 / 4];
    } frame;
    void *p;
    char *q;
    u32 i;

    if (self->file != 0) {
        goto failed;
    }
    self->file = func_02064b2c(name, data_021c9b24, 4, 0);
    if (self->file == 0) {
        goto failed;
    }
    if (NNS_FndMountArchive(frame.arc, data_ov004_02254b90, self->file) == 0) { // data_02254b90 = ROM 0x02254b90
        goto failed;
    }

    p = NNS_FndGetArchiveFileByName(data_ov004_02254b94); // ROM 0x02254b94
    if (p != 0) {
        q = func_02107828(p);
        self->model = q + *(u32 *) (q + *(u16 *) (q + 0xe) + 0xc);
    }

    for (i = 0; i < 13; i++) {
        func_02064328(frame.buf, data_ov004_02254ba4, i); // ROM 0x02254ba4
        p = NNS_FndGetArchiveFileByName(frame.buf);
        if (p != 0) {
            self->jnt[i] = func_02107b44(NNS_G3dGetJntAnmSet(p), 0);
        }
        if (self->jnt[i] == 0) {
            break;
        }
    }
    for (i = 0; i < 13; i++) {
        func_02064328(frame.buf, data_ov004_02254bb4, i); // ROM 0x02254bb4
        p = NNS_FndGetArchiveFileByName(frame.buf);
        if (p != 0) {
            self->mat[i] = func_02107b80(NNS_G3dGetMatCAnmSet(p), 0);
        }
        if (self->mat[i] == 0) {
            break;
        }
    }
    for (i = 0; i < 13; i++) {
        func_02064328(frame.buf, data_ov004_02254bc4, i); // ROM 0x02254bc4
        p = NNS_FndGetArchiveFileByName(frame.buf);
        if (p != 0) {
            self->srt[i] = func_02107bbc(NNS_G3dGetTexSRTAnmSet(p), 0);
        }
        if (self->srt[i] == 0) {
            break;
        }
    }

    func_0210285c(frame.arc);
    return 1;
failed:
    return 0;
}
