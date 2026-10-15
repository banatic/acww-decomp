/* func_ov107_0229c378 @ 0x0229c378, 0x4a bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229c378 {
    char pad_00[0xb9];
    unsigned char b9;
    char pad_BA[0x12];
    int cc;
    int d0;
};

extern void func_0204f794(void *out, int a, int b);
extern unsigned short func_ov107_0229d0f0(struct UnkStruct_0229c378 *p, unsigned char byte);
extern int func_ov003_02219b90(void *a, void *b);
extern void func_ov107_0229caa8(struct UnkStruct_0229c378 *p);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov107_0229c378(struct UnkStruct_0229c378 *p)
{
    unsigned short s;
    int arr[3];
    func_0204f794(arr, p->cc, p->d0);
    s = func_ov107_0229d0f0(p, p->b9);
    if (func_ov003_02219b90(arr, &s)) {
        func_ov107_0229caa8(p);
        func_ov002_02208098((void *) (p), 0x14);
    }
}
