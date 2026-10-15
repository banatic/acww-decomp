/* func_020a1b68 @ 0x020a1b68, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_021dc7a8;
extern int data_020d1c20[];
extern int data_020d1bf0[];
extern char data_021c8188;

struct UnkStruct_020a1b68 {
    char pad_00[0xb0];
    int unk_B0;
};
extern struct UnkStruct_020a1b68 *data_021f3c3c;

extern int func_020a1368(void);
extern int func_02050a10(void *, int, int, int);

int func_020a1b68(unsigned int a, int b)
{
    int arr[3];
    int v, w, x;
    struct UnkStruct_020a1b68 *p;

    arr[0] = (int) &data_021dc7a8;
    arr[1] = (int) &data_021dc7a8;
    arr[2] = func_020a1368();

    v = arr[a];
    x = data_020d1c20[a];
    w = data_020d1bf0[a];

    if (b != 0 && a <= 1) {
        p = data_021f3c3c;
        if (p == 0) {
            return 1;
        }
        v = p->unk_B0;
    }

    return func_02050a10(&data_021c8188, v, w, x) != 0;
}
