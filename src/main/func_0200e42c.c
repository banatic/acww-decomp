/* func_0200e42c @ 0x0200e42c, 0x228 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0200e42c {
    int x;
    int y;
    int z;
} UnkStruct_0200e42c;
typedef struct UnkStruct_0200e42c_2 {
    int a;
    int b;
} UnkStruct_0200e42c_2;

typedef struct UnkStruct_0200e42c_3 {
    char pad_00[8];
    int unk_08;
    char pad_0C[80];
    UnkStruct_0200e42c unk_5C;
    char pad_68[52];
    unsigned int unk_9C;
    unsigned int unk_A0;
    char pad_A4[196];
    int unk_168;
    char unk_16C;
    char pad_16D[1075];
    char unk_5A0;
    char pad_5A1[39];
    char unk_5C8;
    char pad_5C9[291];
    int unk_6EC;
    char pad_6F0[4];
    int unk_6F4;
    int unk_6F8;
    int unk_6FC;
    char pad_700[13];
    char unk_70D;
    char unk_70E;
    char unk_70F;
    char pad_710[144];
    char unk_7A0;
    char pad_7A1[95];
    int unk_800;
    int unk_804;
    int unk_808;
    int unk_80C;
    int unk_810;
    int unk_814;
    int unk_818;
    int unk_81C;
    char pad_820[200];
    char unk_8E8;
    char unk_8E9;
    char pad_8EA[26];
    unsigned char unk_904;
} UnkStruct_0200e42c_3;

extern int func_02096188(int);
extern void func_0203efb0(UnkStruct_0200e42c_3 *, unsigned short);
extern void func_020962c8(int, UnkStruct_0200e42c_3 *);
extern int func_020961d0(int);
extern void func_0205f8cc(void *, int);
extern int func_020112d0(UnkStruct_0200e42c_3 *);
extern int func_02011150(UnkStruct_0200e42c_3 *, int);
extern void func_020106a8(UnkStruct_0200e42c_3 *, int, int);
extern void func_0200e704(UnkStruct_0200e42c_3 *);
extern void func_0205db4c(void *, int);
extern void func_0205d8c4(void *, int);
extern void func_0205dccc(void *, int);
extern int func_020110e8(UnkStruct_0200e42c_3 *);
extern void func_0205dc94(void *, int);
extern void func_0200e6a4(UnkStruct_0200e42c_3 *);
extern void func_0200e654(UnkStruct_0200e42c_3 *);
extern void func_020110c4(UnkStruct_0200e42c_2 *, UnkStruct_0200e42c_3 *);
extern int func_02011368(UnkStruct_0200e42c_3 *);
extern void func_0205ec50(void *, int, UnkStruct_0200e42c_3 *, UnkStruct_0200e42c_2 *, int, int);
extern void func_02060500(void *, int);
extern int func_02096180(int);
extern void func_0200dbb4(UnkStruct_0200e42c_3 *, int, int, int);
extern void func_02006554(UnkStruct_0200e42c_3 *);
extern void func_0200f27c(UnkStruct_0200e42c_3 *, int);
extern unsigned char data_020c75c4[];
extern unsigned char data_020c75d4[];
extern unsigned char data_020c75dc[];
extern unsigned char data_020c75cc[];
extern unsigned char data_020c75e0[];
extern unsigned char data_020e54a8;

int func_0200e42c(UnkStruct_0200e42c_3 *s)
{
    int h;
    int idx;
    int t;
    UnkStruct_0200e42c *v;
    UnkStruct_0200e42c_2 loc;

    h = s->unk_08;
    s->unk_800 = func_02096188(h);
    func_0203efb0(s, (unsigned short) s->unk_800);
    func_020962c8(s->unk_800, s);
    func_0205f8cc(&s->unk_7A0, data_020c75c4[func_020961d0(s->unk_800)]);
    idx = func_020112d0(s);
    func_020106a8(s, idx, func_02011150(s, 1));
    func_0200e704(s);
    func_0205db4c(&s->unk_70F, data_020c75d4[func_020961d0(s->unk_800)]);
    func_0205d8c4(&s->unk_70E, data_020c75dc[func_020961d0(s->unk_800)]);
    func_0205dccc(&s->unk_70D, data_020c75cc[func_020961d0(s->unk_800)]);
    func_0205dc94(&s->unk_70D, func_020110e8(s));
    func_0200e6a4(s);
    func_0200e654(s);
    idx = func_020961d0(s->unk_800);
    func_020110c4(&loc, s);
    func_0205ec50(&s->unk_5A0, data_020c75e0[idx], s, &loc, func_02011368(s), 0);
    func_02060500(&s->unk_5C8, s->unk_800);
    s->unk_9C = 0xffffb000;
    s->unk_A0 = 0xffff6000;
    func_0200dbb4(s, func_02096180(h), 9, -1);
    s->unk_904 &= ~0x80;
    func_02006554(s);
    s->unk_6EC = 0;
    func_0200f27c(s, 1);
    t = data_020e54a8 ? 0 : 1;
    if (t != 0) {
        func_0200f27c(s, 0);
    }
    v = &s->unk_5C;
    s->unk_6F4 = v->x;
    s->unk_6F8 = v->y;
    s->unk_6FC = v->z;
    s->unk_80C = -1;
    s->unk_810 = -1;
    s->unk_804 = -1;
    s->unk_808 = 0;
    s->unk_814 = 0;
    s->unk_818 = 0;
    s->unk_81C = 0xf;
    s->unk_8E9 = 0x1f;
    s->unk_8E8 = 0;
    s->unk_168 = 0;
    s->unk_16C = 0;
    return 1;
}
