/* func_020ab130 @ 0x020ab130, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8fb8(void *ptr);

struct UnkStruct_020ab130 {
    int pad_00[2];
    void *data[5];
};

void func_020ab130(struct UnkStruct_020ab130 *s)
{
    unsigned int i;
    for (i = 0; i < 5; i++) {
        if (s->data[i] != 0) {
            func_020a8fb8(s->data[i]);
            s->data[i] = 0;
        }
    }
}
