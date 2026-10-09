#include "settings.h"

#include <Preferences.h>

static constexpr const char* NVS_NAMESPACE = "keychain";

static constexpr const char* KEY_BRIGHTNESS = "bright";
static constexpr const char* KEY_SCREEN_TO = "scr_to";
static constexpr const char* KEY_SLEEP_TO = "slp_to";
static constexpr const char* KEY_SOUND = "sound";
static constexpr const char* KEY_24H = "24h";
static constexpr const char* KEY_ALARM_H = "alm_h";
static constexpr const char* KEY_ALARM_M = "alm_m";
static constexpr const char* KEY_ALARM_EN = "alm_en";
static constexpr const char* KEY_BAT_LOW = "bat_low";
static constexpr const char* KEY_BAT_CRIT = "bat_crit";
static constexpr const char* KEY_LOCK = "lock";

Settings settings;

bool Settings::begin() {
    Preferences prefs;

    if (!prefs.begin(NVS_NAMESPACE, false)) {
        resetDefaults();
        initialized = false;
        return false;
    }

    values.brightness =
        prefs.getUChar(KEY_BRIGHTNESS, 100);

    values.screenTimeoutMs =
        prefs.getUInt(KEY_SCREEN_TO, 30000);

    values.sleepTimeoutMs =
        prefs.getUInt(KEY_SLEEP_TO, 120000);

    values.soundEnabled =
        prefs.getBool(KEY_SOUND, true);

    values.format24Hour =
        prefs.getBool(KEY_24H, true);

    values.alarmHour =
        prefs.getUChar(KEY_ALARM_H, 7);

    values.alarmMinute =
        prefs.getUChar(KEY_ALARM_M, 0);

    values.alarmEnabled =
        prefs.getBool(KEY_ALARM_EN, false);

    values.batteryLowPercent =
        prefs.getUChar(KEY_BAT_LOW, 20);

    values.batteryCriticalPercent =
        prefs.getUChar(KEY_BAT_CRIT, 5);

    values.buttonLock =
        prefs.getBool(KEY_LOCK, false);

    prefs.end();

    if (!validate()) {
        resetDefaults();
        save();
        initialized = false;
        return false;
    }

    initialized = true;
    return true;
}

const SettingsData& Settings::data() const {
    return values;
}

bool Settings::save() {
    Preferences prefs;

    if (!prefs.begin(NVS_NAMESPACE, false)) {
        return false;
    }

    prefs.putUChar(KEY_BRIGHTNESS, values.brightness);
    prefs.putUInt(KEY_SCREEN_TO, values.screenTimeoutMs);
    prefs.putUInt(KEY_SLEEP_TO, values.sleepTimeoutMs);
    prefs.putBool(KEY_SOUND, values.soundEnabled);
    prefs.putBool(KEY_24H, values.format24Hour);

    prefs.putUChar(KEY_ALARM_H, values.alarmHour);
    prefs.putUChar(KEY_ALARM_M, values.alarmMinute);
    prefs.putBool(KEY_ALARM_EN, values.alarmEnabled);

    prefs.putUChar(KEY_BAT_LOW, values.batteryLowPercent);
    prefs.putUChar(KEY_BAT_CRIT, values.batteryCriticalPercent);

    prefs.putBool(KEY_LOCK, values.buttonLock);

    prefs.end();

    return true;
}

void Settings::resetDefaults() {
    values = SettingsData();
}

void Settings::setBrightness(uint8_t value) {
    if (value > 100) {
        value = 100;
    }

    if (values.brightness == value) {
        return;
    }

    values.brightness = value;
    save();
}

void Settings::setScreenTimeout(uint32_t value) {
    if (value < 5000) {
        value = 5000;
    }

    if (values.screenTimeoutMs == value) {
        return;
    }

    values.screenTimeoutMs = value;
    save();
}

void Settings::setSleepTimeout(uint32_t value) {
    if (value < 10000) {
        value = 10000;
    }

    if (values.sleepTimeoutMs == value) {
        return;
    }

    values.sleepTimeoutMs = value;
    save();
}

void Settings::setSoundEnabled(bool enabled) {
    if (values.soundEnabled == enabled) {
        return;
    }

    values.soundEnabled = enabled;
    save();
}

void Settings::set24Hour(bool enabled) {
    if (values.format24Hour == enabled) {
        return;
    }

    values.format24Hour = enabled;
    save();
}

void Settings::setAlarm(
    uint8_t hour,
    uint8_t minute,
    bool enabled
) {
    if (hour > 23 || minute > 59) {
        return;
    }

    if (values.alarmHour == hour &&
        values.alarmMinute == minute &&
        values.alarmEnabled == enabled) {
        return;
    }

    values.alarmHour = hour;
    values.alarmMinute = minute;
    values.alarmEnabled = enabled;

    save();
}

void Settings::setBatteryThresholds(
    uint8_t lowPercent,
    uint8_t criticalPercent
) {
    if (lowPercent > 100) {
        lowPercent = 100;
    }

    if (criticalPercent > lowPercent) {
        criticalPercent = lowPercent;
    }

    if (values.batteryLowPercent == lowPercent &&
        values.batteryCriticalPercent == criticalPercent) {
        return;
    }

    values.batteryLowPercent = lowPercent;
    values.batteryCriticalPercent = criticalPercent;

    save();
}

void Settings::setButtonLock(bool locked) {
    if (values.buttonLock == locked) {
        return;
    }

    values.buttonLock = locked;
    save();
}

bool Settings::validate() const {
    if (values.brightness > 100) {
        return false;
    }

    if (values.screenTimeoutMs < 5000) {
        return false;
    }

    if (values.sleepTimeoutMs < 10000) {
        return false;
    }

    if (values.alarmHour > 23 ||
        values.alarmMinute > 59) {
        return false;
    }

    if (values.batteryLowPercent > 100 ||
        values.batteryCriticalPercent > 100) {
        return false;
    }

    if (values.batteryCriticalPercent >
        values.batteryLowPercent) {
        return false;
    }

    return true;
}
