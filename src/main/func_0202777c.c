/* func_0202777c @ 0x0202777c, 0x88 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209b4d4(int);
extern void func_0209bb90(int, int);
extern void func_0208150c(int);
extern int func_020036e8(void);
extern void func_0202da38(void *, void *, void *, int, int, int, int, int, int);
extern struct {
    int field0;
    unsigned char field4;
} data_020c8e28;
typedef struct Pair {
    int field0;
    int field4;
} Pair;
extern Pair data_020d9080;
typedef struct UnkStruct_0202777c {
    char pad_00[0xc8];
    Pair unk_C8;
    char pad_D0[0x100 - 0xd0];
    int *unk_100;
    char unk_104;
    char pad_105[0x122 - 0x105];
    unsigned char unk_122;
    char pad_123[0x160 - 0x123];
    int unk_160;
} UnkStruct_0202777c;
typedef struct UnkStruct_0202777c_2 {
    void *field0;
    unsigned char field4;
} UnkStruct_0202777c_2;
void func_0202777c(UnkStruct_0202777c *self, UnkStruct_0202777c_2 *out)
{
    func_0209bb90(func_0209b4d4(self->unk_160), 1);
    func_0208150c(*((int *) (((char *) self->unk_100) + 0x830)));
    func_0202da38(self, ((char *) self) + 0x104, ((char *) self) + 0x122, 0x1e, func_020036e8(), data_020c8e28.field0,
                  data_020c8e28.field4, 0, 0);
    out->field0 = ((char *) self) + 0x104;
    out->field4 = self->unk_122;
    self->unk_C8 = data_020d9080;
}
