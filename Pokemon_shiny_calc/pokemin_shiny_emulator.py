import random

shiny_chance = 1365
pokemon_spawn = 15
counter = 0
shiny_nr = 0
emulation_rounds = 1000
found = False
done = False

found_numbers = []

while not done:
    for x in range(pokemon_spawn):
        if found:
            counter = 0
            found = False
        new_spawn = random.randint(1,shiny_chance)
        if new_spawn == 1:
            found = True
            shiny_nr = shiny_nr + 1
            print("Shiny pokemon found in wave " + str(counter) + "!")
            found_numbers.append(counter)
            if shiny_nr == emulation_rounds:
                done = True
    counter = counter + 1

nr = 0
for x in found_numbers:
    nr = nr + x
avg = nr / len(found_numbers)
print("The avrage rounds of " + str(emulation_rounds) + " emulation rounds, are: " + str(avg))