/* func_020a9cac @ 0x020a9cac, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020a9cac {
    unsigned int arr[6];
    unsigned int count;
};

void func_020a9cac(struct UnkStruct_020a9cac *s, unsigned int *src)
{
    unsigned int idx;
    idx = s->count;
    if (idx >= 6) {
        return;
    }
    s->count = idx + 1;
    s->arr[idx] = *src;
}
