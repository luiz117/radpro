/*
 * Rad Pro
 * Keyboard
 *
 * (C) 2022-2024 Gissio
 *
 * License: MIT
 */

#include <stdint.h>

#include "cmath.h"
#include "events.h"
#include "keyboard.h"

#if defined(KEYBOARD_5KEYS)

#define KEY_REPEAT_START ((uint32_t)(0.5 * SYSTICK_FREQUENCY / KEY_TICKS))
#define KEY_REPEAT_PERIOD ((uint32_t)(0.05 * SYSTICK_FREQUENCY / KEY_TICKS))

#define KEY_PRESSED_LONG ((uint32_t)(1.0 * SYSTICK_FREQUENCY / KEY_TICKS))

#elif defined(KEYBOARD_2KEYS)

#define KEY_PRESSED_LONG ((uint32_t)(0.25 * SYSTICK_FREQUENCY / KEY_TICKS))
#define KEY_PRESSED_EXTENDED ((uint32_t)(1.25 * SYSTICK_FREQUENCY / KEY_TICKS))

#endif

static struct
{
    bool isInitialized;

    bool wasKeyDown[KEY_NUM];

    enum Key pressedKey;
    uint32_t pressedTicks;

#if defined(KEYBOARD_5KEYS)

    KeyboardMode mode;

#endif

    volatile enum Event event;
    volatile enum Event lastEvent;
} keyboard;

void initKeyboard(void)
{
    initKeyboardHardware();

    keyboard.pressedKey = KEY_NONE;

    // +++ TEST
    // bool isKeyDown[KEY_NUM];
    // getKeyboardState(isKeyDown);

    // if (isKeyDown[KEY_LEFT])
    //     startBootloader();
    // +++ TEST

    keyboard.isInitialized = true;
}

void onKeyboardTick(void)
{
    if (!keyboard.isInitialized)
        return;

    enum Event event = EVENT_NONE;

    bool isKeyDown[KEY_NUM];
    getKeyboardState(isKeyDown);

    // Key changes

    for (int32_t i = 0; i < KEY_NUM; i++)
    {
        // Key down

        if (!keyboard.wasKeyDown[i] &&
            isKeyDown[i])
        {
#if defined(KEYBOARD_5KEYS)

            if (!((keyboard.mode == KEYBOARD_MODE_MEASUREMENT) &&
                  (i == KEY_LEFT)) &&
                (i != KEY_SELECT))
                event = i;

#endif

            keyboard.pressedKey = i;
            keyboard.pressedTicks = 0;
        }

        // Key up

        if (keyboard.wasKeyDown[i] &&
            !isKeyDown[i] &&
            (i == keyboard.pressedKey))
        {
#if defined(KEYBOARD_5KEYS)

            if (keyboard.pressedTicks < KEY_PRESSED_LONG)
            {
                if ((keyboard.mode == KEYBOARD_MODE_MEASUREMENT) &&
                    (i == KEY_LEFT))
                    event = EVENT_KEY_BACK;
                else if (i == KEY_SELECT)
                    event = (keyboard.mode == KEYBOARD_MODE_MEASUREMENT)
                                ? EVENT_KEY_BACK
                                : EVENT_KEY_SELECT;
            }

#elif defined(KEYBOARD_2KEYS)

            if (keyboard.pressedTicks < KEY_PRESSED_LONG)
            {
                event = (i == KEY_LEFT)
                            ? EVENT_KEY_UP
                            : EVENT_KEY_DOWN;
            }

#endif

            keyboard.pressedKey = KEY_NONE;
        }

        keyboard.wasKeyDown[i] = isKeyDown[i];
    }

    // Key timer

    if (keyboard.pressedKey != KEY_NONE)
    {
        addClamped(&keyboard.pressedTicks, 1);

#if defined(KEYBOARD_5KEYS)

        if (keyboard.pressedTicks >= KEY_REPEAT_START)
        {
            uint32_t repeatTicks =
                (keyboard.pressedTicks - KEY_REPEAT_START) %
                KEY_REPEAT_PERIOD;
            if (repeatTicks == 0)
            {
                if ((keyboard.pressedKey == KEY_UP) ||
                    (keyboard.pressedKey == KEY_DOWN))
                    event = keyboard.pressedKey;
            }
        }

        if (keyboard.pressedTicks == KEY_PRESSED_LONG)
        {
            switch (keyboard.pressedKey)
            {
            case KEY_LEFT:
                event = EVENT_KEY_RESET;

                break;

            case KEY_SELECT:
                event = EVENT_KEY_POWER;

                break;

            default:
                break;
            }
        }

#elif defined(KEYBOARD_2KEYS)

        if (keyboard.pressedTicks == KEY_PRESSED_LONG)
        {
            if (isKeyDown[KEY_LEFT])
            {
                if (isKeyDown[KEY_SELECT])
                    event = EVENT_KEY_RESET;
                else
                    event = EVENT_KEY_BACK;
            }
            else
                event = EVENT_KEY_SELECT;
        }
        else if (keyboard.pressedTicks == KEY_PRESSED_EXTENDED)
        {
            if (isKeyDown[KEY_SELECT])
                event = EVENT_KEY_POWER;
        }

#endif
    }

    // Send key event

    if (event != EVENT_NONE)
        keyboard.event = ((keyboard.event & ~0xf) + 0x10) | event;
}

void setKeyboardMode(KeyboardMode mode)
{
#if defined(KEYBOARD_5KEYS)

    keyboard.pressedKey = KEY_NONE;

    keyboard.mode = mode;

#endif
}

enum Key getKeyboardEvent(void)
{
    volatile enum Event event = keyboard.event;

    if (keyboard.lastEvent != event)
    {
        keyboard.lastEvent = event;

        return event & 0xf;
    }

    return EVENT_NONE;
}
