#include "display_manager.h"

DisplayManager::DisplayManager(): lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE) {}

void DisplayManager::begin()
{
    lcd.begin(16, 2);
    lcd.backlight();
}

void DisplayManager::show(String l1, String l2)
{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(l1);
    lcd.setCursor(0,1);
    lcd.print(l2);
}
