#pragma once
void SetupBatteryProtect();
void LoopBatteryProtect();
bool GetBatteryAlarmState();

// measured values with actual reistors result into 190 digits per Volt
// what I measured:
// 796 at 4.2V
// 708 at 3.7V
// 626  at 3.3V
#define DIGITS_PER_VOLT 190.0

// on an other chip, I measured:
// 823 at 4.2V
// 726 at 3.7V
// 649  at 3.3V
// which was 194 digits per volt

