/* func_ov108_0229d300 @ 0x0229d300, 0x4c bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229d300 {
    char pad_00[0x2b0];
    unsigned char unk_2B0;
    char pad_2B1[2];
    unsigned char unk_2B3;
    char pad_2B4[0x2498 - 0x2b4];
    char sub;
};

extern int func_ov002_02209f64(char *arg);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov108_0229caec(struct UnkStruct_0229d300 *arg, unsigned char byte);
extern void func_ov108_0229db9c(struct UnkStruct_0229d300 *arg);
extern void func_ov108_0229c940(struct UnkStruct_0229d300 *arg);

void func_ov108_0229d300(struct UnkStruct_0229d300 *s)
{
    if (func_ov002_02209f64(&s->sub) == 0) {
        func_ov002_02208098((void *) (s), s->unk_2B3);
        if (s->unk_2B3 == 6) {
            func_ov108_0229caec(s, s->unk_2B0);
        }
        func_ov108_0229db9c(s);
    }
    func_ov108_0229c940(s);
}
