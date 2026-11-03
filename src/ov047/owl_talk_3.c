/* owl_talk_3: 4 functions, module ov047
 * mwccarm 1.2/base -O4,s
 * func_ov047_02261990 @ 0x02261990, 0x24 bytes, Thumb
 * func_ov047_02261978 @ 0x02261978, 0x18 bytes, Thumb
 * func_ov047_02261958 @ 0x02261958, 0x20 bytes, Thumb
 * func_ov047_02261908 @ 0x02261908, 0x50 bytes, Thumb
 */

typedef struct {
    void *unk_00;
    unsigned char pad_04[0xce - 4];
    unsigned short unk_CE;
} UnkStruct_02261990;

struct obj_ov047 {
    unsigned int *data;
};

struct Pair {
    int a;
    int b;
};

struct UnkStruct_02261908 {
    char pad_00[0xb8];
    struct Pair pair1;
    struct Pair pair2;
    int flag;
    char pad_CC[2];
    unsigned short shortVal;
};

void *func_0202eb70(void *self);
extern int data_ov047_02262c14;
extern void *func_0202eb20(void *self);
extern void func_020edb3c(void *);
extern void func_0201612c(void *self);
extern struct Pair __ptmf_null;

UnkStruct_02261990 *func_ov047_02261990(UnkStruct_02261990 *self)
{
    func_0202eb70(self);
    self->unk_00 = &data_ov047_02262c14;
    self->unk_CE = 0xfff1;
    return self;
}

void *func_ov047_02261978(struct obj_ov047 *self)
{
    self->data = ((unsigned int *) &data_ov047_02262c14);
    func_0202eb20(self);
    return self;
}

void *func_ov047_02261958(void *p)
{
    *(void **) p = (void *) ((char *) &data_ov047_02262c14);
    func_0202eb20(p);
    func_020edb3c(p);
    return p;
}

void func_ov047_02261908(struct UnkStruct_02261908 *self)
{
    struct Pair p;
    func_0201612c(self);
    self->flag = -1;
    self->shortVal = 0xfff1;
    p = __ptmf_null;
    self->pair1 = p;
    self->pair2 = p;
}
