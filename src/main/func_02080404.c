/* func_02080404 @ 0x02080404, 0xb4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021dc7aa[];

extern int func_020951bc(void *);
extern int func_02081edc(void *);
extern int func_02081d28(void *, void *);
extern unsigned short *func_02081d64(void *);
extern int memcmp(const void *, const void *, int);

int func_02080404(void *self, void **out, void *arg2, int arg3)
{
    int count = 0;
    int i;
    if (data_021dc7aa != (unsigned short *) 0 && func_020951bc(arg2)) {
        for (i = 0; i < 8; i++) {
            void *slot = (char *) self + i * 0x80;
            if (func_02081edc(slot) != 0 && func_02081d28(slot, arg2) == 0) {
                switch (arg3) {
                    case 0: {
                        unsigned short *r = func_02081d64(slot);
                        if (r[0] == data_021dc7aa[0] && memcmp(r + 1, (const void *) ((char *) data_021dc7aa + 2), 0xc) == 0) {
                            out[count] = slot;
                            count++;
                        }
                        break;
                    }
                    case 1: {
                        unsigned short *r = func_02081d64(slot);
                        if (r[0] != data_021dc7aa[0] || memcmp(r + 1, (const void *) ((char *) data_021dc7aa + 2), 0xc) != 0) {
                            out[count] = slot;
                            count++;
                        }
                        break;
                    }
                    default:
                        out[count] = slot;
                        count++;
                        break;
                }
            }
        }
    }
    return count;
}
