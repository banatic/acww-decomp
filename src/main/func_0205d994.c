/* func_0205d994 @ 0x0205d994, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020e9b9c(void *ptr);
extern void *data_021c9aec;

typedef struct {
    int arr[9];
    unsigned short h1[18];
    unsigned short h2[18];
} UnkStruct_0205d994;

void func_0205d994(UnkStruct_0205d994 *s)
{
    int i;
    int j;
    int zero = 0;
    unsigned short *p;
    unsigned short *q;

    for (i = 0; i < 9; i++) {
        s->arr[i] = 0;
        for (j = 0; j < 2; j++) {
            q = (unsigned short *) ((char *) s + i * 2 + j * 18);
            p = q;
            p += 0x48 / 2;
            *p = 0x16f;
            q[0x24 / 2] = zero;
        }
    }

    if (data_021c9aec) {
        func_020e9b9c(data_021c9aec);
    }
}
