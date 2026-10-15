/* func_02035e90 @ 0x02035e90, 0x9c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02035684(int, int, int);
extern void func_02035624(int);
extern int func_02036714(void);
extern int func_02035e54(void);
extern void func_02036784(int, int);
extern int func_02035e68(void);
extern void func_02036894(int, int);
extern int func_02035e7c(void);
extern void func_02035930(void);

typedef struct UnkStruct_02035e90 {
    unsigned char pad_00[8];
    unsigned char unk_08;
    unsigned char unk_09;
    unsigned char unk_0A;
    unsigned char unk_0B;
    int unk_0C;
    int unk_10;
} UnkStruct_02035e90;

typedef struct EarlyStruct {
    unsigned char pad_00[12];
    unsigned short unk_0C;
} EarlyStruct;

extern EarlyStruct *data_021f42f4;

void func_02035e90(UnkStruct_02035e90 *r4)
{
    unsigned char stage;

    if (data_021f42f4->unk_0C == 5) {
        return;
    }

    stage = r4->unk_0B;
    if (stage == 1) {
        func_02035684(8, 15, 0);
        r4->unk_0B = 2;
    } else if (stage == 3) {
        func_02035624(8);
        r4->unk_0B = 0;
    }

    r4->unk_09 = func_02036714();
    func_02036784(func_02035e54(), r4->unk_09);

    if (r4->unk_08 == 0 && r4->unk_09 == 0 && r4->unk_0A == 0) {
        if (r4->unk_0C != 0 || r4->unk_10 != 0) {
            func_02035624(7);
        }
        r4->unk_0C = -1;
        r4->unk_10 = 0;
        func_02035684(7, 15, 0);
    } else {
        func_02036894(func_02035e68(), 1);
        if (r4->unk_09 != 0) {
            func_02035e7c();
            func_02035930();
        }
    }
}
