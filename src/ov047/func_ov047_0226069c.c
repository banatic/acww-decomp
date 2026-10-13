/* func_ov047_0226069c @ 0x0226069c, 0x54 bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202e9fc(void *);
extern int func_02073d90(int);
extern short *func_0209d358(int, int);
extern int data_020ccf94;

void func_ov047_0226069c(void *p, int r1)
{
    if (r1 != 0) {
        goto L24;
    }
    if (func_0202e9fc(p) == 0) {
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
