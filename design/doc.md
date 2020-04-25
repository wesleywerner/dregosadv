# Summary

You play the role of Dr Ego, Adventurous Archeologist. You travel to New Guinea looking for a famed artifact - the cursed Egg of Man-toomba.

This is a short story written in Inform 6 with the hope of learning how to implement these goals:

1. Opening a locked container
2. Looking in directions
3. Combine things to create something new
4. Dark rooms and a light source
5. Create a reasonably believable NPC
6. Make something edible

# Implementation Notes

* DM4 $13 Doors and steps and bridges. Pg 80 has steps example.
* See DM4 pg 92 for adding custom verbs.

# Map of the island

```
                      Cliff --- (bridge) --- Waterfall                         
                        ^                      .                               
                        ^                      .                               
                        ^                      . (jump)                        
                        ^                      .                               
                        ^                      .                               
                 (steps)^                      Plunge Pool                     
                        ^                      &         &                     
                        ^                  Temple       Alcove --> Tomb        
                        ^                              (hidden)                
      Tree Top     Valley                                                      
             ^      /                                                          
             ^     /                                                           
             ^ Clearing -------- Jungle Path                                   
                  |                   |                                        
               Old Hut                |                                        
              /                       |                                        
          Garden                 River Shore                                   
                                   (START)                                     

```

# Inventory

You start off with some basic items

* A compass, to help you navigate in the jungle.
* A bullwhip, for grappling items.
* Journal, containing your notes about the region and the treasured artifact.

# Puzzles

#### Find The Way
_(Implemented, Not Tested)_
* Why: Find the way through the thick jungle.
* What: No special items required.
* How: Climb the tree in the clearing, look Northeast to see the stone steps.
* Where: Top of tree.

#### Get Bananas
_(Implemented, Not Tested)_
* Why: required to distract the monkey.
* What: bull whip (inventory item).
* How: Use whip to drop a bunch of bananas from high up.
* Where: Garden.

#### Distract The Monkey
_(Implemented, Not Tested)_
* Why: to retrieve your compass.
* What: banana.
* How: show the monkey the banana, then drop it on the ground.
* Where: Wherever the monkey is present (drop the banana).

When the player climbs the tree to Find The Way, the compass falls by accident.
The monkey grabs it and stays out of reach, it will (tauntingly) follow
the player around clutching the device. To retrieve the banana the player uses
the bullwhip to snag and pull some bananas down from a tree in the Garden.
This action frightens the monkey (if present) and it retreats to the clearing.
When the player shows the banana to the monkey then drops it, the monkey
drops the compass to go for the banana.

#### Deadly Drop
_(Not Implemented, Not Tested)_
* Why: Save yourself from a deadly fall.
* What: Crossing the Rope Bridge has a random chance in the bridge snapping, a message prints and gives the player one turn to act to save themselves.
* How: Whip the bridge to save yourself from falling.
* Where: Rope Bridge

#### Find Oil
_(Not Implemented, Not Tested)_
* Why: oil is needed to make the torch.
* What: crowbar, stone slab.
* How: pry the stone slab open.
* Where: Temple.

#### Make a Torch
_(Not Implemented, Not Tested)_
* Why: to enter the dark underground temple.
* What: A stick, some old cloth, an oily substance, crowbar, flint stone.
* How: tie cloth to stick, dip torch in oil, light torch with flint.
* Where: Old Hut (cloth), Temple (oil), Stream & Water Spring (flint).

#### Find the Alcove
_(Not Implemented, Not Tested)_
* Why: to enter the underground temple.
* What: no special items required.
* How: examining stone carvings in the temple reveals a very noticeable glyph, the player should consult / look up this glyph in the journal to discover it translates to "a door behind falling water". Searching the waterfall reveals the door.
* Where: Temple

#### Pressure Plate Booby Trap
_(Not Implemented, Not Tested)_
* Why: get the golden egg without setting off the trap.
* What: Stone statue.
* How: Place the stone statue on the pressure plate before taking the egg.
* Where: Tomb (stone statue).
