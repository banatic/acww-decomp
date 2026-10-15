/* func_0203e478 @ 0x0203e478, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[8];
    unsigned char unk_08;
    unsigned char pad_09[3];
    unsigned int unk_0C;
    unsigned int unk_10;
    unsigned char unk_14;
    unsigned char unk_15;
    unsigned char unk_16;
    unsigned char unk_17;
    unsigned char unk_18;
    unsigned char unk_19;
} UnkStruct_0203e478;

typedef struct {
    unsigned char c;
} Param5;

extern void *func_0203f504(void);
extern int func_02065c2c(void *, void *);

extern unsigned char data_021c72c4[];

int func_0203e478(int a0, int a1, int a2, int a3, Param5 a4)
{
    UnkStruct_0203e478 *p;

    p = func_0203f504();
    if (p == 0) {
        return 0;
    }
    p->unk_0C = a0;
    p->unk_10 = a1;
    p->unk_15 = (unsigned char) a2;
    p->unk_08 = (unsigned char) a3;
    p->unk_16 = a4.c;
    p->unk_17 = 0;
    p->unk_18 = 0;
    p->unk_19 = 0;
    p->unk_14 = 1;
    func_02065c2c((void *) data_021c72c4, p);
    return 1;
}
