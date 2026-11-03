/* mes_choice_window: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020ac1dc @ 0x020ac1dc, 0xc bytes, Thumb
 * func_020ac1d0 @ 0x020ac1d0, 0xc bytes, Thumb
 * func_020ac1cc @ 0x020ac1cc, 0x4 bytes, Thumb
 * func_020ac1c4 @ 0x020ac1c4, 0x6 bytes, Thumb
 * func_020ac198 @ 0x020ac198, 0x2c bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[112];
    unsigned long unk_70;
} UnkStruct_020ac1c4;

typedef unsigned short uint16_t;

struct UnkStruct_020ac198 {
    unsigned char pad_00[0x70];
    int unk_70;
};

extern void func_0208e508(void *ptr, int arg);
extern uint16_t data_020d1de8[];
extern void func_020ac358(struct UnkStruct_020ac198 *, int, uint16_t);

void func_020ac1dc(void *ptr)
{
    func_0208e508((char *) ptr + 0x20, 0);
}

void func_020ac1d0(void *ptr)
{
    func_0208e508((char *) ptr + 0x20, 8);
}

void func_020ac1cc(int *p0, int p1)
{
    p0[27] = p1;
}

void func_020ac1c4(UnkStruct_020ac1c4 *p)
{
    p->unk_70 = 0;
}

int func_020ac198(struct UnkStruct_020ac198 *s, int arg1)
{
    uint16_t v;
    int result;

    v = data_020d1de8[s->unk_70];
    s->unk_70 = s->unk_70 + 1;
    if (s->unk_70 >= 5) {
        result = 1;
    } else {
        result = 0;
    }
    func_020ac358(s, arg1, v);
    return result;
}
