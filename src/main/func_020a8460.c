/* func_020a8460 @ 0x020a8460, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8658(void *input, unsigned char *b0, unsigned char *b1, unsigned char *b2, unsigned char *b3,
                          unsigned char *b4);
extern int func_020a8a34(void *item, int offset);

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
} Input;

typedef struct {
    int unk_00;
    int unk_04;
} UnkStruct_020a8460;

int func_020a8460(Input *input, unsigned char *out0, UnkStruct_020a8460 *pt0, unsigned char *out1, UnkStruct_020a8460 *pt1,
                  unsigned char *out2, UnkStruct_020a8460 *pt2, unsigned char *out3, UnkStruct_020a8460 *pt3,
                  unsigned char *out4, UnkStruct_020a8460 *pt4)
{
    unsigned char buf[9];
    UnkStruct_020a8460 *pts[5];
    int offset;
    int i;
    int sum;
    int d;

    func_020a8658(input, buf, buf + 1, buf + 2, buf + 3, buf + 4);

    *out0 = buf[0];
    *out1 = buf[1];
    *out2 = buf[2];
    *out3 = buf[3];
    *out4 = buf[4];

    pts[0] = pt0;
    pts[1] = pt1;
    pts[2] = pt2;
    pts[3] = pt3;
    pts[4] = pt4;

    offset = input->unk_0C + input->unk_08 + 2;
    sum = 2;
    i = 0;

    do {
        func_020a8a34(pts[i], offset);
        d = pts[i]->unk_04 + 2;
        sum += d;
        offset += d;
        i++;
    } while (i < 5);

    return sum;
}
