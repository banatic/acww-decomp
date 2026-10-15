/* func_02069e14 @ 0x02069e14, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x24];
    char *unk_24;
    char pad_28[0x34];
    int unk_5C;
} UnkStruct_02069e14;

extern int data_020df160;
extern int func_0206777c(void *);
extern void func_0206bb9c(void *object, int code, const void *message);
extern int func_020a82f8(int);
extern void func_020a9334(void *, int);
extern void func_020a7994(void *, int);
typedef int (*Callback)(void *);

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
