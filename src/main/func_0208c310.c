/* func_0208c310 @ 0x0208c310, 0x42 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0208c310 {
    char data[20];
} UnkStruct_0208c310;
typedef struct UnkStruct_0208c310_2 {
    char pad_00[12];
    UnkStruct_0208c310 arr[9];
} UnkStruct_0208c310_2;
extern void func_0208a0c8(UnkStruct_0208c310 *);
extern int func_0208a160(UnkStruct_0208c310 *);
extern void func_0208c308(UnkStruct_0208c310_2 *);
void func_0208c310(UnkStruct_0208c310_2 *s)
{
    int flag = 1;
    int i = 0;
    int zero = i;
    for (; i < 9; i++) {
        UnkStruct_0208c310 *ptr = &s->arr[i];
        func_0208a0c8(ptr);
        if (func_0208a160(ptr) == 0) {
            flag = zero;
        }
    }
    if (flag) {
        func_0208c308(s);
    }
}
