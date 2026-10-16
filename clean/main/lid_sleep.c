/* The console's lid closing and opening (lid_sleep.h). */
#include "lid_sleep.h"

#include "clean.h"
#include "main/sound.h"

#define LID_SLEEP_SAVED 1u          /* the backlights are saved and off */
#define LID_SLEEP_KEEP_SOUND_OFF 2u /* the sound stays muted on waking */

enum LidSleepState { LID_SLEEP_OPEN, LID_SLEEP_CLOSED, LID_SLEEP_WAKING };

/* NitroSDK's PM arguments: the screens and the backlight switch. */
#define LID_SLEEP_LCD_TOP 0
#define LID_SLEEP_LCD_BOTTOM 1
#define LID_SLEEP_LCD_BOTH 2
#define LID_SLEEP_BACKLIGHT_OFF 0
#define LID_SLEEP_LCD_ON 1

/* The ARM7's word of the buttons it reads (X, Y, ...); bit 15 is set while the lid is closed. */
#define LID_SLEEP_BUTTONS (*(const volatile u16 *) 0x027fffa8)
#define LID_SLEEP_LID_CLOSED 0x8000u

extern u8 data_021f4acc;  /* the flags */
extern u8 data_021f4ad0;  /* the state */
extern u32 data_021f4ad4; /* the bottom screen's saved backlight */
extern u32 data_021f4ad8; /* the top screen's */

extern int PM_GetLCDPower(void);
extern int PM_SetLCDPower(int on);
extern u32 PM_GetBackLight(u32 *top, u32 *bottom);
extern int func_0211dc78(int screens, u32 backlight); /* PM_SetBackLight */

static int lid_closed(void)
{
    /* HW: the ARM7 keeps this word up to date. */
    return (LID_SLEEP_BUTTONS & LID_SLEEP_LID_CLOSED) != 0;
}

/* func_020b025c */
void LidSleep_ClearFlags(u8 flags)
{
    data_021f4acc = (u8) (data_021f4acc & ~flags);
}
CLEAN_AS(func_020b025c, LidSleep_ClearFlags)

/* func_020b026c */
void LidSleep_SetFlags(u32 flags)
{
    data_021f4acc = (u8) (data_021f4acc | flags);
}
CLEAN_AS(func_020b026c, LidSleep_SetFlags)

/* func_020b027c: whether any of `flags` is set. */
int LidSleep_HasFlags(u8 flags)
{
    return (data_021f4acc & flags) != 0;
}
CLEAN_AS(func_020b027c, LidSleep_HasFlags)

/* func_020b0294: powers the screens up (giving up for this frame when that fails), turns the
 * sound up unless it is to stay muted, and the lid counts as open. */
void LidSleep_Wake(void)
{
    /* HW: the power goes up before the sound. */
    if (PM_GetLCDPower() != LID_SLEEP_LCD_ON && PM_SetLCDPower(LID_SLEEP_LCD_ON) == 0) {
        return;
    }
    if (LidSleep_HasFlags(LID_SLEEP_KEEP_SOUND_OFF) == 0) {
        SoundSys_MasterVolumeFull();
    }
    data_021f4ad0 = LID_SLEEP_OPEN;
}
CLEAN_AS(func_020b0294, LidSleep_Wake)

/* func_020b02c8: the saved backlights back on, when saved. */
void LidSleep_RestoreBacklights(void)
{
    if (LidSleep_HasFlags(LID_SLEEP_SAVED) != 0) {
        func_0211dc78(LID_SLEEP_LCD_TOP, data_021f4ad8);
        func_0211dc78(LID_SLEEP_LCD_BOTTOM, data_021f4ad4);
        LidSleep_ClearFlags(LID_SLEEP_SAVED);
    }
}
CLEAN_AS(func_020b02c8, LidSleep_RestoreBacklights)

/* func_020b0300: saves both backlights and turns them off, unless already saved. */
void LidSleep_BacklightsOff(void)
{
    if (LidSleep_HasFlags(LID_SLEEP_SAVED) == 0) {
        PM_GetBackLight(&data_021f4ad8, &data_021f4ad4);
        func_0211dc78(LID_SLEEP_LCD_BOTH, LID_SLEEP_BACKLIGHT_OFF);
        LidSleep_SetFlags(LID_SLEEP_SAVED);
    }
}
CLEAN_AS(func_020b0300, LidSleep_BacklightsOff)

/* func_020b0334: the sound stays muted when the lid opens. */
void LidSleep_KeepSoundOff(void)
{
    LidSleep_SetFlags(LID_SLEEP_KEEP_SOUND_OFF);
}
CLEAN_AS(func_020b0334, LidSleep_KeepSoundOff)

/* func_020b0340: once a frame. Open: a closing lid turns the backlights and the screens off
 * and mutes the sound. Closed: an opening lid restores the backlights and starts waking.
 * Waking: LidSleep_Wake until it works. */
void LidSleep_Update(void)
{
    switch (data_021f4ad0) {
        case LID_SLEEP_OPEN:
            if (lid_closed()) {
                data_021f4ad0 = LID_SLEEP_CLOSED;
                LidSleep_BacklightsOff();
                PM_SetLCDPower(0);
                SoundSys_MasterVolumeOff();
            }
            break;
        case LID_SLEEP_CLOSED:
            if (!lid_closed()) {
                data_021f4ad0 = LID_SLEEP_WAKING;
                LidSleep_RestoreBacklights();
                LidSleep_Wake();
            }
            break;
        case LID_SLEEP_WAKING:
            LidSleep_Wake();
            break;
    }
}
CLEAN_AS(func_020b0340, LidSleep_Update)

/* func_020b03ac */
void LidSleep_Reset(void)
{
    data_021f4acc = 0;
    data_021f4ad0 = LID_SLEEP_OPEN;
}
CLEAN_AS(func_020b03ac, LidSleep_Reset)
