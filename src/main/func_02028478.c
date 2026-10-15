/* func_02028478 @ 0x02028478, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02028478 {
    unsigned char pad_00[0x158];
    unsigned char unk_158;
    unsigned char unk_159;
} UnkStruct_02028478;

extern int func_0202d9c4(UnkStruct_02028478 *);
extern void *func_0209bc20(void *record);
extern void func_0209e474(int);
extern void func_0209e234(int, unsigned char);
extern void func_0209bb74(int, unsigned char);

void func_02028478(UnkStruct_02028478 *arg)
{
    if (func_0202d9c4(arg) != 0) {
        int v;
        v = (int) func_0209bc20((void *) func_0202d9c4(arg));
        func_0209e474(v);
        func_0209e234(v, arg->unk_158);
        func_0209bb74(func_0202d9c4(arg), arg->unk_159);
    }
}
