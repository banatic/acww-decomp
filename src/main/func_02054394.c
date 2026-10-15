/* func_02054394 @ 0x02054394, 0x9c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_01ffcc10(void *, void *);
extern int func_02054548(void *, int);
extern int func_020549fc(void *, int);
extern void func_02054430(void *, void *);
extern void func_02054944(void *, void *);
extern void func_02054d14(void *, void *);

void func_02054394(void *a0, void *a1)
{
    unsigned int f1b0, f1ac, f14c, f150, combined;
    unsigned char c;
    unsigned int shifted;

    if (func_01ffcc10(a0, a1)) {
        return;
    }

    f1b0 = *(unsigned int *) ((char *) a0 + 0x1b0);
    f1ac = *(unsigned int *) ((char *) a0 + 0x1ac);
    f14c = *(unsigned int *) ((char *) a0 + 0x14c);
    f150 = *(unsigned int *) ((char *) a0 + 0x150);
    combined = f1b0 | (f1ac | (f14c | f150));

    if (combined == 0) {
        func_02054d14(a0, a1);
        return;
    }

    c = ((unsigned char *) (*(void **) a1))[1];
    shifted = 1u << (c & 0x1f);

    if ((combined & shifted) == 0) {
        func_02054d14(a0, a1);
        return;
    }

    if (func_02054548(a0, c)) {
        func_02054430(a0, a1);
        return;
    }
    if (func_020549fc(a0, c)) {
        func_02054944(a0, a1);
        return;
    }
    func_02054d14(a0, a1);
}
