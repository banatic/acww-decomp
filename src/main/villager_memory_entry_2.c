/* villager_memory_entry_2: 14 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02081f30 @ 0x02081f30, 0x30 bytes, Thumb
 * func_02081f18 @ 0x02081f18, 0x18 bytes, Thumb
 * func_02081ef0 @ 0x02081ef0, 0x28 bytes, Thumb
 * func_02081edc @ 0x02081edc, 0x12 bytes, Thumb
 * func_02081e94 @ 0x02081e94, 0x46 bytes, Thumb
 * func_02081e14 @ 0x02081e14, 0x80 bytes, Thumb
 * func_02081e10 @ 0x02081e10, 0x4 bytes, Thumb
 * func_02081d88 @ 0x02081d88, 0x88 bytes, Thumb
 * func_02081d68 @ 0x02081d68, 0x20 bytes, Thumb
 * func_02081d64 @ 0x02081d64, 0x4 bytes, Thumb
 * func_02081d60 @ 0x02081d60, 0x2 bytes, Thumb
 * func_02081d28 @ 0x02081d28, 0x38 bytes, Thumb
 * func_02081d20 @ 0x02081d20, 0x6 bytes, Thumb
 * func_02081d18 @ 0x02081d18, 0x6 bytes, Thumb
 */

typedef struct {
    char pad_00[0x54];
    int unk_54;
    int unk_58;
    char unk_5C[0x0e];
    unsigned short unk_6A;
} UnkStruct_02081f30;

typedef struct {
    unsigned char unk_00[0x5c];
    unsigned char unk_5C;
} UnkStruct_02081f18;

typedef struct UnkStruct_02081d88 {
    unsigned char pad_00[0x7c];
    unsigned short lo : 8;
    unsigned short mode : 3;
    unsigned short hi : 5;
} UnkStruct_02081d88;

typedef struct {
    unsigned short unk_00;
    char data[12];
} UnkStruct_02081d28;

typedef struct {
    unsigned char pad_00[108];
    unsigned char unk_6C;
} UnkStruct_02081d18;

extern void *func_0209529c(void *);
extern void func_020642fc(void *);
extern void func_020642f8(void *arg);
extern int func_0209526c(void *arg);
extern void func_02095238(void *param1);
extern void MI_CpuFill8(void *param1, int param2, int param3);
extern int func_020951bc(void *object);
extern void *func_020950a8(void *);
extern void MI_CpuCopy8(void *, const void *, unsigned int);
extern struct UnkStruct_02081e14;
extern const char data_021dc7aa[];
extern const char data_021f3b68[];
extern void func_0209525c(struct UnkStruct_02081e14 *self, const char *str);
extern void func_0209e474(void *buf);
extern void func_020642d0(void *a, const char *b);
extern void func_02081a90(struct UnkStruct_02081e14 *self, const char *str);
extern int func_0209dffc(const unsigned char *);
extern int func_0209e3ac(void *p0, int p1, int p2);
extern int func_0209e380(int p0, void *p1);
extern int func_02081cec(void *obj, signed char val);
extern __arm int memcmp(const void *, const void *, unsigned int);
extern int func_0209518c(void *, void *);

void func_02081ef0(void *param1);
void func_02081e14(struct UnkStruct_02081e14 *self, const char *str1, const char *str2, char *buf);
int func_02081e10(int p0);
int func_02081d88(UnkStruct_02081d88 *self, void *param2);
int func_02081d68(void *obj);
int func_02081d64(int p0);
void *func_02081d60(void *record);

UnkStruct_02081f30 *func_02081f30(UnkStruct_02081f30 *obj)
{
    func_0209529c(obj);
    obj->unk_54 = 0;
    obj->unk_58 = 0;
    func_020642fc(obj->unk_5C);
    obj->unk_6A = 0xfff1;
    func_02081ef0(obj);
    return obj;
}

UnkStruct_02081f18 *func_02081f18(UnkStruct_02081f18 *ptr)
{
    func_020642f8(&ptr->unk_5C);
    func_0209526c(ptr);
    return ptr;
}

void func_02081ef0(void *param1)
{
    MI_CpuFill8(param1, 0, 0x80);
    func_02095238(param1);
    *(int *) ((char *) param1 + 0x54) = 0;
    *(int *) ((char *) param1 + 0x58) = 0;
    *(unsigned short *) ((char *) param1 + 0x6a) = 0xfff1;
}

int func_02081edc(void *object)
{
    return func_020951bc(func_02081d60(object));
}

int func_02081e94(void *param0, void *param1, void *param2, void *param3)
{
    int result = 0;

    if (func_020951bc(param1)) {
        void *dst;
        char *src;

        func_02081ef0(param0);
        func_02081e14((struct UnkStruct_02081e14 *) param0, (const char *) param1, (const char *) param2, (char *) param3);

        dst = func_020950a8(param1);
        src = (char *) param0 + 0x1e;
        MI_CpuCopy8(dst, src, 0xc);

        result = 1;
    }

    return result;
}

void func_02081e14(struct UnkStruct_02081e14 *self, const char *str1, const char *str2, char *buf)
{
    int local[3];

    local[0] = 0;
    local[1] = 0;

    if (str1 != 0) {
        if (func_020951bc((void *) str1)) {
            func_0209525c(self, str1);
        }
    }
    if (str2 == 0) {
        str2 = data_021dc7aa;
    }
    if (buf == 0) {
        func_0209e474(local);
        buf = (char *) local;
    }
    if (func_02081d88((UnkStruct_02081d88 *) self, (void *) buf)) {
        func_02081d68((void *) self);
    }
    func_020642d0((void *) func_02081d64((int) self), str2);
    MI_CpuCopy8(buf, (void *) func_02081e10((int) self), 8);
    func_02081a90(self, data_021f3b68);
}

int func_02081e10(int p0)
{
    return ((int) (p0) + (84));
}

int func_02081d88(UnkStruct_02081d88 *self, void *param2)
{
    int x = func_02081e10((int) self);
    unsigned short field = 0;
    int result = 0;
    int w;

    if (func_0209dffc((const unsigned char *) x) == 0) {
        if (func_0209e3ac(param2, x, 0x3f) == 1) {
            w = func_0209e380(x, param2);
            if (w == 0) {
                field = self->mode;
            } else {
                if (w == 1) {
                    field = (unsigned short) (self->mode + 1);
                }
                result = 1;
            }
        } else {
            result = 1;
        }
    } else {
        result = 1;
    }

    if (field > 4) {
        field = 4;
    }

    self->mode = field;
    return result;
}

int func_02081d68(void *obj)
{
    unsigned short raw = *(unsigned short *) ((char *) obj + 0x7c);
    int n = ((unsigned int) raw << 21) >> 29;
    if (n > 4) {
        n = 4;
    }
    n++;
    return func_02081cec(obj, (signed char) n);
}

int func_02081d64(int p0)
{
    return ((int) (p0) + (92));
}

void *func_02081d60(void *record)
{
    return record;
}

int func_02081d28(UnkStruct_02081d28 *a, UnkStruct_02081d28 *b)
{
    if (a->unk_00 != b->unk_00) {
        goto fail;
    }
    if (memcmp((char *) a + 2, (char *) b + 2, 0xc) != 0) {
        goto fail;
    }
    if (func_0209518c(a, b) == 0) {
        goto fail;
    }
    return 1;
fail:
    return 0;
}

int func_02081d20(signed char *p)
{
    return p[108];
}

void func_02081d18(UnkStruct_02081d18 *p, unsigned char v)
{
    p->unk_6C = v;
}
