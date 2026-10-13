/* func_02073044 @ 0x02073044, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

/* FAKEMATCH: the empty if keeps the three overlay ids loaded as ov065, ov066, ov067 into r2, r1, r0; the plain condition loads them in the other order */

typedef struct {
    int v;
    unsigned char unk_04;
} UnkStruct_02073044;
extern UnkStruct_02073044 data_021d11c4;
extern char SDK_OVERLAY_ov065_ID;
extern char SDK_OVERLAY_ov066_ID;
extern char SDK_OVERLAY_ov067_ID;
extern void OS_Terminate(void);
void func_02073044(void)
{
    char *ptr;
    int k;
    int a;
    int b;
    int c;
    unsigned int ok;
    if (data_021d11c4.unk_04 != 0) {
        k = -1;
    } else {
        k = data_021d11c4.v;
    }
    a = (int) (&SDK_OVERLAY_ov065_ID);
    ptr = &SDK_OVERLAY_ov066_ID;
    if ((!ok) && (!ok)) {
    }
    c = (int) (&SDK_OVERLAY_ov067_ID);
    b = (int) ptr;
    if (((k == a) || (k == b)) || (k == c)) {
        ok = 1;
    } else {
        ok = 0;
    }
    if (ok == 0) {
        OS_Terminate();
    }
}
