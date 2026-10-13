/* func_020865d8 @ 0x020865d8, 0xe0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209df64(void *);
extern int func_0203fdc4(int);
extern int func_0209dcdc(void *, void *);
extern void *func_02098844(void *, int);
extern int func_02099a28(void);
extern void func_02099670(void *);
extern void func_02088ac0(void);
extern void func_02088aa0(void);
extern void func_02098fd0(void *, int);
extern void func_0209f100(void *, int);
extern void func_0208683c(void *);

typedef struct {
    unsigned char pad_00[0x44];
    unsigned char unk_44;
    unsigned char pad_45;
    unsigned char unk_46;
} UnkStruct_020865d8;

extern unsigned char data_021dc7a8[];
extern unsigned char data_021dc7bc[];

void func_020865d8(UnkStruct_020865d8 *obj, int selector)
{
    unsigned char tmp[4];
    int val;
    int ret;
    int i;

    func_0209df64(tmp);

    val = 0;
    switch (selector) {
        case 0:
            val = func_0203fdc4(0xe);
            break;
        case 1:
            val = func_0203fdc4(0x11);
            break;
        case 2:
            val = func_0203fdc4(0x10);
            break;
    }

    ret = func_0209dcdc(tmp, &obj->unk_44);

    if (tmp[2] != obj->unk_46) {
        goto FAIL;
    }
    if (val == -1) {
        goto FAIL;
    }
    if (ret > 7) {
        goto FAIL;
    }
    if (ret < 0) {
        goto FAIL;
    }
    if ((tmp[0] - val) <= obj->unk_44) {
        return;
    }

FAIL:
    switch (selector) {
        case 1:
            func_0209f100((void *) data_021dc7a8, 0x11);
            break;
        case 0:
        case 2:
            i = 0;
            do {
                void *p = func_02098844((void *) data_021dc7bc, i);
                if (p != 0 && func_02099a28() != 0) {
                    if (selector == 2) {
                        func_02099670(p);
                        func_02088ac0();
                        func_02098fd0(p, 0xf);
                    } else {
                        func_02099670(p);
                        func_02088aa0();
                    }
                }
                i++;
            } while (i < 4);
            break;
        default:
            break;
    }

    func_0208683c(obj);
}
