/* func_0206c2c4 @ 0x0206c2c4, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x414];
    int arr[3];
} UnkStruct_0206c2c4;

void func_0206c2c4(UnkStruct_0206c2c4 *s, int v)
{
    unsigned int i = 0;
    goto test;
loop:
    s->arr[i] = v;
    i++;
test:
    if (i < 3) {
        goto loop;
    }
}
