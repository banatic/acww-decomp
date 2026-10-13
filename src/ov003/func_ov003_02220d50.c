/* func_ov003_02220d50 @ 0x02220d50, 0x64 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0204f794(int *out, int a, int b);
extern void *func_020961a8(int arg);
extern int func_020644e4(int value);
extern void func_ov003_022213f8(int *data, int a1, int *pair, int *dest, int arg5, int arg6, int arg7, int arg8);
extern int data_ov003_0223cfe4[];

typedef struct {
    int unk_00;
    int unk_04;
} UnkStruct_02220d50;

void func_ov003_02220d50(int a1, int a2, UnkStruct_02220d50 *s)
{
    int val = 0;
    int pair[2];
    int buffer[3];
    int dest[3];
    void *ptr;

    func_0204f794(buffer, s->unk_00, s->unk_04);

    ptr = func_020961a8(4);
    if (ptr) {
        val = (func_020644e4(*(short *) ((char *) ptr + 0x8e)) << 29) >> 16;
    }

    dest[0] = buffer[0];
    dest[1] = buffer[1];
    dest[2] = buffer[2];

    pair[0] = s->unk_00;
    pair[1] = s->unk_04;

    func_ov003_022213f8(data_ov003_0223cfe4, a1, pair, dest, 11, a2, val, 0);
}
