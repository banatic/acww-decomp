/* star_designer_pieces_2: 11 functions, module ov129
 * mwccarm 1.2/base -O4,s
 * func_ov129_0229be58 @ 0x0229be58, 0x24 bytes, Thumb
 * func_ov129_0229be04 @ 0x0229be04, 0x52 bytes, Thumb
 * func_ov129_0229bd4c @ 0x0229bd4c, 0xb8 bytes, Thumb
 * func_ov129_0229bd1c @ 0x0229bd1c, 0x30 bytes, Thumb
 * func_ov129_0229bcf0 @ 0x0229bcf0, 0x2c bytes, Thumb
 * func_ov129_0229bca4 @ 0x0229bca4, 0x4c bytes, Thumb
 * func_ov129_0229bc34 @ 0x0229bc34, 0x70 bytes, Thumb
 * func_ov129_0229bbd8 @ 0x0229bbd8, 0x5c bytes, Thumb
 * func_ov129_0229ba2c @ 0x0229ba2c, 0x1ac bytes, Thumb
 * func_ov129_0229b9d8 @ 0x0229b9d8, 0x52 bytes, Thumb
 * func_ov129_0229b9a0 @ 0x0229b9a0, 0x38 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned char pad_00[0xaa];
    unsigned short hword;
    unsigned char pad_AC[4];
    unsigned char byte;
} UnkStruct_0229bd4c;

typedef struct {
    char pad_00[0x2f78];
    unsigned short arr[16];
} UnkStruct_0229bd1c;

typedef struct {
    unsigned char pad_00[0x2f78];
    unsigned short array[16];
} UnkStruct_0229bcf0;

typedef struct {
    char pad_00[0xaa];
    u16 unk_AA;
    char pad_AC[0xb1 - 0xac];
    u8 b1;
    char pad_B2[1];
    u8 b3;
    char pad_B4[0x1d4 - 0xb4];
    char unk_1D4[0x2f78 - 0x1d4];
    u16 arr[0x10];     // 0x2f78
    u8 unk_2F98[0x10]; // 0x2f98
} UnkStruct_0229ba2c;

extern int func_ov129_0229be7c(void *p0, int p1, int p2);
extern int func_ov127_022996d8(int a);
extern int func_ov127_022996c8(int a);
extern int func_ov127_022996e4(unsigned short *out, int a, int b);
extern int func_ov127_02299a18(const void *p, const void *a, const void *b, unsigned int *out1, unsigned int *out2);
extern unsigned int func_ov127_02299844(unsigned int a, unsigned int b);
extern unsigned int func_ov127_02299804(unsigned int a, unsigned int b);
extern const int data_ov129_0229db04[5];
extern const int data_ov129_0229db18[5];
extern unsigned char *func_ov127_022996bc(unsigned short x);
extern void func_ov002_0220a658(void *, int);
extern void func_0200467c(int);
extern void func_ov129_0229c610(void *p, int arg);

int func_ov129_0229bd1c(UnkStruct_0229bd1c *p);

void func_ov129_0229be58(void *obj, unsigned short val, int param)
{
    unsigned char *q = (unsigned char *) obj + 0x2f98 + val;
    if (*q != 0) {
        return;
    }
    if (func_ov129_0229be7c(obj, val, param) != 0) {
        return;
    }
    *q = 3;
}

void func_ov129_0229be04(void *obj, int param)
{
    unsigned short local[10];
    int v1, v2, count, i;

    if (param == 0xFF) {
        return;
    }
    if (func_ov129_0229bd1c((UnkStruct_0229bd1c *) obj) == -1) {
        return;
    }

    v1 = func_ov127_022996d8(param);
    v2 = func_ov127_022996c8(param);
    count = func_ov127_022996e4(local, v1, v2);

    for (i = 0; i < count; i++) {
        func_ov129_0229be58(obj, local[i], param);
    }
}

int func_ov129_0229bd4c(UnkStruct_0229bd4c *self, const char *a, const char *b)
{
    unsigned int zero1 = 0;
    unsigned int zero2 = 0;
    unsigned int out1, out2;
    int i;

    self->byte = 0xff;
    self->hword = 0xffff;

    for (i = 0; i < 5; i++) {
        if (func_ov127_02299a18((const char *) self + 0x734, a + data_ov129_0229db04[i], b + data_ov129_0229db18[i], &out1,
                                &out2) != 0) {
            if (self->byte == 0xff) {
                unsigned int val = func_ov127_02299844(out1, out2);
                if (val != ~zero1) {
                    self->byte = (unsigned char) val;
                }
            }
            if (self->hword == 0xffff) {
                unsigned int val = func_ov127_02299804(out1, out2);
                if (val != ~zero2) {
                    self->hword = (unsigned short) val;
                }
            }
        }
    }

    if (self->byte != 0xff || self->hword != 0xffff) {
        return 1;
    }
    return 0;
}

int func_ov129_0229bd1c(UnkStruct_0229bd1c *p)
{
    int i;
    for (i = 0; i < 16; i++) {
        if (p->arr[i] == 0xffff) {
            return i;
        }
    }
    return -1;
}

int func_ov129_0229bcf0(UnkStruct_0229bcf0 *s, unsigned short target)
{
    int i;
    for (i = 0; i < 16; i++) {
        if (target == s->array[i]) {
            return i;
        }
    }
    return -1;
}

int func_ov129_0229bca4(unsigned char *base, void *obj)
{
    unsigned short arr[8];
    void *a;
    int b;
    int n;
    int i;
    unsigned char *p;

    a = (void *) func_ov127_022996d8((int) obj);
    b = func_ov127_022996c8((int) obj);
    n = func_ov127_022996e4(arr, (int) a, b);

    for (i = 0; i < n; i++) {
        p = base + arr[i];
        if (p[0x2f98] == 2) {
            return 1;
        }
    }
    return 0;
}

int func_ov129_0229bc34(void *arg0, unsigned int arg1)
{
    unsigned short local[10];
    int count;
    int i;
    int x, y;
    x = func_ov127_022996d8(arg1);
    y = func_ov127_022996c8(arg1);
    count = func_ov127_022996e4(local, x, y);
    for (i = 0; i < count; i++) {
        if (((unsigned char *) arg0 + local[i])[0x2f98] == 1) {
            return 0;
        }
    }
    for (i = 0; i < count; i++) {
        if (func_ov129_0229be7c(arg0, (unsigned short) local[i], arg1) == 0) {
            return 1;
        }
    }
    return 3;
}

unsigned short func_ov129_0229bbd8(int unused, int p1, unsigned char p2)
{
    int k = 0;
    unsigned short arr[8];
    int i;
    int j;
    int count;
    unsigned char *s;
    int x = func_ov127_022996d8(p1);
    int y = func_ov127_022996c8(p1);

    count = func_ov127_022996e4(arr, x, y);
    for (i = 0; i < count; i++) {
        s = func_ov127_022996bc(arr[i]);
        for (j = k; j < 2; j++) {
            if (p2 == s[j]) {
                return arr[i];
            }
        }
    }
    return 0xffff;
}

int func_ov129_0229ba2c(UnkStruct_0229ba2c *self)
{
    u8 *p;
    char *mp;
    u16 *slot;
    int n;
    int i;
    int k;
    int cnt;
    int changed;
    int m;
    int r;
    int t;
    int u;
    int idx;
    u8 *q;
    u8 c;
    u8 marks[16];
    u16 buf[8];

    k = func_ov129_0229bcf0((UnkStruct_0229bcf0 *) self, (u16) self->unk_AA);
    if (k == -1) {
        return 0;
    }
    slot = &self->arr[k];
    *slot = 0xffff;

    changed = 1;
    cnt = 0;
    for (i = 0; i < 16; i++) {
        if (self->arr[i] == 0xffff) {
            marks[i] = 3;
        } else {
            if (cnt > 0) {
                marks[i] = 0;
            } else {
                marks[i] = 1;
            }
            cnt++;
        }
    }
    if (cnt == 0) {
        func_ov002_0220a658(self->unk_1D4, 6);
        self->b1 = 0;
        self->b3 = 0xff;
        func_0200467c(0x882);
        return 2;
    }
    while (changed) {
        changed = 0;
        for (i = 0; i < 16; i++) {
            mp = (char *) &marks[i];
            if (marks[i] == 1) {
                p = (u8 *) func_ov127_022996bc((u16) self->arr[i]);
                for (m = 0; m < 2; m++) {
                    t = func_ov127_022996d8((u8) p[m]);
                    u = func_ov127_022996c8((u8) p[m]);
                    n = func_ov127_022996e4((unsigned short *) buf, t, u);
                    for (r = 0; r < n; r++) {
                        idx = func_ov129_0229bcf0((UnkStruct_0229bcf0 *) self, (u16) buf[r]);
                        if (idx != -1) {
                            q = &marks[idx];
                            if (marks[idx] == 0) {
                                *q = 1;
                            }
                        }
                    }
                }
                *mp = 2;
            }
        }
        for (i = 0; i < 16; i++) {
            if (marks[i] == 1) {
                changed = 1;
            }
        }
    }
    for (i = 0; i < 16; i++) {
        if (marks[i] == 0) {
            *slot = self->unk_AA;
            return 0;
        }
    }

    p = (u8 *) func_ov127_022996bc((u16) self->unk_AA);
    c = 0xff;
    if (p[0] == self->b3) {
        c = p[1];
    } else if (p[1] == self->b3) {
        c = p[0];
    }
    if (c != 0xff) {
        self->unk_2F98[self->unk_AA] = 0;
        if (func_ov129_0229bca4((unsigned char *) self, (void *) self->b3) == 0) {
            self->b3 = c;
        }
    }
    func_0200467c(0x882);
    return 2;
}

int func_ov129_0229b9d8(unsigned char *p)
{
    int result = 0;
    if (p[0xb0] == 0xff) {
        goto end;
    }
    result = func_ov129_0229bc34(p, p[0xb0]);
    if (result == 1) {
        goto body;
    }
    if (result == 3) {
        func_ov129_0229c610(p, 0x16);
    }
    goto end;
body:
    p[0xb1] = 1;
    p[0xb2] = p[0xb0];
    p[0xb3] = p[0xb0];
end:
    return result;
}

void func_ov129_0229b9a0(unsigned char *param0)
{
    unsigned char *r0;
    unsigned char r2;
    unsigned char r1;
    unsigned char r0_2;

    func_0200467c(0x881);
    r0 = func_ov127_022996bc(*(unsigned short *) (param0 + 0xaa));
    r2 = *r0;
    r1 = *(param0 + 0xb3);
    if (r2 == r1) {
        r0_2 = *(r0 + 1);
        *(param0 + 0xb3) = r0_2;
    } else {
        *(param0 + 0xb3) = r2;
    }
}
