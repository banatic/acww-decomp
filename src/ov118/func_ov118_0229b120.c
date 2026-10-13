/* func_ov118_0229b120 @ 0x0229b120, 0x15c bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char x;
    unsigned char y;
    unsigned char t;
} UnkStruct_0229b120;

typedef struct {
    unsigned char pad_00[0x47a4];
    UnkStruct_0229b120 a[3];
    UnkStruct_0229b120 b[14];
} UnkStruct_0229b120_2;

typedef struct {
    short unk_00;
    short unk_02;
} UnkStruct_0229b120_3;

extern UnkStruct_0229b120_3 *func_ov117_0229a280(void *h, int i);
extern int func_ov117_0229a26c(void *h, int i);
extern const unsigned char data_ov118_0229caa0[];

void func_ov118_0229b120(UnkStruct_0229b120_2 *d, void *h)
{
    int i;
    int j;
    unsigned int k;
    int m;
    UnkStruct_0229b120_3 *p;

    i = 0;
    for (j = 0; j < 3; j++) {
        p = func_ov117_0229a280(h, i);
        if (p != 0) {
            switch (func_ov117_0229a26c(h, i)) {
                case 0:
                    d->a[j].t = 8;
                    break;
                case 1:
                    d->a[j].t = 7;
                    break;
                case 2:
                    d->a[j].t = 9;
                    break;
                case 3:
                    d->a[j].t = 0x89;
                    break;
                default:
                    d->a[j].t = 0xc;
                    break;
            }
            d->a[j].x = p->unk_00 - 8;
            d->a[j].y = p->unk_02 + 0x10;
        } else {
            d->a[j].t = 0xc;
        }
        i++;
    }
    k = 3;
    for (m = 0; m < 14; m++) {
        p = func_ov117_0229a280(h, k);
        if (p != 0) {
            if (k >= 3 && k <= 0xa) {
                d->b[m].t = 0;
            } else if (k == 0xb) {
                d->b[m].t = 1;
            } else {
                d->b[m].t = *(data_ov118_0229caa0 + k - 0xc);
            }
            d->b[m].x = p->unk_00 - 8;
            d->b[m].y = p->unk_02 + 0x10;
        } else {
            d->b[m].t = 0xc;
        }
        k++;
    }
}
