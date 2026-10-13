/* func_ov003_02212574 @ 0x02212574, 0x1b4 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x98];
    void *unk_98;
    char pad_9C[0x7d4 - 0x9c];
    unsigned char data[3];
    char pad_7D7[0x80c - 0x7d7];
    int unk_80C;
} UnkStruct_02212574;

typedef struct {
    int x, y, z;
} Vec3;

extern void func_0204f794(Vec3 *out, unsigned char a, unsigned char b);
extern void func_0204f818(int *a, int *b, Vec3 *in);
extern int func_ov003_0220cf68(UnkStruct_02212574 *self, Vec3 *in, unsigned char *flag);
extern void func_ov003_0221248c(UnkStruct_02212574 *self, int a, int b);
extern void func_ov003_022122ac(UnkStruct_02212574 *self, int a, int *vec, int b, int c);
extern void func_ov003_02211d4c(UnkStruct_02212574 *self, int a, int *vec, int b, int c);
extern void func_ov003_02211980(UnkStruct_02212574 *self, int *vec, int a, int b, int c);
extern void func_ov003_022109f8(UnkStruct_02212574 *self, int a, int *vec, int b, int c, int d);
extern void func_ov003_022123a8(UnkStruct_02212574 *self, int a, int b);

int func_ov003_02212574(UnkStruct_02212574 *self, Vec3 *src, unsigned char flag)
{
    int r6;
    int r7;
    unsigned char *r5;
    Vec3 buffer;
    int a, b;
    int c, d;
    int local2[2];
    int local6[2];
    int local7[2];
    Vec3 local3, local4, local5, local8;

    if (self->unk_98) {
        return -1;
    }

    r7 = 0;
    r5 = (unsigned char *) self + 0x7d4;

    if (flag) {
        buffer.x = src->x;
        buffer.y = src->y;
        buffer.z = src->z;
    } else {
        func_0204f794(&buffer, r5[0], r5[1]);
        if (r5[2] == 0) {
            r7 = 1;
            flag = 1;
        }
    }

    r6 = func_ov003_0220cf68(self, &buffer, &flag);

    a = 0;
    b = 0;
    func_0204f818(&a, &b, &buffer);

    if (r7 != 0) {
        if (self->unk_80C != -1) {
            r5[2] = 1;
        }
    }

    switch (r6) {
        case 0:
            break;
        case 1:
            func_ov003_0221248c(self, 6, -1);
            break;
        case 2:
            local2[0] = a;
            local2[1] = b;
            func_ov003_022122ac(self, 0, local2, 6, -1);
            break;
        case 3:
            local3.x = buffer.x;
            local3.y = buffer.y;
            local3.z = buffer.z;
            func_ov003_02211d4c(self, 0, (int *) &local3, 6, -1);
            break;
        case 4:
            local4.x = buffer.x;
            local4.y = buffer.y;
            local4.z = buffer.z;
            func_ov003_02211d4c(self, 1, (int *) &local4, 6, -1);
            break;
        case 5:
            local5.x = buffer.x;
            local5.y = buffer.y;
            local5.z = buffer.z;
            func_ov003_02211980(self, (int *) &local5, 0, 6, -1);
            break;
        case 6:
            c = 0;
            d = 0;
            func_0204f818(&c, &d, &buffer);
            local6[0] = c;
            local6[1] = d;
            func_ov003_022109f8(self, 0, local6, 0xfff1, 6, -1);
            break;
        case 7:
            func_ov003_022123a8(self, 6, -1);
            break;
        case 8:
            local7[0] = a;
            local7[1] = b;
            func_ov003_022122ac(self, 1, local7, 6, -1);
            break;
        case 9:
            local8.x = buffer.x;
            local8.y = buffer.y;
            local8.z = buffer.z;
            func_ov003_02211980(self, (int *) &local8, 1, 6, -1);
            break;
    }

    return r6;
}
