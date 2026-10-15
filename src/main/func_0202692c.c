/* func_0202692c @ 0x0202692c, 0x9c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202d9c4(void *);
extern int func_0209bc40(int);
extern int func_0208150c(int);
extern int func_020036e8(int);
extern int func_0202da38(int, int, int, int, int, int, int, int, int);
extern void func_0209b56c(int);

typedef struct {
    int unk_00;
    unsigned char unk_04;
} UnkStruct_0202692c_3;

extern UnkStruct_0202692c_3 data_020c8d88;
extern UnkStruct_0202692c_3 data_020c8d78;

typedef struct {
    char pad_00[0x100];
    void *unk_100;         // offset 0x100
    char buffer104[30];    // offset 0x104..0x121
    unsigned char unk_122; // offset 0x122
    char pad_123[0x15a - 0x123];
    unsigned short unk_15A; // offset 0x15a
    char pad_15C[4];
    int int160; // offset 0x160
} UnkStruct_0202692c;

typedef struct {
    char *unk_00;
    unsigned char unk_04;
} UnkStruct_0202692c_2;

void func_0202692c(UnkStruct_0202692c *param1, UnkStruct_0202692c_2 *out)
{
    int y;
    UnkStruct_0202692c_3 *data;
    int a;

    y = func_0209bc40(func_0202d9c4(param1));

    switch (y) {
        case 0xa:
            data = &data_020c8d88;
            break;
        case 0x13:
            data = &data_020c8d78;
            break;
        default:
            data = &data_020c8d88;
            break;
    }

    a = func_020036e8(func_0208150c(*(int *) ((char *) (param1->unk_100) + 0x830)));

    func_0202da38((int) param1, (int) (param1->buffer104), (int) (&param1->unk_122), 30, a, data->unk_00, data->unk_04, 0, 0);

    out->unk_00 = (char *) (param1->buffer104);
    out->unk_04 = param1->unk_122;

    if (param1->int160 != 0) {
        func_0209b56c(param1->int160);
    }

    param1->unk_15A = 0x5f;
}
