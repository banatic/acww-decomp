/* func_020a33e0 @ 0x020a33e0, 0x1d0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_020a33e0 UnkStruct_020a33e0;
struct UnkStruct_020a33e0 {
    char pad_00[0xa1];
    unsigned char unk_A1;
    char pad_A2[0xd2 - 0xa2];
    unsigned short unk_D2;
    char pad_D4[0xe6 - 0xd4];
    unsigned char unk_E6;
};

typedef struct UnkStruct_020a33e0_2 UnkStruct_020a33e0_2;
struct UnkStruct_020a33e0_2 {
    char pad_00[0x64];
    int unk_64;
};

extern UnkStruct_020a33e0_2 *data_020ccf94;
extern int func_02073fdc(int a);
extern void func_02074078(void);
extern int func_020a259c(UnkStruct_020a33e0 *p, int a);
extern unsigned short func_020740b4(void);
extern void func_020a02b4(UnkStruct_020a33e0 *p, unsigned char *q, int a);
extern int func_020a2438(UnkStruct_020a33e0 *p, int a);
extern void func_020a2480(UnkStruct_020a33e0 *p);
extern int func_020a03e0(UnkStruct_020a33e0 *p, unsigned char *q, int a, int b, int c, int d, int e, int f);
extern int func_020a6ed0(void);
extern int func_02073c90(UnkStruct_020a33e0_2 *g, int a);
extern int func_02075918(void);
extern int func_02073044(void);
extern int func_020ebf70(void);
extern void func_020a6c6c(int a);
extern void func_02073d74(UnkStruct_020a33e0_2 *g, int a);
extern void func_02073820(UnkStruct_020a33e0_2 *g);
extern void func_02073770(UnkStruct_020a33e0_2 *g, int a, int b);
extern void func_020ba37c(void);
extern int func_020a0848(UnkStruct_020a33e0 *p, unsigned char *q, int a, int b, int c, int d);
extern void func_020a25cc(void);
extern void func_020a4e94(UnkStruct_020a33e0 *p, int a);

void func_020a33e0(UnkStruct_020a33e0 *p)
{
    int ok;
    UnkStruct_020a33e0_2 *g;

    switch (p->unk_A1) {
        case 0:
            if (func_02073fdc(1) != 0) {
                func_02074078();
                break;
            }
            if (func_020a259c(p, 0) == 0) {
                break;
            }
            p->unk_D2 = func_020740b4();
            p->unk_A1 = 1;
            break;
        case 1:
        case 2:
            if (func_02073fdc(1) != 0) {
                func_02074078();
                break;
            }
            func_020a02b4(p, &p->unk_A1, 1);
            break;
        case 3:
            if (func_02073fdc(1) != 0) {
                func_02074078();
                break;
            }
            if (func_020a2438(p, data_020ccf94->unk_64) == 0) {
                break;
            }
            func_020a2480(p);
            p->unk_A1 = 4;
            break;
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
            func_020a03e0(p, &p->unk_A1, 4, 0xf, 0x15, 1, 1, 1);
            break;
        case 12:
            if (func_02073fdc(1) != 0) {
                func_02074078();
                break;
            }
            ok = 1;
            if (func_02073c90(data_020ccf94, func_020a6ed0()) != 0) {
                ok = 0;
            }
            if (ok == 0) {
                break;
            }
            if (func_02075918() == 0) {
                break;
            }
            p->unk_A1 = 0xd;
            break;
        case 13:
            if (func_02073fdc(1) != 0) {
                func_02074078();
                break;
            }
            if ((func_02073044(), func_020ebf70()) == 0) {
                break;
            }
            if (p->unk_D2 == func_020740b4()) {
                break;
            }
            func_020a6c6c(func_020a6ed0());
            g = data_020ccf94;
            func_02073d74(g, 2);
            func_02073820(g);
            func_02073770(g, 6, 0);
            p->unk_A1 = 0xe;
            break;
        case 14:
            if (func_02073fdc(1) != 0) {
                func_02074078();
                break;
            }
            if (p->unk_E6 == 0) {
                break;
            }
            func_020ba37c();
            p->unk_A1 = 0x1a;
            break;
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 21:
        case 22:
        case 23:
        case 24:
        case 25:
            func_020a0848(p, &p->unk_A1, 0xf, 0x15, 1, 1);
            break;
        default:
            asm { add r0, p, #0 }
            func_020a25cc();
            func_020a4e94(p, 0xa);
            break;
    }
}
