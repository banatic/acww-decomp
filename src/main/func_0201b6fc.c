/* func_0201b6fc @ 0x0201b6fc, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203f7d0(void *);

int func_0201b6fc(void *r0, void *r1)
{
    int r3;
    int r2;
    int r0_2;

    r3 = *(int *) ((char *) r0 + 0x46c);
    if (r3 == 0) {
        r2 = *(int *) ((char *) r0 + 0x470);
        if (r2 == 0) {
            r2 = *(int *) ((char *) r0 + 0x474);
            if (r2 == 0) {
                return 0;
            }
        }
    }
    *(int *) r1 = r3;
    r2 = *(int *) ((char *) r0 + 0x470);
    *(int *) ((char *) r1 + 4) = r2;
    r0_2 = *(int *) ((char *) r0 + 0x474);
    *(int *) ((char *) r1 + 8) = r0_2;
    func_0203f7d0(r1);
    return 1;
}
