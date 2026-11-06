/* talk_tags_7: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02069e14 @ 0x02069e14, 0x84 bytes, Thumb
 * func_02069e10 @ 0x02069e10, 0x2 bytes, Thumb
 * func_02069d8c @ 0x02069d8c, 0x84 bytes, Thumb
 */

typedef struct {
    char pad_00[0x24];
    char *unk_24;
    char pad_28[0x34];
    int unk_5C;
} UnkStruct_02069e14;

typedef int (*Callback)(void *);

typedef int (*SubMethod)(void *);

struct SubVtbl {
    SubMethod func0;
    SubMethod func1;
    SubMethod func2;
    SubMethod func3;
};

struct UnkStruct_02069d8c {
    struct SubVtbl *vtbl;
};

struct Big {
    unsigned char pad_00[0x1a58];
    char unk_1A58;
    unsigned char pad1[0x7];
    int unk_1A60;
    unsigned char pad_1A64[0x3c0];
    struct UnkStruct_02069d8c sub;
};

struct UnkStruct_02069d8c_2 {
    unsigned char pad_00[0x24];
    struct Big *unk_24;
    unsigned char pad1[0x34];
    int unk_5C;
};

extern int data_020df160;
extern int func_0206777c(void *);
extern void func_0206bb9c(void *object, int code, const void *message);
extern int func_020a82f8(int);
extern void func_020a9334(void *, int);
extern void func_020a7994(void *, int);
extern unsigned char data_020df154;
extern int func_02067728(struct Big *);

void func_02069e14(UnkStruct_02069e14 *self)
{
    if (func_0206777c(self->unk_24) == 0) {
        func_0206bb9c(self, 0xdb2, &data_020df160);
    }
    func_020a9334(self, func_020a82f8(self->unk_5C));

    {
        char *p = self->unk_24 + 0x1e04;
        func_020a9334(self, (*(Callback *) ((char *) *(void **) p + 0xc))(p));
    }

    func_020a9334(self, func_020a82f8(5));

    {
        char *p = self->unk_24 + 0x1e04;
        func_020a7994(self->unk_24 + 0x1a58, (*(Callback *) ((char *) *(void **) p + 0xc))(p));
    }

    *(int *) (self->unk_24 + 0x1a60) = 1;
}

void func_02069e10(void) {}

void func_02069d8c(struct UnkStruct_02069d8c_2 *self)
{
    if (func_02067728(self->unk_24) == 0) {
        func_0206bb9c(self, 0xdd0, &data_020df154);
    }
    func_020a9334((void *) self, func_020a82f8(self->unk_5C));
    func_020a9334((void *) self, ((struct UnkStruct_02069d8c *) ((char *) self->unk_24 + 0x1e24))
                                     ->vtbl->func3((struct UnkStruct_02069d8c *) ((char *) self->unk_24 + 0x1e24)));
    func_020a9334((void *) self, func_020a82f8(2));
    func_020a7994((char *) self->unk_24 + 0x1a58,
                  ((struct UnkStruct_02069d8c *) ((char *) self->unk_24 + 0x1e24))
                      ->vtbl->func3((struct UnkStruct_02069d8c *) ((char *) self->unk_24 + 0x1e24)));
    self->unk_24->unk_1A60 = 1;
}
