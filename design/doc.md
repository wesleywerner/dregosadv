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

> Legend
> ^ climbable
> & present in the connecting location
> > enterable

```
                      Cliff --- (bridge) --- Waterfall                         
                        ^                     &      &                         
                        ^                     &      &                         
                        ^                Temple      Alcove > Tomb             
                        ^                |                                     
                        ^                |                                     
                 (steps)^                |                                     
                        ^                |                                     
                        ^                |                                     
                        ^                |                                     
      Tree Top     Valley                .                                     
             ^      /                    .                                     
             ^     /                     .                                     
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
_(Implemented, Tested - find_the_way.spec)_
* Why: Find the way through the thick jungle.
* What: No special items required.
* How: Climb the tree in the clearing, look Northeast to see the stone steps.
* Where: Top of tree.

#### Get Bananas
_(Implemented, Tested - get_bananas.spec)_
* Why: required to distract the monkey.
* What: bull whip (inventory item).
* How: Use whip to drop a bunch of bananas from high up.
* Where: Garden.

#### Distract The Monkey
_(Implemented, Tested - distract_monkey.spec)_
* Why: to retrieve your compass.
* What: banana.
* How: show the monkey the banana, then drop it on the ground.
* Where: Wherever the monkey is present.

When the player climbs the tree to Find The Way, the compass falls by accident.
The monkey grabs it and stays out of reach, it will (tauntingly) follow
the player around clutching the device. To retrieve the banana the player uses
the bullwhip to snag and pull some bananas down from a tree in the Garden.
This action frightens the monkey (if present) and it retreats to the clearing.
When the player shows the banana to the monkey then drops it, the monkey
drops the compass to go for the banana.

#### Deadly Drop
_(Implemented, Tested - deadly_drop.spec)_
* Why: Save yourself from a deadly fall.
* What: Crossing the Rope Bridge has a random chance of a plank breaking, the player gets one turn to respond.
* How: Whip the bridge to save yourself from falling.
* Where: Rope Bridge

#### Make a Torch
_(Not Implemented, Not Tested)_
* Why: to enter the dark underground temple.
* What: A stick, some old cloth, an oily substance, crowbar, flint stone.
* How: tie cloth to stick, dip torch in oil, light torch with flint.
* Where: Old Hut and Temple (cloth), Temple (oil), Stream & Water Spring (flint).

1. Search the rubble in the hut to find a crowbar and some old cloth.
2. Search the jungle to find a stick.
3. Pry the stone slab in the Temple open with the crowbar, to find the oily substance and some bones.
4. Tie/wrap the cloth around the stick or bone to make a torch.
5. Dip the torch in the oil.
5. Find the flint stone by the Waterfall (noticeable when carrying the torch).
6. Light the torch with the flint (requires holding the crowbar to strike the flint).

#### Find the Alcove
_(Implemented, Tested - find_the_alcove.spec)_
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

# TODO
* Get NewbieGrammar.h included
* Look in directions in most rooms
* Listen and smell senses in most rooms
* task_scores - DM$ $22
* Changing weather in the sky object
* Optimize entry descriptions for all rooms
* Advent style "go to room" logic, DM4 $30 pg 220
* Fill the journal with notes
