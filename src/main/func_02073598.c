/* func_02073598 @ 0x02073598, 0xf6 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02073598 {
    unsigned char pad_00[0x64];
    unsigned int unk_64;
};

extern int func_02073dd4(struct UnkStruct_02073598 *self, unsigned int field);
extern unsigned int func_02073690(struct UnkStruct_02073598 *self);
extern char *func_020736b4(struct UnkStruct_02073598 *self);
extern void MI_CpuCopy8(void *dst, const void *src, unsigned int size);
extern void func_02077a34(char *dst, const char *a, const char *b);
extern int func_020a71ec(unsigned char c);
extern unsigned int func_020734a4(struct UnkStruct_02073598 *self);
extern char *func_020734c8(struct UnkStruct_02073598 *self);
extern unsigned int func_02077868(const char *str);
extern void func_020734ac(struct UnkStruct_02073598 *self, unsigned int total);
extern void func_02073820(struct UnkStruct_02073598 *self);
extern void func_020737f0(struct UnkStruct_02073598 *self, char *ptr, unsigned int len);
extern void func_02073770(struct UnkStruct_02073598 *self, unsigned char a, unsigned char b);
extern void func_020736a0(struct UnkStruct_02073598 *self);

void func_02073598(struct UnkStruct_02073598 *self)
{
    unsigned int count;
    char *offset;
    unsigned int len;
    unsigned char data[17];
    unsigned int total;
    char *ptr;
    unsigned int idx;
    unsigned int field;
    int res;
    unsigned char b;

    field = self->unk_64;
    if (func_02073dd4(self, field) == 0) {
        return;
    }
    count = func_02073690(self);
    if (count == 0) {
        return;
    }
    ptr = func_020736b4(self);

    MI_CpuCopy8(ptr, (char *) &data[2], 5);
    func_02077a34((char *) &data[6], (const char *) &data[0], (const char *) &data[1]);

    b = data[0];
    res = func_020a71ec(b);
    if (res >= 4) {
        return;
    }
    if (res == field) {
        total = func_020734a4(self);
        offset = func_020734c8(self) + total;
        idx = 0;
        while (idx < count) {
            MI_CpuCopy8(ptr, (char *) &data[7], 5);
            len = func_02077868((const char *) &data[7]);
            MI_CpuCopy8(ptr, offset, len + 5);
            offset += len + 5;
            total += len + 5;
            ptr += len + 5;
            idx += len + 5;
        }
        func_020734ac(self, total);
    } else {
        total = 0;
        while (total < count) {
            MI_CpuCopy8(ptr, (char *) &data[12], 5);
            ptr += 5;
            total += 5;
            len = func_02077868((const char *) &data[12]);
            func_02073820(self);
            func_020737f0(self, ptr, len);
            func_02073770(self, data[14], data[15]);
            ptr += len;
            total += len;
        }
    }
    func_020736a0(self);
}
