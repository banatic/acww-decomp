/* sky_events_4: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020be000 @ 0x020be000, 0xa0 bytes, Thumb
 * func_020bdfd8 @ 0x020bdfd8, 0x28 bytes, Thumb
 */

struct UnkStruct_020be000 {
    unsigned char pad[0x2f26];
    unsigned char flagD;
    unsigned char flagE;
    unsigned char flagF;
};

struct Entry {
    unsigned short id;
    unsigned char pad[10];
};

extern void func_0209e474(unsigned int *);
extern void MI_CpuCopy8(unsigned int *, void *, int);
extern int func_0203fec4(struct Entry *, void *, int);
extern int func_0203fc78(int, void *, int);
extern void func_0209f100(void *param1, int param2);
extern void func_020bde98(void *param1);
extern unsigned char data_021dc7a8[];

void func_020be000(struct UnkStruct_020be000 *self)
{
    unsigned int state[2];
    unsigned char buf[8];
    unsigned char tmp[8];
    struct Entry entries[7];
    struct Entry *p, *end;
    unsigned int hit;
    unsigned short id;

    self->flagD = 0;
    self->flagE = 0;
    self->flagF = 0;

    state[0] = 0;
    state[1] = 0;

    func_0209e474(state);
    MI_CpuCopy8(state, buf, 8);
    end = entries + func_0203fec4(entries, buf, 0);

    p = entries;
    while (p < end) {
        id = p->id;
        MI_CpuCopy8(state, tmp, 8);
        hit = (func_0203fc78(id, tmp, 0) != 0) ? 1 : 0;
        if (hit != 0) {
            if (id == 0x44) {
                self->flagD = 1;
            } else if (id == 0x45) {
                self->flagE = 1;
            } else if (id == 0x13 || id == 0xf) {
                self->flagF = 1;
            }
        }
        p++;
    }
}

void func_020bdfd8(void *param1, int param2)
{
    void *r4 = param1;
    if (param2 != 0) {
        func_0209f100((void *) data_021dc7a8, 9);
        func_020be000((struct UnkStruct_020be000 *) r4);
        func_020bde98(r4);
    }
}
