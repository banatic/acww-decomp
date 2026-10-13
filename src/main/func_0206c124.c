/* func_0206c124 @ 0x0206c124, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8fb8(int value);

struct UnkStruct_0206c124 {
    char pad_00[0x420];
    int arr[3];
};

void func_0206c124(struct UnkStruct_0206c124 *s)
{
    unsigned int i;
    for (i = 0; i < 3; i++) {
        if (s->arr[i] != 0) {
            func_020a8fb8(s->arr[i]);
            s->arr[i] = 0;
        }
    }
}
