/* func_0201eed8 @ 0x0201eed8, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct InnerType {
    char pad_00[0x830];
    int value;
} InnerType;

typedef struct SelfType {
    char pad_00[0x100];
    InnerType *ptr;
    char unk_104;
    char pad_105[0x1D];
    unsigned char unk_122;
} SelfType;

typedef struct OutType {
    void *unk_00;
    char unk_04;
} OutType;

extern int data_020c8ba0;
extern unsigned int func_0208150c(int);
extern int func_020036e8(unsigned char *);
extern int func_0202da38(SelfType *a, char *b, char *c, int d, int e, int f, int g, int h, int i);

void func_0201eed8(SelfType *self, OutType *out)
{
    func_0202da38(self, &self->unk_104, (char *) &self->unk_122, 30,
                  func_020036e8((unsigned char *) func_0208150c(self->ptr->value)), data_020c8ba0, 1, 0x13, 2);
    out->unk_00 = &self->unk_104;
    out->unk_04 = self->unk_122;
}
