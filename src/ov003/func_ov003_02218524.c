/* func_ov003_02218524 @ 0x02218524, 0x8c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02218664(void *a, void *b, void *c, void *d, void *e);
extern int func_02096614(unsigned char *a, int *b, int *c, int d, int e);
extern int func_ov003_022186cc(void *obj, unsigned char b, unsigned int v18, unsigned int v20, int shortval, int six,
                               int arg1);

typedef struct {
    char pad_00[0x5c];
    unsigned int unk_5C;
    unsigned int unk_60;
    unsigned int unk_64;
    char pad_68[0x8e - 0x68];
    unsigned short unk_8E;
    char pad_90[0x7f0 - 0x90];
    unsigned int unk_7F0;
    char pad_7F4[0x800 - 0x7f4];
    unsigned int unk_800;
    char pad_804[0x8f0 - 0x804];
    char unk_8F0;
    char pad_8F1[0xc84 - (0x8f0 + 1)];
    unsigned short unk_C84;
} BigStruct;

typedef struct {
    unsigned char unk_00;
    unsigned char unk_01;
    short unk_02;
} LocalBuf;

void func_ov003_02218524(BigStruct *obj, int arg1)
{
    LocalBuf buf;
    int val;
    int val2;
    int val3;
    volatile int local_c;
    int val4;

    if ((obj->unk_7F0 - 0x38) <= 2) {
        obj->unk_C84 = (unsigned short) arg1;
        return;
    }

    func_ov003_02218664(&obj->unk_8F0, &buf, &val3, &val4, &buf.unk_02);

    local_c = obj->unk_60;

    if (func_02096614(&buf.unk_01, &val, &val2, -1, obj->unk_800) != 0) {
        obj->unk_5C = val;
        obj->unk_64 = val2;
    }

    obj->unk_8E = (unsigned short) buf.unk_02;
    func_ov003_022186cc(obj, buf.unk_00, val3, val4, buf.unk_02, 6, arg1);
}
