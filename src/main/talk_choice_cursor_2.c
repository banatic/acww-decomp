/* talk_choice_cursor_2: 15 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020ab37c @ 0x020ab37c, 0x20 bytes, Thumb
 * func_020ab36c @ 0x020ab36c, 0x10 bytes, Thumb
 * func_020ab354 @ 0x020ab354, 0x18 bytes, Thumb
 * func_020ab348 @ 0x020ab348, 0xc bytes, Thumb
 * func_020ab344 @ 0x020ab344, 0x4 bytes, Thumb
 * func_020ab338 @ 0x020ab338, 0xc bytes, Thumb
 * func_020ab334 @ 0x020ab334, 0x4 bytes, Thumb
 * func_020ab30c @ 0x020ab30c, 0x28 bytes, Thumb
 * func_020ab304 @ 0x020ab304, 0x8 bytes, Thumb
 * func_020ab2fc @ 0x020ab2fc, 0x8 bytes, Thumb
 * func_020ab2e0 @ 0x020ab2e0, 0x1a bytes, Thumb
 * func_020ab278 @ 0x020ab278, 0x66 bytes, Thumb
 * func_020ab270 @ 0x020ab270, 0x8 bytes, Thumb
 * func_020ab238 @ 0x020ab238, 0x38 bytes, Thumb
 * func_020ab230 @ 0x020ab230, 0x8 bytes, Thumb
 */

typedef struct {
    int unk_00;
    int unk_04;
    int array[5];
    int unk_1C;
    int unk_20;
    int unk_24;
    int unk_28;
    int unk_2C;
} UnkStruct_020ab37c;

typedef struct {
    char pad_00[0x20];
    int unk_20;
} UnkStruct_020ab348;

typedef struct {
    char pad_00[0x20];
    int unk_20;
} UnkStruct_020ab338;

typedef struct {
    unsigned char pad_00[0x1C];
    void *unk_1C;
    void *unk_20;
} UnkStruct_020ab2e0;

struct UnkStruct_020ab278 {
    int unk_00;
    char pad_04[28];
    int unk_20;
};

struct UnkStruct_020ab238 {
    unsigned char pad_00[8];
    unsigned int arr[5];
    unsigned int max;
    unsigned int count;
};

extern void func_020ab130(int);
extern unsigned int func_020ab51c(void *arg0);
extern int func_020ab504(int a);
extern void func_020ab58c(void *);
extern void func_020ab1a0(void *);
extern void func_020ab17c(void *);
extern void func_020ab158(void *);
extern void func_020ab558(void *ptr);
extern int func_020ab0f4(void *object);
extern int func_020a7e50(void);
extern int func_020ab0a4(struct UnkStruct_020ab278 *);
extern int func_020a7e44(void);
extern int func_020aaf20(struct UnkStruct_020ab278 *);
extern void func_020ab42c(int, int);
extern unsigned int func_020515b8(unsigned int);

void func_020ab238(struct UnkStruct_020ab238 *self);
void func_020ab230(int *p0);

void func_020ab37c(UnkStruct_020ab37c *s, int val)
{
    unsigned int i;
    int zero = 0;
    s->unk_00 = zero;
    s->unk_04 = val;
    s->unk_1C = zero;
    s->unk_20 = zero;
    s->unk_24 = zero;
    s->unk_28 = zero;
    s->unk_2C = zero;
    for (i = 0; i < 5; i++) {
        s->array[i] = zero;
    }
}

int func_020ab36c(int arg)
{
    func_020ab130(arg);
    return arg;
}

void func_020ab354(void *arg0, void *arg1)
{
    func_020ab51c(arg1);
    *(void **) ((unsigned char *) arg0 + 0x20) = arg1;
}

unsigned int func_020ab348(UnkStruct_020ab348 *obj)
{
    return func_020ab51c((void *) obj->unk_20);
}

int func_020ab344(int *p0)
{
    return p0[0];
}

int func_020ab338(UnkStruct_020ab338 *obj)
{
    return func_020ab504(obj->unk_20);
}

int func_020ab334(int *p0)
{
    return p0[7];
}

void func_020ab30c(void *param)
{
    void *r4 = param;
    func_020ab58c(*(void **) ((char *) r4 + 0x20));
    func_020ab1a0(r4);
    *(int *) r4 = 0;
    *(int *) ((char *) r4 + 0x24) = 0;
    func_020ab230((int *) r4);
    func_020ab238((struct UnkStruct_020ab238 *) r4);
}

void func_020ab304(void *argument0)
{
    func_020ab17c((void *) argument0);
}

void func_020ab2fc(void *argument0)
{
    func_020ab158((void *) argument0);
}

void func_020ab2e0(UnkStruct_020ab2e0 *obj)
{
    func_020ab130((int) obj);
    func_020ab558(obj->unk_20);
    obj->unk_1C = 0;
    obj->unk_20 = 0;
}

void func_020ab278(struct UnkStruct_020ab278 *self)
{
    if (self->unk_20 != 0 && func_020ab504(self->unk_20) < 0) {

        if (func_020ab0f4(self) != 0) {
            func_020ab230((int *) self);
            return;
        } else {
            int flag = 0;
            if (func_020a7e50() != 0) {
                if (func_020ab0a4(self) != 0) {
                    flag = 1;
                }
            } else {
                if (func_020a7e44() != 0) {
                    if (func_020aaf20(self) != 0) {
                        flag = 1;
                    }
                }
            }
            if (flag != 0) {
                func_020ab42c(self->unk_20, self->unk_00);
            }
        }
    }
}

int func_020ab270(void *object)
{
    return func_020a7e50();
}

void func_020ab238(struct UnkStruct_020ab238 *self)
{
    unsigned int n;
    unsigned int max;
    unsigned int i;
    unsigned int v;

    n = func_020ab51c((void *) self->count);
    max = 0;
    for (i = 0; i < n; i++) {
        if (self->arr[i] != 0) {
            v = func_020515b8(self->arr[i]);
            if (v > max) {
                max = v;
            }
        }
    }
    self->max = max;
}

void func_020ab230(int *p0)
{
    p0[10] = 0;
    p0[11] = 0;
}
