/* func_02000e8c @ 0x02000e8c, 0x1b0 bytes, ARM, module main
 * mwccarm 1.2/base -O4,s
 */

// The SDK option record is 12 bytes with a three-bit language field.
struct UserSettingsOption {
    unsigned short language : 3;
    unsigned short agbLcd : 1;
    unsigned short detectCardRemoval : 1;
    unsigned short detectCartridgeRemoval : 1;
    unsigned short autoBoot : 1;
    unsigned short reserved : 4;
    unsigned short favoriteColorSet : 1;
    unsigned short touchCalibrated : 1;
    unsigned short languageSet : 1;
    unsigned short rtcSet : 1;
    unsigned short nicknameSet : 1;
    unsigned char timezone;
    unsigned char rtcClockAdjust;
    long long rtcOffset;
};
struct UserSettingsPage {
    unsigned char standardSettings[0x64];
    struct UserSettingsOption option;
    unsigned short saveCount;
    unsigned short crc16;
    unsigned char extensionVersion;
    unsigned char extendedLanguage;
    unsigned short validLanguageBitmap;
    unsigned char reserved[0x86];
    unsigned short extendedCrc16;
};

extern int func_02001074(void);
extern unsigned short func_0200103c(void);
extern unsigned short GetCRC16(unsigned short start, const void *p, unsigned long len);

int func_02000e8c(struct UserSettingsPage *base)
{
    unsigned short i;
    int valid;
    unsigned short mask;
    int m40;
    unsigned char t;
    unsigned int cv;

    valid = 0;

    if (func_02001074() != 0) {
        mask = func_0200103c();
        m40 = mask & 0x40;
        for (i = 0; i < 2; i = (unsigned short) (i + 1)) {
            cv = GetCRC16(0xffff, &base[i], 0x70);
            if (cv != base[i].crc16) {
                continue;
            }
            if (base[i].saveCount >= 0x80) {
                continue;
            }
            cv = GetCRC16(0xffff, &base[i].extensionVersion, 0x8a);
            if (cv != base[i].extendedCrc16) {
                continue;
            }
            if (((1u << base[i].extendedLanguage) & base[i].validLanguageBitmap) == 0) {
                continue;
            }
            if ((mask & base[i].validLanguageBitmap) != 0) {
                base[i].option.language = base[i].extendedLanguage;
            }
            if ((m40 & ~base[i].validLanguageBitmap) != 0) {
                return 3;
            }
            valid = valid | (1 << i);
        }
    } else {
        if ((func_0200103c() & 0x40) != 0) {
            return 3;
        }
        i = 0;
        do {
            cv = GetCRC16(0xffff, &base[i], 0x70);
            if (cv == base[i].crc16) {
                if (base[i].saveCount < 0x80) {
                    valid = valid | (1 << i);
                }
            }
            i = (unsigned short) (i + 1);
        } while (i < 2);
    }

    switch (valid) {
        case 1:
        case 2:
            return valid;
        case 3:
            t = (unsigned char) ((base[0].saveCount + 1) & 0x7f);
            if (t == base[1].saveCount) {
                return 2;
            }
            return 1;
    }
    return 0;
}
