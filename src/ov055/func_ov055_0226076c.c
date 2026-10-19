/* func_ov055_0226076c @ 0x0226076c, 0x34 bytes, Thumb, module ov055
 * mwccarm 1.2/base -O4,s
 */

#define g_global (*(unsigned short *) 0x027fffa8)
void func_0200467c(int);
void func_02068434(void *);
void func_ov055_02260870(void *, int);

struct SelfType {
    char pad_00[0x40];
    void *unk_40;
};

void func_ov055_0226076c(struct SelfType *self)
{
    if ((g_global & 0x8000) >> 15) {
        return;
    }
    func_0200467c(0x69);
    func_02068434(self->unk_40);
    func_ov055_02260870(self, 0);
}
