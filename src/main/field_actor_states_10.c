/* field_actor_states_10: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0200a528 @ 0x0200a528, 0x90 bytes, Thumb
 * func_0200a4b8 @ 0x0200a4b8, 0x70 bytes, Thumb
 * func_0200a4ac @ 0x0200a4ac, 0xc bytes, Thumb
 */

typedef struct {
    char pad_00[0x2d8];
    unsigned int unk_2D8;
    char pad_2DC[0x428];
    int unk_704;
    char pad_708[0x128];
    int unk_830;
    int unk_834;
    int unk_838;
} UnkStruct_0200a528;

struct UnkStruct_0200a4b8_2 {
    unsigned char a;
    unsigned char b;
    unsigned char c;
    unsigned char d;
};

struct UnkStruct_0200a4b8 {
    char pad_00[0x7d4];
    struct UnkStruct_0200a4b8_2 sub;
    char pad_7D8[0x28];
    unsigned int flags;
};

typedef struct {
    int unk_00;
    unsigned char unk_04;
    int unk_08;
    int unk_0C;
} Struct0200A4AC;

extern void func_0200f268(UnkStruct_0200a528 *s, int n);
extern void func_0200f650(UnkStruct_0200a528 *s, int n);
extern unsigned int data_020ccf94;
extern void func_02010f5c(void *p);
extern void func_02010d64(void *p);
extern void func_0200ae7c(void *p, unsigned char *ptr, unsigned char byte);
extern int func_0200f530(void *p, unsigned int *arr);
extern void func_0200ae04(void *p);
extern int func_02073908(unsigned int a, unsigned int b);

void func_0200a528(UnkStruct_0200a528 *s)
{
    if (s->unk_704 == 0x18) {
        goto equal;
    }
    s->unk_830 = 0;
    s->unk_834 = 0;
    s->unk_838 = 0;
    func_0200f268(s, 13);
    goto end;
equal: {
    unsigned int t = (s->unk_2D8 << 4) >> 16;
    if (t < 6) {
        int r4 = 0x1000 - (int) (t << 12) / 6;
        if (r4 < 0) {
            r4 = 0;
            func_0200f268(s, 13);
        }
        s->unk_830 = r4;
        s->unk_834 = r4;
        s->unk_838 = r4;
        func_0200f650(s, r4);
    } else {
        s->unk_830 = 0;
        s->unk_834 = 0;
        s->unk_838 = 0;
    }
}
end:;
}

void func_0200a4b8(struct UnkStruct_0200a4b8 *p)
{
    struct UnkStruct_0200a4b8_2 *sub;
    unsigned int pos[2];
    unsigned char d;

    func_02010f5c(p);
    if (func_02073908(data_020ccf94, p->flags)) {
        func_02010d64(p);
        func_0200a528((UnkStruct_0200a528 *) p);
        sub = &p->sub;
        func_0200ae7c(p, &sub->b, sub->a);
    } else {
        sub = &p->sub;
        d = sub->d;
        pos[0] = sub->c;
        pos[1] = d;
        func_0200f530(p, pos);
        func_02010d64(p);
        func_0200a528((UnkStruct_0200a528 *) p);
        func_0200ae04(p);
    }
}

void func_0200a4ac(Struct0200A4AC *ptr, int a, unsigned char b, int c, int d)
{
    ptr->unk_00 = a;
    ptr->unk_04 = b;
    ptr->unk_08 = c;
    ptr->unk_0C = d;
}
