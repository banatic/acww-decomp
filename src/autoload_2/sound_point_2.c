/* sound_point_2: 3 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020f4f80 @ 0x020f4f80, 0x38 bytes, ARM
 * func_020f4f64 @ 0x020f4f64, 0x1c bytes, ARM
 * func_020f4f44 @ 0x020f4f44, 0x20 bytes, ARM
 */

typedef struct {
    char pad_00[0xc];
    char unk_0C;
} UnkStruct_020f4f64;

extern int data_021fd234;
extern unsigned int func_020f4d00(int, void *);
extern int func_020eed18(void *, int);
extern void NNS_SndHandleReleaseSeq(void *);
extern void NNS_FndInitList(char *self, int flag);
extern void func_020eed48(char *res);

void func_020f4f80(char *arg)
{
    func_020f4d00(data_021fd234, arg);
    func_020eed18(arg + 8, 5);
    NNS_SndHandleReleaseSeq(arg + 8);
}

UnkStruct_020f4f64 *func_020f4f64(UnkStruct_020f4f64 *self)
{
    NNS_SndHandleReleaseSeq(&self->unk_0C);
    return self;
}

void func_020f4f44(char *self)
{
    NNS_FndInitList(self, 0);
    func_020eed48(self + 0xC);
}
