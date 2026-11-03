/* villager_talk_steps_6: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020240c8 @ 0x020240c8, 0x2c bytes, Thumb
 * func_020240a8 @ 0x020240a8, 0x20 bytes, Thumb
 * func_02024078 @ 0x02024078, 0x30 bytes, Thumb
 */

typedef struct UnkStruct_020240c8 {
    unsigned char pad_00[0x830];
    int unk_830;
} UnkStruct_020240c8;

typedef struct UnkStruct_020240c8_2 {
    unsigned char pad_00[0x100];
    UnkStruct_020240c8 *unk_100;
    unsigned char pad_104[0x60];
    int unk_164;
} UnkStruct_020240c8_2;

typedef struct {
    int a;
    int b;
} Pair;

extern void func_0209b920(int);
extern void func_02078630(int);
extern void func_020157d4(void *, int (*)(unsigned short *, int), unsigned char, unsigned char);
extern int func_02015828(void *, int);
extern void func_0202dbf0(void *, Pair);
extern Pair data_020d9118;

void func_020240c8(UnkStruct_020240c8_2 *arg)
{
    func_0209b920(arg->unk_164);
    func_02078630(arg->unk_100->unk_830);
}

int func_020240a8(unsigned short *p, int status)
{
    int ret;
    (void) status;
    ret = 0;
    if (*p >= 0x1561u && *p <= 0x1564u) {
        ret = 1;
    }
    return ret;
}

void func_02024078(void *p, void *output)
{
    func_020157d4(p, func_020240a8, 13, 0);
    func_02015828(p, 0);
    func_0202dbf0(p, data_020d9118);
}
