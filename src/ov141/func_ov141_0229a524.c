/* func_ov141_0229a524 @ 0x0229a524, 0x3c bytes, Thumb, module ov141
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229a524 {
    char pad_00[0x1274];
    int unk_1274;
    char pad_1278[0x813];
    char unk_1A8B;
} UnkStruct_0229a524;

extern void func_ov141_02299f5c(UnkStruct_0229a524 *, int);
extern void func_ov002_02208090(UnkStruct_0229a524 *, int);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void RtcSendPxiCommand(int);

void func_ov141_0229a524(UnkStruct_0229a524 *self)
{
    func_ov141_02299f5c(self, 2);
    self->unk_1274 = 10;
    self->unk_1A8B = 5;
    func_ov002_02208090(self, 3);
    func_ov002_02208098((void *) (self), 5);
    RtcSendPxiCommand(0x27);
}
