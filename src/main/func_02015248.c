/* func_02015248 @ 0x02015248, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

func_02015248(unsigned char *r5)
{
    unsigned char *r1;
    unsigned char *r0;
    int r4 = 0;

    r1 = (unsigned char *) (*(unsigned int *) (r5 + 0x4c));
    if (r1 != 0) {
        r0 = (unsigned char *) (*(unsigned int *) (r5 + 0x40));
        if (r0 != 0) {
            r0 = r1 + 0x564;
            if (func_02019e00(r0) == 0xe) {
                r1 = (unsigned char *) (*(unsigned int *) (r5 + 0x4c));
                r0 = r1 + 0x564;
                if (func_02019de8(r0) != 0) {
                    r0 = (unsigned char *) (*(unsigned int *) (r5 + 0x40));
                    func_02068434(r0);
                    r0 = r5 + 0x94;
                    if (*(unsigned char *) r0 != 4) {
                        func_02016004(r5);
                    }
                    *(unsigned char *) (r5 + 0xac) = 2;
                    r4 = 1;
                }
            }
        }
    }
    return r4;
}
