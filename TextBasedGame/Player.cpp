//Lewis Andrew Broad. Buckinghamshire New University
#include "Player.h"

void Player::Display() const{
    cout << "\nPlayer Info:\n";
    Character::Display();
    
}
void Player::Display(bool breif) const { //override for the display function.
	cout << "\nPlayer Info:\n";
    Character::Display(true);
}
Player* Player::PlayerCreation() { //Static  method that creates and returns a new Player object. it creates a new instance of the class
    string name;
    Specialty specialty;
    //initialise variables
    int maxHealth = 0;
    int health = 0;
    int physDamage = 0;
    int magDamage = 0;
    int armour = 0;
    int magResist = 0;

    cout << "Enter your characters name: ";
    cin >> name;

    //character class selection here
    cout << "Choose your class: \n";
    cout << "1. Knight (High Health, High Resist, Low Damage)\n";
    cout << "2. Mage (Medium Health, High Magic Resist, High Magic Damage)\n";
    cout << "3. Rogue (low Health, High Physical Damage)\n";
    cout << "4. Wimp (Low Health, Low Damage)\n";
    int choice;
    cin >> choice;
    cin.ignore();
    
	switch (choice) { //switch statement to set the values of the player based on the class chosen
    case 1:
        specialty = Specialty::Knight;
        maxHealth = 200;
        health = 200;
        physDamage = 20;
        magDamage = 10;
        armour = 20;
        magResist = 15;
        break;
    case 2:
        specialty = Specialty::Mage;
        maxHealth = 100;
        health = 100;
        physDamage = 15;
        magDamage = 30;
        armour = 10;
        magResist = 15;
        break;
    case 3:
        specialty = Specialty::Rogue;
        maxHealth = 75;
        health = 75;
        physDamage = 50;
        magDamage = 10;
        armour = 10;
        magResist = 10;
        break;
    case 4:
        specialty = Specialty::Wimp;
        maxHealth = 75;
        health = 75;
        physDamage = 15;
        magDamage = 15;
        armour = 5;
        magResist = 5;
        break;
    default:
        cout << "invalid class. Defaulting to knight\n";
        specialty = Specialty::Knight;
        maxHealth = 200;
        health = 200;
        physDamage = 20;
        magDamage = 10;
        armour = 20;
        magResist = 15;
        break;
    }
    cout << "Character created: " << name << " the " << getSpecialty(specialty);
	return new Player(name, specialty, maxHealth, health, physDamage, magDamage, armour, magResist); //returns a new player object
}
string Player::getSpecialty(Specialty specialty) {
    switch (specialty) {
    case Specialty::Knight:
        return "Knight";
    case Specialty::Mage:
        return "Mage";
    case Specialty::Rogue:
        return "Rogue";
    case Specialty::Wimp:
        return "Wimp";
    default:
        return "Unkown";

    }
}
void Player::levelUp() {
    Character::levelUp();

}

void Player::heal(int healing) {
    health += healing;
    if (health > maxHealth) health = maxHealth;
}
void Player::boostAttack(int boost) {
    if (physDamage > magDamage) {
        physDamage += boost;
    }
    else magDamage += boost;
}
void Player::resistBoost(int boost) {
    armour += boost;
    magResist += boost;
}


