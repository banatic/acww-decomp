/* func_02019098 @ 0x02019098, 0xac bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern volatile unsigned short data_020c80f8;
extern unsigned int data_020c81c4[];
extern unsigned short data_020c81a8[];
extern int func_0201afec(void *);
extern void func_02016764(void *, void *, unsigned int, unsigned short, int, int, int, int);
extern void func_02012444(int, unsigned short, int);
extern void func_0200442c(void *, unsigned short, int, int);

void func_02019098(void *self, void *data)
{
    if (*(short *) ((char *) data + 0x8e) != func_0201afec((char *) data + 0x350)) {
        return;
    }
    if (*(int *) ((char *) self + 0xb0) >= 5) {
        *(int *) ((char *) self + 0xb0) = 0;
    }
    {
        unsigned short first = data_020c80f8;
        func_02016764((char *) data + 0x334, data, data_020c81c4[*(int *) ((char *) self + 0xb0)], data_020c80f8, 1, 0x1000, 0,
                      0);
        {
            int fld = *(int *) ((char *) data + 0x628);
            if (fld != 0) {
                func_02012444(fld, first, 0);
            }
        }
        func_0200442c((char *) data + 0x514, data_020c81a8[*(int *) ((char *) self + 0xb0)], 0x7f, 0);
        *(char *) ((char *) self + 0x98) = 1;
    }
}
