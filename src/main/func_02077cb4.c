/* func_02077cb4 @ 0x02077cb4, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char data[0x24];
} UnkStruct_02077cb4;

extern void *func_02077d00(void *entries);
extern int func_02077c3c(UnkStruct_02077cb4 *p);
extern int func_02077e50(void *friend_data);
extern void *func_02077c64(UnkStruct_02077cb4 *dst, UnkStruct_02077cb4 *src);
extern void func_02077c40(UnkStruct_02077cb4 *p);

void func_02077cb4(void *entries)
{
    int i;
    int k;
    UnkStruct_02077cb4 *base;

    base = func_02077d00(entries);

    for (i = k = 0; i < 32; i++) {
        UnkStruct_02077cb4 *cur = base + i;

        if (func_02077e50((void *) func_02077c3c(cur)) != 0) {
            if (i != k) {
                func_02077c64(base + k, cur);
                func_02077c40(cur);
            }
            k++;
        }
    }
}
