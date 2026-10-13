/* func_ov142_0229a644 @ 0x0229a644, 0x94 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov142_0229c5e4;
extern void *data_ov142_0229c5ec[];

void *func_ov142_0229a644(void *base, int idx)
{
    int type;
    if ((data_ov142_0229c5e4 & 1) == 0) {
        data_ov142_0229c5ec[0] = (void *) ((char *) base + 0x9d8);
        data_ov142_0229c5ec[1] = (void *) ((char *) base + 0x11d8);
        data_ov142_0229c5ec[2] = (void *) ((char *) base + 0x1260);
        data_ov142_0229c5ec[3] = (void *) ((char *) base + 0x12e8);
        data_ov142_0229c5ec[4] = (void *) ((char *) base + 0x14e8);
        data_ov142_0229c5ec[5] = (void *) ((char *) base + 0x1528);
        data_ov142_0229c5ec[6] = (void *) ((char *) base + 0x1668);
        data_ov142_0229c5ec[7] = (void *) ((char *) base + 0x16e8);
        data_ov142_0229c5ec[8] = (void *) ((char *) base + 0x17e6);
        data_ov142_0229c5e4 |= 1;
    }
    if (idx < 0) {
        idx = 0;
    }
    type = *(unsigned char *) ((char *) base + 0xbc);
    return (char *) data_ov142_0229c5ec[type] + 2 * idx;
}
