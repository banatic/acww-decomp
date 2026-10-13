/* func_02037608 @ 0x02037608, 0x164 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_021c9b24;
extern void func_02064328(char *dst, const char *fmt, int a, int b);
extern int func_02037af8(const char *src, unsigned int *out);
extern int NNS_FndMountArchive(char *dst, const char *fmt, unsigned int val);
extern void *NNS_FndGetArchiveFileByName(const char *name);
extern void *func_02107828(void *p);
extern void *NNS_G3dGetJntAnmSet(void);
extern void *func_02107b44(void *p, int a);
extern void *NNS_G3dGetMatCAnmSet(void);
extern void *func_02107b80(void *p, int a);
extern void *NNS_G3dGetTexSRTAnmSet(void);
extern void *func_02107bbc(void *p, int a);
extern void func_0210285c(void *buf);
extern int func_021077e8(void);
extern int func_02064b2c(void *buf, void *ptr, unsigned int mask, int param);
extern int func_02056064(int a, int b);
extern int func_020561cc(int a, unsigned int b);
extern void func_020e9898(void *p);

typedef struct UnkStruct_02037608 {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
    unsigned int unk_0C;
    unsigned int unk_10;
    unsigned int unk_14;
    unsigned int unk_18;
    unsigned int unk_1C;
    unsigned int unk_20;
    unsigned int unk_24;
    unsigned int unk_28;
    int unk_2C;
} UnkStruct_02037608;

extern unsigned char data_020da37c[];
extern unsigned char data_020da390[];
extern unsigned char data_020da394[];
extern unsigned char data_020da3a4[];
extern unsigned char data_020da3b4[];
extern unsigned char data_020da3c4[];
extern unsigned char data_020da3d4[];
extern unsigned char data_020da3e4[];
extern unsigned char data_020da3f4[];
extern unsigned char data_020da404[];
extern unsigned char data_021fbe94[];

UnkStruct_02037608 *func_02037608(UnkStruct_02037608 *arr, int key)
{
    unsigned int global;
    unsigned int i;
    int shift;
    int temp;
    char buf1[0x20];
    char buf2[0x68];

    global = data_021c9b24;
    for (i = 0; i < 0x1f; arr++, i++) {
        if (arr->unk_04 == 0) {
            shift = key >> 4;
            func_02064328(buf1, (const char *) data_020da37c, shift, key);
            arr->unk_04 = func_02037af8(buf1, &arr->unk_24);
            if (NNS_FndMountArchive(buf2, (const char *) data_020da390, arr->unk_04) != 0) {
                void *p, *q;
                unsigned short off;
                unsigned int val;

                p = NNS_FndGetArchiveFileByName((const char *) data_020da394);
                q = func_02107828(p);
                off = *(unsigned short *) ((char *) q + 0xe);
                val = *(unsigned int *) ((char *) ((char *) q + off) + 0xc);
                arr->unk_08 = (unsigned int) q + val;

                arr->unk_0C = (unsigned int) NNS_FndGetArchiveFileByName((const char *) data_020da3a4);
                arr->unk_10 = (unsigned int) NNS_FndGetArchiveFileByName((const char *) data_020da3b4);

                if (NNS_FndGetArchiveFileByName((const char *) data_020da3c4) != 0) {
                    void *r = NNS_G3dGetJntAnmSet();
                    arr->unk_14 = (unsigned int) func_02107b44(r, 0);
                }
                if (NNS_FndGetArchiveFileByName((const char *) data_020da3d4) != 0) {
                    void *r = NNS_G3dGetMatCAnmSet();
                    arr->unk_18 = (unsigned int) func_02107b80(r, 0);
                }
                if (NNS_FndGetArchiveFileByName((const char *) data_020da3e4) != 0) {
                    void *r = NNS_G3dGetTexSRTAnmSet();
                    arr->unk_1C = (unsigned int) func_02107bbc(r, 0);
                }
                {
                    void *r = NNS_FndGetArchiveFileByName((const char *) data_020da3f4);
                    if (r != 0) {
                        arr->unk_28 = (unsigned int) r + 2;
                        arr->unk_2C = *(short *) r;
                    }
                }
                func_0210285c(buf2);
            }
            if (((key & 0xF000) >> 12) == 1) {
                func_02064328(buf1, (const char *) data_020da404, shift, key);
                shift = func_02064b2c(buf1, *(void **) data_021fbe94, ~3, 0);
                if (shift != 0) {
                    temp = func_021077e8();
                    func_02056064(temp, 0);
                    arr->unk_20 = func_020561cc(temp, global);
                    if (shift != 0) {
                        func_020e9898((void *) shift);
                    }
                }
            }
            arr->unk_00 = (unsigned int) key;
            return arr;
        } else {
            if (arr->unk_00 == (unsigned int) key) {
                return arr;
            }
        }
    }
    return 0;
}
