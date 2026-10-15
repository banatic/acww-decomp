/* func_02081e14 @ 0x02081e14, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct UnkStruct_02081e14;
extern const char data_021dc7aa[];
extern const char data_021f3b68[];
extern int func_020951bc(const char *str);
extern void func_0209525c(struct UnkStruct_02081e14 *self, const char *str);
extern void func_0209e474(void *buf);
extern int func_02081d88(struct UnkStruct_02081e14 *self, char *buf);
extern int func_02081d68(struct UnkStruct_02081e14 *self);
extern void *func_02081d64(struct UnkStruct_02081e14 *self);
extern void func_020642d0(void *a, const char *b);
extern void *func_02081e10(struct UnkStruct_02081e14 *self);
extern void MI_CpuCopy8(void *dst, const void *src, unsigned int n);
extern void func_02081a90(struct UnkStruct_02081e14 *self, const char *str);

void func_02081e14(struct UnkStruct_02081e14 *self, const char *str1, const char *str2, char *buf)
{
    int local[3];

    local[0] = 0;
    local[1] = 0;

    if (str1 != 0) {
        if (func_020951bc(str1)) {
            func_0209525c(self, str1);
        }
    }
    if (str2 == 0) {
        str2 = data_021dc7aa;
    }
    if (buf == 0) {
        func_0209e474(local);
        buf = (char *) local;
    }
    if (func_02081d88(self, buf)) {
        func_02081d68(self);
    }
    func_020642d0(func_02081d64(self), str2);
    MI_CpuCopy8(buf, func_02081e10(self), 8);
    func_02081a90(self, data_021f3b68);
}
