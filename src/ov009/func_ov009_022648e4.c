/* func_ov009_022648e4 @ 0x022648e4, 0x1f4 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

extern void *data_021c9b1c;
extern void *data_021fbe94;
extern char data_ov009_02265a28[], data_ov009_02265a2c[], data_ov009_02265a3c[], data_ov009_02265a4c[];
extern char data_ov009_02265a5c[], data_ov009_02265a6c[], data_ov009_02265a7c[], data_ov009_02265a8c[];
extern char data_ov009_02265a9c[];

typedef struct UnkStruct_022648e4 {
    int unk_00, unk_04, unk_08, unk_0C, unk_10, unk_14, unk_18, unk_1C;
    int unk_20[4];
    int unk_30[4];
    int unk_40, unk_44, unk_48, unk_4C;
} UnkStruct_022648e4;

extern UnkStruct_022648e4 *func_ov009_02264884(void *self);
extern int func_ov009_022655f8(void);
extern void *func_020b3b50(void *p);
extern void func_020b3c58(void *h, int *a, int *b, int *c, int *d);
extern void *func_02064b2c(void *a, void *b, int c, int d);
extern int NNS_FndMountArchive(void *arc, char *name, void *p);
extern int NNS_FndGetArchiveFileByName(char *name);
extern int func_ov009_02265598(void);
extern void func_02064328(char *dst, char *fmt, int i);
extern int NNS_G3dGetTexSRTAnmSet(int h);
extern int func_02107bbc(int h, int k);
extern int NNS_G3dGetTexPatAnmSet(int h);
extern int func_02107bf8(int h, int k);
extern int func_ov009_022655ac(int h);
extern void func_0210285c(void *arc);
extern int func_02064858(void *p);
extern int func_021077e8(void *p);
extern int func_020560e0(int h, int k);
extern int func_02056064(int h, int k);
extern int func_020561cc(int h, void *p);
extern void func_020e9898(void *p);

int func_ov009_022648e4(char *self, void *a, void *b, void *c)
{
    int ret;
    char buf1[0x1c];
    char buf2[0x20];
    char arc[0x6c];
    UnkStruct_022648e4 *r;
    void *h;
    void *p;
    unsigned int i;
    int res;

    ret = 0;
    r = func_ov009_02264884(self);
    if (func_ov009_022655f8() != 0) {
        return 1;
    }
    h = func_020b3b50(self + 0x136);
    if (h != 0) {
        func_020b3c58(h, &r->unk_40, &r->unk_44, &r->unk_48, &r->unk_4C);
    }
    if (a != 0) {
        p = func_02064b2c(a, data_021c9b1c, 4, 0);
        if (p != 0) {
            if (NNS_FndMountArchive(arc, data_ov009_02265a28, p) != 0) {
                if (NNS_FndGetArchiveFileByName(data_ov009_02265a2c) != 0) {
                    r->unk_08 = func_ov009_02265598();
                }
                if (NNS_FndGetArchiveFileByName(data_ov009_02265a3c) != 0) {
                    r->unk_0C = func_ov009_02265598();
                }
                if (NNS_FndGetArchiveFileByName(data_ov009_02265a4c) != 0) {
                    r->unk_10 = func_ov009_02265598();
                }
                for (i = 0; i < 4; i++) {
                    func_02064328(buf1, data_ov009_02265a5c, i);
                    res = NNS_FndGetArchiveFileByName(buf1);
                    if (res != 0) {
                        r->unk_20[i] = func_02107bbc(NNS_G3dGetTexSRTAnmSet(res), 0);
                    }
                }
                for (i = 0; i < 4; i++) {
                    func_02064328(&buf2[2], data_ov009_02265a6c, i);
                    res = NNS_FndGetArchiveFileByName(&buf2[2]);
                    if (res != 0) {
                        r->unk_30[i] = func_02107bf8(NNS_G3dGetTexPatAnmSet(res), 0);
                    }
                }
                r->unk_00 = func_ov009_022655ac(NNS_FndGetArchiveFileByName(data_ov009_02265a7c));
                res = NNS_FndGetArchiveFileByName(data_ov009_02265a8c);
                if (res != 0) {
                    r->unk_04 = func_ov009_022655ac(res);
                }
                r->unk_1C = NNS_FndGetArchiveFileByName(data_ov009_02265a9c);
                func_0210285c(arc);
            }
            ret = 1;
        }
    }
    if (b != 0 && func_02064858(b) != 0) {
        p = func_02064b2c(b, data_021fbe94, -4, 0);
        if (p != 0) {
            r->unk_14 = func_021077e8(p);
            if (func_020560e0(r->unk_14, 0) != 0) {
                r->unk_14 = func_020561cc(r->unk_14, data_021c9b1c);
            }
            func_020e9898(p);
        }
    }
    if (c != 0 && func_02064858(c) != 0) {
        p = func_02064b2c(c, data_021fbe94, -4, 0);
        if (p != 0) {
            r->unk_18 = func_021077e8(p);
            if (func_02056064(r->unk_18, 0) != 0) {
                r->unk_18 = func_020561cc(r->unk_18, data_021c9b1c);
            }
            func_020e9898(p);
        }
    }
    return ret;
}
