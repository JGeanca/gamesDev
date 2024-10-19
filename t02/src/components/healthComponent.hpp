#ifndef HEALTH_COMPONENT_HPP
#define HEALTH_COMPONENT_HPP

struct HealthComponent {
  int maxHealth;
  int currentHealth;
  int regenerationRate;
  double regenerationTimer;

  HealthComponent(int max = 100, int regen = 0)
      : maxHealth(max),
        currentHealth(max),
        regenerationRate(regen),
        regenerationTimer(0) {}

  void takeDamage(int damage) {
    currentHealth -= damage;
    if (currentHealth < 0) currentHealth = 0;
  }

  void heal(int amount) {
    currentHealth += amount;
    if (currentHealth > maxHealth) currentHealth = maxHealth;
  }

  bool isDead() const { return currentHealth <= 0; }
};

#endif  // HEALTH_COMPONENT_HPP