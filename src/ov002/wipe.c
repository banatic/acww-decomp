/* wipe: 5 functions, module ov002
 * mwccarm 1.2/base -O4,s
 * func_ov002_02208458 @ 0x02208458, 0x40 bytes, Thumb
 * func_ov002_02208418 @ 0x02208418, 0x40 bytes, Thumb
 * func_ov002_022083b8 @ 0x022083b8, 0x60 bytes, Thumb
 * func_ov002_02208348 @ 0x02208348, 0x6e bytes, Thumb
 * func_ov002_02208344 @ 0x02208344, 0x4 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0xc];
    unsigned int unk_0C;
    unsigned int unk_10;
    unsigned int unk_14;
    unsigned char unk_18;
} UnkStruct_02208458;

typedef struct {
    unsigned char pad_00[0xc];
    int unk_0C;
    unsigned char pad_10[0x18 - 0xc - 4];
    unsigned char dir;
} UnkStruct_022083b8;

typedef struct UnkStruct_02208348 {
    char pad_00[0xc];
    int unk_0C;
    char pad_10[0x4];
    int unk_14;
    unsigned char unk_18;
} UnkStruct_02208348;

extern void func_ov002_0220882c(UnkStruct_02208458 *self, unsigned int denominator);
extern void func_0200284c(int a, int b, int c);
extern void func_02002808(int, int, int, int, int);

void func_ov002_02208458(UnkStruct_02208458 *self, int arg1, unsigned char byte, unsigned int word)
{
    self->unk_18 = byte;
    self->unk_14 = word;
    func_ov002_0220882c(self, (unsigned int) arg1);
    {
        unsigned char val = self->unk_18;
        switch (val) {
            case 0:
            case 1:
                self->unk_0C = 0xC0;
                self->unk_10 = 0xC0;
                break;
            case 2:
            case 3:
                self->unk_0C = 0x100;
                self->unk_10 = 0x100;
                break;
        }
    }
}

void func_ov002_02208418(void *object, int denominator, unsigned char direction, int word)
{
    int result;
    *(unsigned char *) ((char *) object + 0x18) = direction;
    *(int *) ((char *) object + 0x14) = word;
    func_ov002_0220882c((UnkStruct_02208458 *) object, (unsigned int) denominator);
    *(int *) ((char *) object + 0xc) = 0;
    result = *(unsigned char *) ((char *) object + 0x18);
    switch (result) {
        case 0:
        case 1:
            result = 0xc0;
            *(int *) ((char *) object + 0x10) = result;
            break;
        case 2:
        case 3:
            result = 0x100;
            *(int *) ((char *) object + 0x10) = result;
            break;
    }
}

void func_ov002_022083b8(UnkStruct_022083b8 *p, int a, int b, int c)
{
    switch (p->dir) {
        case 0:
            func_0200284c(a, -b, -(p->unk_0C + c));
            break;
        case 1:
            func_0200284c(a, -b, p->unk_0C - c);
            break;
        case 2:
            func_0200284c(a, p->unk_0C - b, -c);
            break;
        case 3:
            func_0200284c(a, -(p->unk_0C + b), -c);
            break;
    }
}

void func_ov002_02208348(UnkStruct_02208348 *obj, int param2)
{
    int val = 0;
    int val2 = val;
    int val3 = 0xff;
    int val4 = 0xc0;

    switch (obj->unk_18) {
        case 0:
            val2 = obj->unk_0C - obj->unk_14;
            if (val2 < 0) {
                val2 = val;
            }
            break;
        case 1:
            val4 = obj->unk_14 + 0xc0 - obj->unk_0C;
            if (val4 > 0xbf) {
                val4 = 0xbf;
            }
            break;
        case 2:
            val3 = val3 - obj->unk_0C;
            if (val3 < 1) {
                val3 = 1;
            }
            break;
        case 3:
            val = obj->unk_0C;
            if (val > 0xfe) {
                val = 0xfe;
            }
            break;
        default:
            break;
    }

    func_02002808(param2, val, val2, val3, val4);
}

void func_ov002_02208344(int *p0, int p1)
{
    p0[4] = p1;
}
