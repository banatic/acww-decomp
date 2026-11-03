/* item_footprint: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02052e3c @ 0x02052e3c, 0x34 bytes, Thumb
 * func_02052e38 @ 0x02052e38, 0x2 bytes, Thumb
 * func_02052e20 @ 0x02052e20, 0x18 bytes, Thumb
 * func_02052dc0 @ 0x02052dc0, 0x60 bytes, Thumb
 */

typedef struct {
    int unk_00;
    int unk_04;
} UnkStruct_02052dc0;

extern int func_0204bc64(int);
extern int func_02053be0(int);
extern int func_0204bc7c(int);
extern unsigned char *data_020dcfe0[];
extern unsigned int data_021c8744;
extern unsigned short data_021c8748[2];

int *func_02052e3c(int *out, int in)
{
    int temp;
    *out = -1;
    temp = func_0204bc64(in);
    if (temp != -1) {
        *out = func_02053be0(temp);
        *(out + 1) = func_0204bc7c(in);
    }
    return out;
}

void func_02052e38(void *object) {}

unsigned char func_02052e20(int *p)
{
    int v = *p;
    if (v < 3) {
        return data_020dcfe0[v][0x10];
    } else {
        return 0;
    }
}

void *func_02052dc0(UnkStruct_02052dc0 *self, unsigned int param1)
{
    if (self->unk_00 < 3 && param1 < (unsigned int) func_02052e20((int *) self)) {
        return &((void **) (((void ** *) data_020dcfe0)[self->unk_00][self->unk_04]))[param1 & 3];
    }
    if ((data_021c8744 & 1) == 0) {
        data_021c8748[0] = 0;
        data_021c8748[1] = 0;
        data_021c8744 |= 1;
    }
    return data_021c8748;
}
