/* scene_command_6: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020151c0 @ 0x020151c0, 0x18 bytes, Thumb
 * func_0201516c @ 0x0201516c, 0x54 bytes, Thumb
 * func_0201511c @ 0x0201511c, 0x50 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x40];
    unsigned int unk_40;
    unsigned char pad_44[8];
    unsigned int unk_4C;
    unsigned char pad_50[0x5c];
    unsigned char unk_AC;
} UnkStruct_0201516c;

typedef struct {
    char pad_00[0x40];
    void *unk_40;
    char pad_44[0x8];
    char *unk_4C;
    char pad_50[0x5c];
    unsigned char unk_AC;
} UnkStruct_0201511c;

extern int func_0201596c(int arg0, int arg1);
extern int func_02019d0c(unsigned int, int, int, int, int, int, int, int, int, unsigned short, int);
extern void func_02068440(unsigned int);
extern unsigned short data_020c80f8;
extern int func_02019e00(char *p);
extern int func_02019de8(char *p);
extern void func_02068434(void *p);
extern void func_02016004(void *p);

int func_020151c0(int arg)
{
    int ret = 0;
    if (func_0201596c(arg, 5) != 0) {
        ret = 1;
    }
    return ret;
}

int func_0201516c(UnkStruct_0201516c *p)
{
    if (p->unk_4C != 0 && p->unk_40 != 0) {
        if (func_02019d0c(p->unk_4C + 0x564, 0xf, 4, 0, 0, 0, 0, 0, 0, data_020c80f8, 0)) {
            func_02068440(p->unk_40);
            p->unk_AC = 1;
        }
    }
    return 0;
}

int func_0201511c(UnkStruct_0201511c *s)
{
    int r = 0;
    if (s->unk_4C != 0 && s->unk_40 != 0) {
        if (func_02019e00(s->unk_4C + 0x564) == 0xf) {
            if (func_02019de8(s->unk_4C + 0x564) != 0) {
                func_02068434(s->unk_40);
                func_02016004(s);
                s->unk_AC = 2;
                r = 1;
            }
        }
    }
    return r;
}
