/* func_02024b4c @ 0x02024b4c, 0xac bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02024b4c_4 {
    const void *text;
    unsigned char unk_04;
    unsigned char unk_05;
    unsigned char unk_06;
    unsigned char unk_07;
} UnkStruct_02024b4c_4;

typedef struct UnkStruct_02024b4c {
    unsigned char pad_00[0x830];
    void *unk_830;
} UnkStruct_02024b4c;

typedef struct UnkStruct_02024b4c_2 {
    unsigned char pad_00[8];
    int unk_08;
} UnkStruct_02024b4c_2;

typedef struct UnkStruct_02024b4c_3 {
    unsigned char pad_00[0x40];
    UnkStruct_02024b4c_2 *unk_40;
    unsigned char pad_44[0xbc];
    UnkStruct_02024b4c *unk_100;
    unsigned char unk_104[0x1e];
    unsigned char unk_122;
} UnkStruct_02024b4c_3;

typedef struct UnkStruct_02024b4c_5 {
    unsigned char *ptr;
    unsigned char unk_04;
} UnkStruct_02024b4c_5;

extern const UnkStruct_02024b4c_4 data_020d8fb8;
extern const int data_020d9a9c, data_020d9aa8, data_020d9ab4;

extern void func_0202d9c4(UnkStruct_02024b4c_3 *p);
extern int func_0209bc40(void);
extern void func_0208150c(void *a);
extern void *func_020036e8(void);
extern void func_0202da38(UnkStruct_02024b4c_3 *p, unsigned char *buf, unsigned char *flag, int size, void *a,
                          const void *text, int b, int c, int d);

void func_02024b4c(UnkStruct_02024b4c_3 *p, UnkStruct_02024b4c_5 *out)
{
    UnkStruct_02024b4c_4 info;

    info = data_020d8fb8;
    func_0202d9c4(p);
    switch (func_0209bc40()) {
        case 2:
            info.text = &data_020d9a9c;
            break;
        case 3:
            info.text = &data_020d9aa8;
            break;
        default:
            info.text = &data_020d9ab4;
            break;
    }
    if (p->unk_40 != 0) {
        p->unk_40->unk_08 = 1;
    }
    if (info.text != 0) {
        func_0208150c(p->unk_100->unk_830);
        func_0202da38(p, p->unk_104, &p->unk_122, 0x1e, func_020036e8(), info.text, info.unk_04, 0, 0);
    }
    out->ptr = p->unk_104;
    out->unk_04 = p->unk_122;
}
