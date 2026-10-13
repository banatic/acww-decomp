/* func_0202dac0 @ 0x0202dac0, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct Pair {
    int a;
    int b;
} Pair;
extern Pair data_0213dd98;
typedef struct UnkStruct_0202dac0 {
    char pad_00[0xb0];
    Pair arr[3];
} UnkStruct_0202dac0;

void func_0202dac0(UnkStruct_0202dac0 *p)
{
    Pair tmp;
    p->arr[0] = data_0213dd98;
    tmp = data_0213dd98;
    p->arr[1] = tmp;
    p->arr[2] = tmp;
}
