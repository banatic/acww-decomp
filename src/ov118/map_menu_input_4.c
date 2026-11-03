/* map_menu_input_4: 4 functions, module ov118
 * mwccarm 1.2/base -O4,s
 * func_ov118_0229aca0 @ 0x0229aca0, 0x84 bytes, Thumb
 * func_ov118_0229ac44 @ 0x0229ac44, 0x5c bytes, Thumb
 * func_ov118_0229abe0 @ 0x0229abe0, 0x64 bytes, Thumb
 * func_ov118_0229ab64 @ 0x0229ab64, 0x7c bytes, Thumb
 */

typedef struct Ov118Struct {
    unsigned char pad_00[0xA6];
    unsigned char unk_A6;
    unsigned char pad_A7[0x5D1];
    unsigned char unk_678;
} Ov118Struct;

typedef struct {
    char pad_00[0x9A];
    unsigned short unk_9A;
} UnkStruct_0229abe0;

extern int func_ov118_0229a460(void *p, int);
extern int func_ov002_0220a58c(void *p, unsigned char a, unsigned char b);
extern unsigned char *func_ov002_02208098(void *p, unsigned char value);
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;
extern void func_ov002_0220a4c8(void *receiver);
extern int func_ov118_0229b374(void *);
extern void func_ov118_0229adf0(void *, int);
extern unsigned short data_021fbe40;
extern void func_ov118_0229afd4(void *, int);
extern void func_ov118_0229b454(void *);
extern void func_ov118_0229b43c(void *);

int func_ov118_0229aca0(void *p)
{
    unsigned char v1, v2;
    if (!func_ov118_0229a460(p, 8)) {
        return 0;
    }
    v1 = data_021f6c58;
    v2 = data_021f6c54;
    if (func_ov002_0220a58c((unsigned char *) p + 0x678, v1, v2)) {
        *((unsigned char *) p + 0xa5) = v2;
        *((unsigned char *) p + 0xa7) = *((unsigned char *) p + 0xa4);
        *((unsigned char *) p + 0xa6) = *((unsigned char *) p + 0xa7);
        func_ov002_02208098(p, 1);
        return 1;
    } else {
        if ((int) v1 > 0xe8 && (int) v1 < 0xf5 && (int) v2 > 0x56 && (int) v2 < 0xae) {
            func_ov002_02208098(p, 2);
            return 1;
        }
        return 0;
    }
}

void func_ov118_0229ac44(Ov118Struct *self, int val)
{
    int t = val;
    int diff;
    int product;
    int quotient;

    if (t < 0) {
        t = 0;
    } else if (t > 0x58) {
        t = 0x58;
    }

    diff = t - self->unk_A6;

    if (diff >= 4 || diff <= -4) {
        func_ov002_0220a4c8(&self->unk_678);
        self->unk_A6 = (unsigned char) t;
    }

    product = t * func_ov118_0229b374(self);
    quotient = product / 0x58;
    func_ov118_0229adf0(self, quotient);
}

void func_ov118_0229abe0(void *self)
{
    int v;
    unsigned short flags;
    int limit;

    v = ((UnkStruct_0229abe0 *) self)->unk_9A;
    flags = data_021fbe40;

    if (flags & 0x40) {
        v -= 4;
    } else if (flags & 0x80) {
        v += 4;
    }

    limit = func_ov118_0229b374(self);

    if (v < 0) {
        v = 0;
    } else if (v > limit) {
        v = limit;
    }

    if (v != ((UnkStruct_0229abe0 *) self)->unk_9A) {
        func_ov002_0220a4c8((char *) self + 0x678);
    }

    func_ov118_0229adf0(self, v);
}

int func_ov118_0229ab64(unsigned char *a)
{
    unsigned char b0 = data_021f6c58;
    unsigned char b1 = data_021f6c54;
    if ((int) b1 < 0x33 || (int) b1 > 0x4b) {
        return 0;
    }
    if (func_ov118_0229a460(a, 1)) {
        if ((int) b0 < 0xcd || (int) b0 > 0xe5) {
            return 0;
        }
        func_ov118_0229afd4(a, 0);
        func_ov118_0229b454(a);
    } else {
        if ((int) b0 < 0xaa || (int) b0 > 0xc2) {
            return 0;
        }
        func_ov118_0229afd4(a, 0);
        func_ov118_0229b43c(a);
    }
    func_ov118_0229adf0(a, 0);
    a[0xa3] = 0xff;
    return 1;
}
