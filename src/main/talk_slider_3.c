/* talk_slider_3: 10 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020aaeb4 @ 0x020aaeb4, 0x34 bytes, Thumb
 * func_020aaea4 @ 0x020aaea4, 0x10 bytes, Thumb
 * func_020aae8c @ 0x020aae8c, 0x18 bytes, Thumb
 * func_020aae88 @ 0x020aae88, 0x4 bytes, Thumb
 * func_020aae84 @ 0x020aae84, 0x4 bytes, Thumb
 * func_020aae78 @ 0x020aae78, 0xc bytes, Thumb
 * func_020aae40 @ 0x020aae40, 0x38 bytes, Thumb
 * func_020aae38 @ 0x020aae38, 0x8 bytes, Thumb
 * func_020aae30 @ 0x020aae30, 0x8 bytes, Thumb
 * func_020aae14 @ 0x020aae14, 0x1a bytes, Thumb
 */

typedef struct {
    int param0;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14[5];
    int unk_28;
    int unk_2C;
    unsigned char unk_30;
    unsigned char unk_31;
    int unk_34;
} UnkStruct_020aaeb4;

typedef struct {
    char pad_00[0x34];
    void *unk_34;
} UnkStruct_020aae78;

struct UnkStruct_020aae14 {
    unsigned char pad_00[0x28];
    unsigned int unk_28;
    unsigned char pad_2C[0x34 - 0x2C];
    void *unk_34;
};

extern void func_020aac1c(int arg);
extern unsigned int func_020ab51c(void *);
extern int func_020ab504(void *arg1);
extern void func_020ab58c(void *);
extern void func_020aac8c(void *);
extern void func_020aa9c0(void *);
extern void func_020aad08(void *);
extern void func_020aac68(void *);
extern void func_020aac44(void *);
extern void func_020ab558(void *ptr);

void func_020aaeb4(UnkStruct_020aaeb4 *arg0, int arg1)
{
    unsigned int i;
    arg0->param0 = arg1;
    arg0->unk_04 = 0;
    arg0->unk_08 = 0x800;
    arg0->unk_0C = 0x800;
    arg0->unk_10 = 0;
    arg0->unk_28 = 0;
    arg0->unk_2C = 0;
    arg0->unk_30 = 0;
    arg0->unk_31 = 0;
    arg0->unk_34 = 0;
    for (i = 0; i < 5; i++) {
        arg0->unk_14[i] = 0;
    }
}

int func_020aaea4(int arg)
{
    func_020aac1c(arg);
    return arg;
}

void func_020aae8c(void *arg0, void *arg1)
{
    void *r4;
    void *r5;

    r5 = arg0;
    r4 = arg1;
    func_020ab51c(r4);
    *(void **) ((char *) r5 + 0x34) = r4;
}

int func_020aae88(int *p0)
{
    return p0[2];
}

int func_020aae84(int *p0)
{
    return p0[10];
}

int func_020aae78(UnkStruct_020aae78 *self)
{
    return func_020ab504(self->unk_34);
}

void func_020aae40(void *param)
{
    void *r4 = param;
    func_020ab58c(*(void **) ((char *) r4 + 0x34));
    func_020aac8c(r4);
    *(int *) ((char *) r4 + 4) = 0;
    *(int *) ((char *) r4 + 8) = 0x800;
    *(int *) ((char *) r4 + 0xc) = 0x800;
    func_020aa9c0(r4);
    func_020aad08(r4);
    *(char *) ((char *) r4 + 0x31) = 0;
}

void func_020aae38(void *argument0)
{
    func_020aac68((void *) argument0);
}

void func_020aae30(void *argument0)
{
    func_020aac44((void *) argument0);
}

void func_020aae14(struct UnkStruct_020aae14 *obj)
{
    func_020aac1c((int) obj);
    func_020ab558(obj->unk_34);
    obj->unk_28 = 0;
    obj->unk_34 = 0;
}
