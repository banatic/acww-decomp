/* func_ov094_0229b220 @ 0x0229b220, 0x54 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov094_0229b1e8(void *, unsigned char *);
extern void func_ov094_0229b134(void *, int);
extern void func_ov094_0229b154(void *, int);

typedef struct {
    unsigned int pad_00;
    unsigned char *unk_04;
    unsigned int pad_08;
} UnkStruct_0229b220;

void func_ov094_0229b220(UnkStruct_0229b220 *self, unsigned char *val, int idx, int count)
{
    int cond = 0;
    int i;
    unsigned char *p;

    self->unk_04 = val;
    p = self->unk_04;
    for (i = 0; i < count; i++) {
        if (func_ov094_0229b1e8(self, p) != ~cond) {
            func_ov094_0229b154((void *) ((char *) self + 8), idx);
        } else {
            func_ov094_0229b134((void *) ((char *) self + 8), idx);
        }
        p += 0x100;
        idx++;
    }
}
