#include "Health.h"
Health::Health(int val) : value(val < 0 ? 0 : val) {}
void Health::decrease(int amount) { value -= amount; if (value < 0) value = 0; }
void Health::increase(int amount) { value += amount; }
bool Health::isZero() const { return value <= 0; }
int Health::getValue() const { return value; }