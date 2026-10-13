/* func_ov116_0229de60 @ 0x0229de60, 0x52 bytes, Thumb, module ov116
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229de60 UnkStruct_0229de60;
struct UnkStruct_0229de60 {
    unsigned char pad_00[0x94];
    char unk_94;
    unsigned char pad_95[0x63];
    char unk_F8;
};

extern int func_ov114_0229c60c(const void *);
extern int func_ov114_0229c5f4(const void *);
extern void func_ov002_0220a254(const void *);
extern void func_ov002_0220a2b4(const void *);
extern int func_ov116_0229dedc(const UnkStruct_0229de60 *);
extern int func_ov116_0229ded0(const UnkStruct_0229de60 *);
extern void func_ov116_0229de2c(const UnkStruct_0229de60 *, int, int);

void func_ov116_0229de60(UnkStruct_0229de60 *obj)
{
    int t1, t2;

    if (func_ov114_0229c60c(&obj->unk_F8) != -1 || func_ov114_0229c5f4(&obj->unk_F8) != 0) {
        func_ov002_0220a254(&obj->unk_94);
    } else {
        func_ov002_0220a2b4(&obj->unk_94);
    }

    t1 = func_ov116_0229dedc(obj);
    t2 = func_ov116_0229ded0(obj);
    func_ov116_0229de2c(obj, t1, t2);
}
