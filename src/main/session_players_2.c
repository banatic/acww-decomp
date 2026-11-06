/* session_players_2: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0209658c @ 0x0209658c, 0x88 bytes, Thumb
 * func_02096518 @ 0x02096518, 0x74 bytes, Thumb
 * func_0209649c @ 0x0209649c, 0x7c bytes, Thumb
 * func_02096484 @ 0x02096484, 0x16 bytes, Thumb
 */

struct GStruct_020ccf94 {
    char pad_00[0x68];
    int unk_68;
};

typedef struct {
    char pad_00[0x68];
    int unk_68;
} UnkStruct_02096518;

typedef struct {
    char pad_00[0x7f0];
    int unk_7F0;
} UnkStruct_02096518_2;

extern int func_02073908(void *ptr, int val);
extern void *func_02096718(int val);
extern int func_020966c4(int val);
extern int func_020966e0(int val);
extern int func_020778f8(int object);
extern struct GStruct_020ccf94 *data_020ccf94;
extern void MI_CpuCopy8(int, void *, int);
extern void *func_020b65c4(void);
extern void func_02077a54(void *, void *, int);
extern void func_020778e0(short *, short);
extern int func_0207762c(void *);
extern void func_020778b0(void);

int func_02096518(int *param0, int param1, int param2);

int func_0209658c(short *out, int p1, int p2)
{
    int forwarded_value;

    int r4 = p2;

    if (r4 == 4) {
        r4 = data_020ccf94->unk_68;
    }

    if (func_02073908(data_020ccf94, r4) != 0) {
        void *p = func_02096718(4);
        if (p != 0) {
            *out = (short) (*(short *) ((char *) p + 0x8e));
            return 1;
        } else {
            return 0;
        }
    } else {
        int local;
        if (func_020966c4(r4) == 0) {
            return 0;
        }
        if (func_02096518(&local, p1, r4) == 0) {
            return 0;
        }
        if (local >= 0x93) {
            return 0;
        }
        if ((forwarded_value = (int) func_020966e0(r4)) == 0) {
            return 0;
        }
        *out = (short) func_020778f8((int) forwarded_value);
        return 1;
    }
}

int func_02096518(int *param0, int param1, int param2)
{
    unsigned char local;
    if (param2 == 4) {
        param2 = (*(UnkStruct_02096518 **) &data_020ccf94)->unk_68;
    }
    if (func_02073908((*(UnkStruct_02096518 **) &data_020ccf94), param2) != 0) {
        void *ptr = func_02096718(4);
        if (ptr) {
            *param0 = ((UnkStruct_02096518_2 *) ptr)->unk_7F0;
            return 1;
        } else {
            return 0;
        }
    } else {
        int val = func_020966c4(param2);
        if (val == 0) {
            return 0;
        }
        MI_CpuCopy8(val + 1, &local, 1);
        if (local == 0) {
            return 0;
        }
        *param0 = local - 1;
        return 1;
    }
}

void func_0209649c(void *a, void *b)
{
    struct {
        int f0;
        struct {
            char c0;
            unsigned char c1;
            short s;
        } sub;
        char buf[8];
    } local;

    void *p = func_02096718(4);

    if (p) {
        void *q = func_020b65c4();
        func_02077a54(&local.sub, q, 0);

        if (func_02096518((int *) (&local), -1, 4)) {
            local.sub.c1 = (unsigned char) (local.f0 + 1);
        }

        func_020778e0(&local.sub.s, *(short *) ((char *) p + 0xc84));
        MI_CpuCopy8((int) ((char *) p + 0x8f0), local.buf, 8);
    } else {
        local.sub.c1 = 0x94u;
    }

    MI_CpuCopy8((int) (&local.sub), a, func_0207762c(b));
}

void func_02096484(unsigned char *r0, int r1, unsigned char r2)
{
    unsigned char *r5 = r0;
    unsigned char r4 = r2;

    func_020778b0();
    r5[2] = r4;
}
