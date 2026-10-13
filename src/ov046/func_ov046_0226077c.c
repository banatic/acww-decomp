/* func_ov046_0226077c @ 0x0226077c, 0x74 bytes, Thumb, module ov046
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x40];
    int unk_40;
    unsigned char pad_44[0x7c];
    int unk_C0;
    unsigned char unk_C4;
    unsigned char unk_C5;
    unsigned char pad_C6[0x16];
    int unk_DC;
} UnkStruct_0226077c;

extern void func_020b1954(void *);
extern void func_020b1394(void *, int);
extern void func_02068404(int, int, void *);
extern void func_020b14c0(int);
extern void func_020b193c(void *);
extern int func_020b1558(void);
extern int func_ov046_022610fc(UnkStruct_0226077c *);

void func_ov046_0226077c(UnkStruct_0226077c *obj, int flag)
{
    unsigned char buf[32];

    obj->unk_C4 = 0;
    if (flag == 0) {
        if (obj->unk_C0 >= 0) {
            func_020b1954(buf);
            func_020b1394(buf, obj->unk_C0);
            func_02068404(obj->unk_40, 6, buf);
            func_020b14c0(obj->unk_C0);
            func_020b193c(buf);
        }
        obj->unk_C5 = 16 - func_020b1558();
        obj->unk_C4 = 0;
        obj->unk_DC = 27;
    } else {
        obj->unk_DC = func_ov046_022610fc(obj);
    }
}
