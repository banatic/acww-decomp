/* func_ov002_0220866c @ 0x0220866c, 0x62 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220880c(void *a);
extern void func_02001b6c(int);
extern void func_02001d00(int);
extern void func_02001ba4(int);
extern void func_02001d1c(int);
extern void func_ov002_02208704(void *a, int b);
extern void func_ov002_022086d0(void *a, int b);

typedef struct {
    char pad_00[0x0c];
    int unk_0C;
    char pad_10[0x08];
    unsigned char unk_18;
} UnkStruct_0220866c;

int func_ov002_0220866c(UnkStruct_0220866c *self, int kind)
{
    if (func_ov002_0220880c(self)) {
        self->unk_0C = 0;
        switch (kind) {
            case 0:
                func_02001b6c(1);
                func_02001d00(0x1f);
                break;
            case 1:
                func_02001ba4(1);
                func_02001d1c(0x1f);
                break;
            default:
                break;
        }
        return 1;
    } else {
        switch (self->unk_18) {
            case 0:
            case 1:
                func_ov002_02208704(self, kind);
                break;
            default:
                func_ov002_022086d0(self, kind);
                break;
        }
        return 0;
    }
}
