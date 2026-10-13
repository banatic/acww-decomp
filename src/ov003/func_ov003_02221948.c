/* func_ov003_02221948 @ 0x02221948, 0xf0 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_020ccf94;
extern void func_02073d90(unsigned int, unsigned short);
extern void func_020044d0(void *, void *);
extern void func_ov003_022226c8(void *);
extern void func_ov003_02222598(void *);
extern void func_ov003_022223bc(void *);
extern void func_ov003_02222318(void *);
extern void func_ov003_022221cc(void *);
extern void func_ov003_022220f4(void *);
extern void func_ov003_02221fb0(void *);
extern void func_ov003_02221f14(void *);
extern void func_ov003_02221dd0(void *);
extern void func_ov003_02221d64(void *);
extern void func_ov003_02221cb4(void *);
extern void func_ov003_02221ad8(void *);
struct Entry {
    unsigned char pad_00[4];
    unsigned int unk_04;
    unsigned short unk_08;
    unsigned char pad_0A[2];
    unsigned int unk_0C;
    unsigned char pad_10[0x18 - 0x10];
    unsigned int unk_18;
    unsigned int unk_1C;
    unsigned int unk_20;
    unsigned char pad_24[0x4e - 0x24];
    unsigned short unk_4E;
    unsigned char pad_50[0x60 - 0x50];
    unsigned char data[0xa4 - 0x60];
};
void func_ov003_02221948(struct Entry *p)
{
    unsigned short local = 0xfff1;
    unsigned int temp[3];
    unsigned short *plocal;
    unsigned int *ptemp;
    int i;
    func_02073d90(data_020ccf94, local);
    i = 0;
    plocal = &local;
    ;
    for (; i < 20; p++, i++) {
        if (p->unk_04 == 0) {
            continue;
        }
        p->unk_4E++;
        *plocal = p->unk_08;
        switch (p->unk_0C) {
            case 0:

            case 13:
                func_ov003_022226c8(p);
                break;

            case 1:

            case 2:
                func_ov003_02222598(p);
                break;

            case 3:

            case 14:
                func_ov003_022223bc(p);
                break;

            case 4:
                func_ov003_02222318(p);
                break;

            case 5:
                func_ov003_022221cc(p);
                break;

            case 6:
                func_ov003_022220f4(p);
                break;

            case 7:
                func_ov003_02221fb0(p);
                break;

            case 8:
                func_ov003_02221f14(p);
                break;

            case 9:
                func_ov003_02221dd0(p);
                break;

            case 10:
                func_ov003_02221d64(p);
                break;

            case 11:
                func_ov003_02221cb4(p);
                break;

            case 12:
                func_ov003_02221ad8(p);
                break;
        }

        temp[0] = p->unk_18;
        temp[1] = p->unk_1C;
        temp[2] = p->unk_20;
        func_020044d0(p->data, temp);
    }
}
