/* map_menu_list_4: 5 functions, module ov118
 * mwccarm 1.2/base -O4,s
 * func_ov118_0229b088 @ 0x0229b088, 0x60 bytes, Thumb
 * func_ov118_0229afd4 @ 0x0229afd4, 0xb4 bytes, Thumb
 * func_ov118_0229af64 @ 0x0229af64, 0x70 bytes, Thumb
 * func_ov118_0229aef8 @ 0x0229aef8, 0x6c bytes, Thumb
 * func_ov118_0229ae90 @ 0x0229ae90, 0x68 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0xa9];
    unsigned char b_a8;
    unsigned char b_a9;
} UnkStruct_0229afd4;

typedef struct UnkStruct_0229aef8 {
    unsigned char pad_00[0xa1];
    unsigned char count;
    unsigned char pad_A2[0x478a - 0xa2];
    unsigned char table[0x100];
} UnkStruct_0229aef8;

extern void func_ov118_0229aa98(UnkStruct_0229afd4 *self);
extern void func_ov118_0229aab4(UnkStruct_0229afd4 *self);
extern void func_ov118_0229a440(UnkStruct_0229afd4 *self, unsigned int val);
extern int func_ov118_0229a460(UnkStruct_0229afd4 *self, unsigned int val);
extern void func_ov118_0229b454(UnkStruct_0229afd4 *self);
extern void func_ov118_0229ae64(UnkStruct_0229afd4 *self);
extern void func_ov118_0229b43c(UnkStruct_0229afd4 *self);
extern void func_ov118_0229a450(UnkStruct_0229afd4 *self, unsigned int val);
extern void func_ov118_0229ae0c(UnkStruct_0229afd4 *self);
extern void func_0206fdd4(char *dst, int a, int b, int c, int d, int e);
extern unsigned char data_ov118_0229ca98[];
extern const unsigned char *func_ov118_0229b3b0(int);
extern const unsigned char data_ov118_0229ca90[];

void func_ov118_0229af64(void *p, int n);
unsigned char func_ov118_0229aef8(UnkStruct_0229aef8 *p, unsigned int key);
unsigned char func_ov118_0229ae90(int a, unsigned int b);

int func_ov118_0229b088(char *p, int arg1, int arg2)
{
    int i;

    for (i = 0; i < 14; i++) {
        unsigned char *e = (unsigned char *) (p + i * 3);
        if (e[0x47af] == 0xc) {
            continue;
        }
        if (e[0x47ad] - 8 >= arg1) {
            continue;
        }
        if (e[0x47ad] + 8 <= arg1) {
            continue;
        }
        if (e[0x47ae] - 8 >= arg2) {
            continue;
        }
        if (e[0x47ae] + 8 <= arg2) {
            continue;
        }
        return (unsigned char) i;
    }
    return 14;
}

void func_ov118_0229afd4(UnkStruct_0229afd4 *self, unsigned int idx)
{
    if (idx == 0) {
        self->b_a8 = 0xe;
        self->b_a9 = 0xe;
        func_ov118_0229aa98(self);
        return;
    }
    func_ov118_0229aab4(self);
    self->b_a9 = func_ov118_0229aef8((UnkStruct_0229aef8 *) self, idx);
    self->b_a8 = func_ov118_0229ae90((int) self, idx);
    if (idx >= 1 && idx < 0xf) {
        func_ov118_0229a440(self, 0x200);
        if (func_ov118_0229a460(self, 1)) {
            if (idx >= 1 && idx <= 9) {
                func_ov118_0229b454(self);
                func_ov118_0229ae64(self);
                return;
            }
        } else {
            if (idx < 1 || idx > 9) {
                func_ov118_0229b43c(self);
                func_ov118_0229ae64(self);
                return;
            }
        }
    } else {
        func_ov118_0229a450(self, 0x200);
    }
    func_ov118_0229ae0c(self);
    func_ov118_0229af64((void *) self, (unsigned char) 0xe);
    func_ov118_0229af64((void *) self, (unsigned char) self->b_a9);
}

void func_ov118_0229af64(void *p, int n)
{
    func_ov118_0229a450((UnkStruct_0229afd4 *) p, 0x80);
    if (n == 14) {
        func_0206fdd4((char *) p + 0x1724, 0x13, 0, 0x1c, 25, 4);
    } else if (n == 13) {
        func_0206fdd4((char *) p + 0x1724, 0x13, 0, 0x1c, ((unsigned char *) p)[0xb0] * 2 - 1, 3);
    } else {
        func_0206fdd4((char *) p + 0x1724, 0x13, n * 2, 0x1c, n * 2 + 1, 3);
    }
}

unsigned char func_ov118_0229aef8(UnkStruct_0229aef8 *p, unsigned int key)
{
    if (key == 9) {
        return 13;
    }
    if (key >= 1 && key < 9) {
        unsigned int target = key + 5;
        int i = 0;
        int n = p->count;
        while (i < n) {
            if (p->table[i] == target) {
                return (unsigned char) i;
            }
            i++;
        }
        return 14;
    }
    if (key < 15 && key >= 10) {
        return data_ov118_0229ca98[key - 10];
    }
    if (key < 28 && key >= 15) {
        return (unsigned char) (key - 15);
    }
    return 14;
}

unsigned char func_ov118_0229ae90(int a, unsigned int b)
{
    unsigned char r1;
    const unsigned char *p;
    if (b >= 1 && b < 15) {
        return (unsigned char) (b - 1);
    }
    if (b >= 15 && b < 28) {
        p = func_ov118_0229b3b0(a);
        r1 = p[b - 15];
        if (r1 == 0) {
            return 14;
        }
        if (r1 == 1 || (r1 >= 2 && r1 < 6)) {
            return 8;
        }
        if (r1 >= 6 && r1 < 14) {
            return (unsigned char) (r1 - 6);
        }
        if (r1 >= 14 && r1 < 19) {
            return data_ov118_0229ca90[r1 - 14];
        }
    }
    return 14;
}
