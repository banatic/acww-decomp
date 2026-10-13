/* func_ov066_0226b1d0 @ 0x0226b1d0, 0xac bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

extern int func_ov066_022699cc(void);
extern void func_ov066_0226b27c(int arg0, unsigned char *arg1);

typedef struct {
    unsigned char pad[0xb];
    unsigned char count;
} UnkStruct_0226b1d0;

typedef struct {
    unsigned char unk_00;
    unsigned char pad[2];
    signed char slot3;
} UnkStruct_0226b1d0_2;

typedef struct {
    unsigned short unk_00;
    unsigned short flags;
} UnkStruct_0226b1d0_3;

extern UnkStruct_0226b1d0 *data_ov066_0226bdec;
extern UnkStruct_0226b1d0_2 *data_ov066_0226be08;

void func_ov066_0226b1d0(UnkStruct_0226b1d0_3 *self)
{
    unsigned short i;
    unsigned char *p = (unsigned char *) self + 4;

    for (i = 0; i < data_ov066_0226bdec->count; i++) {
        if (self->flags & (1 << i)) {
            if (i == func_ov066_022699cc()) {
                data_ov066_0226be08->slot3--;
            }
            func_ov066_0226b27c(i, p);
            p += data_ov066_0226be08->unk_00 & ~1;
        }
    }
}
