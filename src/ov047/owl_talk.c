/* owl_talk: 4 functions, module ov047
 * mwccarm 1.2/base -O4,s
 * func_ov047_022606f0 @ 0x022606f0, 0x32 bytes, Thumb
 * func_ov047_0226069c @ 0x0226069c, 0x54 bytes, Thumb
 * func_ov047_02260688 @ 0x02260688, 0x14 bytes, Thumb
 * func_ov047_0226063c @ 0x0226063c, 0x4c bytes, Thumb
 */

extern int func_020984e8(void);
extern int func_02099020(int, int);
extern int func_0202e9fc(void);
extern int func_02073d90(int);
extern short *func_0209d358(int, int);
extern int data_020ccf94;
extern unsigned short func_ov047_02261ae8(void *unused0, int unused1);
extern void func_020157d4(void *obj, unsigned int address, unsigned char state, unsigned char flags);
extern int func_02015828(void *, int);
extern void func_ov047_02261f84(void *, int);
extern int func_0209f150(void *, int);
extern int data_021dc7a8;

void func_ov047_022606f0(void *arg0, int arg1)
{
    if (arg1 == 0) {
        if (func_02099020(func_020984e8(), 0x35) == 0) {
            *(int *) ((char *) arg0 + 0xd0) = 0x4b;
        } else {
            *(int *) ((char *) arg0 + 0xd0) = 0x19;
        }
    } else {
        *(int *) ((char *) arg0 + 0xd0) = 0x15;
    }
}

void func_ov047_0226069c(void *p, int r1)
{
    if (r1 != 0) {
        goto L24;
    }
    if (func_0202e9fc() == 0) {
        goto L40;
    }
    if (func_02073d90(data_020ccf94) != 0) {
        goto L41;
    }
    if (*(short *) func_0209d358(0, 0x4A) == 0) {
        goto L14;
    }

L41:
    *(int *) ((char *) p + 0xD0) = 0x41;
    goto end;
L14:
    *(int *) ((char *) p + 0xD0) = 0x14;
    goto end;
L40:
    *(int *) ((char *) p + 0xD0) = 0x40;
    goto end;
L24:
    *(int *) ((char *) p + 0xD0) = 0x24;
end:;
}

void func_ov047_02260688(void *r0, int r1)
{
    if (r1 == 0) {
        *(int *) ((char *) r0 + 0xd0) = 0x14;
    } else {
        *(int *) ((char *) r0 + 0xd0) = 0x28;
    }
}

void func_ov047_0226063c(void *obj, int flag)
{
    if (flag == 0) {
        func_020157d4(obj, (unsigned int) func_ov047_02261ae8, 0xd, 0);
        func_02015828(obj, 0);
        func_ov047_02261f84(obj, 2);
    } else {
        if (func_0209f150(&data_021dc7a8, 0xc) != 0) {
            *((int *) ((char *) obj + 0xd0)) = 0xea;
        } else {
            *((int *) ((char *) obj + 0xd0)) = 0xe9;
        }
    }
}
