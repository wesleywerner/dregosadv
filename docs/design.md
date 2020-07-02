# Dr Ego's Adventure - Design Document

You play the role of Dr Ego, Adventurous Archeologist. You travel to New Guinea looking for a famed artifact - the cursed Egg of Man-toomba.

This is a short story written in Inform 6 with the hope of learning how to implement these goals:

1. Opening a locked container
2. Looking in directions
3. Combine things to create something new
4. Dark rooms and a light sources
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

List of the puzzles in the game that give score.

#### Use the Compass

It is easy to get lost in the thick jungle since the dense foliage hides all
distinguishing landmarks. Attempts to backtrack fails, and repeated attempts to
go in any direction has a chance of finding the way back eventually, however
using the compass finds the way back in a single turn.

Technical notes:
1. Any room of class `JungleRoom` moves the player to the `LostInJungle` room, if moving in an undefined direction.
2. The value of `OddsOfFindingWayWhenLost` defines the chance of the player stumbling their way back to the last known location.

Implemented. Tested in `compass.spec`

* Why: Return to the last known location when lost in the jungle
* What: Your compass
* How: Examine the compass
* Where: LostInJungle room

#### Find The Way

The player reaches a location where there is no known path forward. To find the
path they need to climb up a tree to spot a distant stone staircase and reveal
the direction to move forward.

Technical notes:
1. The `TreeTop` room is where this puzzle takes place.

_Implemented. Tested in `find_the_way.spec`_

* Why: Find the path to progress forward
* What: No special items required
* How: Climb the tree and look northeast
* Where: In the clearing

#### Get Bananas

The player uses their bullwhip to snag a banana hanging out of reach.
The player can eat the banana and get another one, but ultimately the fruit is
used to solve another puzzle. This whip action frightens the monkey if it is
present, and it scurries away.

Technical notes:
1. The `garden_trees` object controls the whipping action.

_Implemented. Tested in `get_bananas.spec`_

* Why: required for the "Distract The Monkey" puzzle
* What: bull whip
* How: whip tree or whip bananas
* Where: Garden

#### Distract The Monkey

When the player climbs the tree to Find The Way, the compass falls by accident.
The monkey grabs the compass and stays out of reach, tauntingly following
the player around clutching the device. To retrieve the compass, the player 
drops a banana on the ground, the monkey grabs the banana and loses interest in
the compass, leaving it for the player to reclaim.

Technical notes:
1. The `monkey` daemon controls all the monkey's actions, including looking for edible fruit in the current location.

_Implemented. Tested in `distract_monkey.spec`_

* Why: to retrieve your compass from the monkey
* What: a banana
* How: show the monkey the banana, drop it
* Where: Wherever the monkey is present

#### Deadly Drop

A jungle should have at least one dangerous rope bridge, in this game the player has to cross a rope bridge at some point. There is a random chance that the player may fall off, when this happens the player is told they are losing their balance, and gives the opportunity to save themselves by using their whip. If the player falls to their death, the game hints at how they could have saved themselves, and offers the `undo` option.

Technical notes: 
1. The `bridge_way` door performs the check if the player should fall, the player is moved to the `DeadlyDrop` room if this happens.
2. The `DeadlyDrop` room controls the turns until player death, as well as the saving whip action.

_Implemented. Tested in `deadly_drop.spec`_

* Why: Save yourself from a deadly fall
* What: bullwhip
* How: whip the bridge
* Where: crossing the bridge from the Cliff or Waterfall

#### Make a Torch

The tomb is a dark place, to enter it the player must have a light source.

Technical notes:
1. An object of class `TorchWickObject` can be tied to objects of class `TorchBaseObject` to make a torch.
2. The `TorchFuelObject` class simulates an oily substance. It covers other objects in oil if they are inserted in the oil's container, i.e. gives the `oily` attribute. The oil itself cannot be taken from its container.
3. The `TorchBaseObject` class controls burning the torch, it checks if the torch has a wick tied to it, and that the torch has the `oily` attribute.
4. A torch must be burned with a `SparkThrowerObject`.
5. The player starts with a matchbook, but it has the `wet` attribute and is simply a red herring.

_Implemented. Tested in `make_a_torch.spec`_

* Why: to enter the dark underground temple
* What: A stick or bone, some old cloth, an oily substance, a flint stone
* How: tie cloth to stick, dip torch in oil, light torch with flint
* Where: Jungle (stick), Bungalow (cloth), Temple (oil urn, bone), Waterfall (flint)

1. search the rubble in the Bungalow to find old cloth, or search the jungle to find a stick.
2. open the stone lid in the Temple to find the oil urn and a bone
3. Tie the cloth to the stick or bone to make a torch
4. Dip the torch in the oil urn
5. Find the flint stone by the Waterfall (seen when carrying a torch)
6. LIGHT TORCH WITH FLINT

#### Find the Alcove

The alcove that leads to the underground Tomb is hidden behind the cascading waterfall.

_Implemented. Tested in `find_the_alcove.spec`_

* Why: to enter the Tomb
* What: no special items required
* How: examining stone carvings in the temple reveals a very noticeable glyph, the player should consult / look up this glyph in the journal to discover it translates to "a door behind falling water". Searching the waterfall reveals the door.
* Where: Temple, Waterfall

#### Pressure Plate Booby Trap

Taking the Golden Egg triggers a trap of poison darts, killing the player. To prevent this demise, the player should place an egg-shaped stone on the altar before taking the prize.

_Implemented. Tested in `pressure_plate_trap.spec`_

* Why: take the golden egg without setting off the trap
* What: stone egg
* How: put the stone on the altar
* Where: Temple (stone egg), Tomb (altar)

# Scores

Using the task scoring system, these tasks are Achievable. See the `task_scores` variable in the source.

+ 1: Use your compass when lost in the jungle. (puzzle)
+ 2: See the stairs from the top of the tree. (puzzle)
+ 3: Whip a banana off the tree. (puzzle)
+ 4: Retrieve your compass from the monkey. (puzzle)
+ 5: Made a torch. (puzzle)
+ 6: Discover the alcove behind the waterfall. (puzzle)
+ 7: Get the golden egg without setting off the dart trap. (puzzle)
+ 8: Catch a fish with your whip (amusing)

# TODO
* Add HELP, ABOUT, HINT
* Optimize entry descriptions for all rooms
* Fill the journal with notes
* Use ScenicBase
* Remove the crowbar and MetalObject, these are not used
* Try get oil on inventory items, and examining oily things descriptions

### Done
* Add task based scoring - DM$ $22
* Changing weather in the sky object
* Add ways (doors) to locations so that player can GO WAY
* Include "Scenic" and write up some scenery