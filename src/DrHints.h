Object Hints "hint options"
with
    ! Warn the first time hints are used.
    Warning true,
    NoBanana,
    HasBanana,
    TreetopNotVisited,
    TreetopVisited,
    GlyphsNotSeen,
    GlyphsSeen,
    NoTorch,
    NoWick,
    NoFlint,
    NotOily,
    TieWick,
    KeyHole,
    PlanBribe,
    CatchChic,
    NoWeightedObject,
    ;

[ HintSub itemA itemB itemC;
    if (Hints.Warning) {
        Hints.Warning = false;
        "You are about to ask Dr Hint for advice. Each time you type HINT
        you are given the next clue, based on my current situation, and each will be more of a spoiler.
        If you are sure you want a clue, type HINT again.";
    }
    
    ! Exit a dark Tomb
    if (location == thedark && real_location == Tomb) {
        "This place is dark, but I can still go up. ";
    }
    
    ! Lost
    if (location == LostInJungle) {
        if (ItemInPlayer(lodestar)) {
            "I can read my compass to find the way back. ";
        } else {
            ! no compass
            "Without my compass, I can only keep trying my luck. ";
        }
    }
    
    ! Seeing the way to the Valley
    if (Clearing has visited && Clearing.n_to ~= valley_way) {
        style bold;
        print "I can't find the way past the clearing: ";
        style roman;
        if (TreeTop has visited) {
            switch (++Hints.TreetopVisited) {
                1: "The path is overgrown, and visible from a higher vantage point. ";
                2: "From the top of the tree, I can look in all directions. ";
                3: "The river is south, so I want to look in the opposite direction. ";
                default: "Look north from the top of the tree. ";
            }
        } else {
            ! not visited treetop
            switch (++Hints.TreetopNotVisited) {
                1: "The path is overgrown, and visible from a higher vantage point. ";
                2: "I can try climb a tall tree. ";
                default: "Climb the fig tree. ";
            }
        }
    }
    
    ! Finding the alcove behind the waterfall
    if (Temple has visited && alcove_door notin Waterfall) {
        if (temple_glyphs hasnt examined) {
            switch (++Hints.GlyphsNotSeen) {
                1: "A way is hidden near the temple. ";
                2: "The writing is on the walls, as the saying goes. ";
                3: "An ancient form of writing in the temple provides a clue. ";
                default: "Examine the symbols on the temple walls. ";
            }
        }
        if (temple_glyphs has examined) {
            switch (++Hints.GlyphsSeen) {
                1: "My journal contains notes on some symbols. ";
                2: "I should read my notes on the symbol I see in the temple. ";
                default: "Look behind the waterfall. ";
            }
        }
    }
    
    ! Making a torch. Enter the dark alcove.
    if (alcove_door in Waterfall && Tomb hasnt visited) {
        style bold;
        print "I need a light to enter the alcove: ";
        style roman;
        itemA = ItemOfClassInPlayer(TorchBaseObject);
        itemB = ItemOfClassInPlayer(TorchWickObject);
        itemC = ItemOfClassInPlayer(SparkThrowerObject);
        if (itemA && itemA has is_torch) {
            ! has torch
            if (itemA has light) {
                "The torch is lit. I can enter it now. ";
            } else
            if (itemA has oily) {
                if (itemC) {
                    ! has flint
                    "Light ", (the) itemA, " with ", (the) itemC, ". ";
                } else {
                    ! no flint
                    switch (++Hints.NoFlint) {
                        1: "I need something that makes sparks, to light the torch. ";
                        2: "I could ask my guide about fire. ";
                        default: "I could even find fire in the tribe. ";
                    }
                }
            } else {
                ! no oil
                switch(++Hints.NotOily) {
                    1: "The torch needs some kind of fuel. ";
                    2: "Oil can be used as fuel for the torch. ";
                    3: "I can find oil in the temple. ";
                    default: "Dip the torch in the oil. ";
                }
            }
        }
        else {
            if (itemA) {
                ! has torch
                if (itemB) {
                    ! has wick
                    switch(++Hints.TieWick) {
                        1: "To make a wick, bind some cloth to the base. ";
                        default: "Tie ", (the) itemB, " to ", (the) itemA, ". ";
                    }
                } else {
                    ! no wick
                    switch(++Hints.NoWick) {
                        1: "A torch needs a wick.
                            Some cloth might do the trick. ";
                        2: "Search amongst some junk for wicking material. ";
                        default: "Search the rubble in the bungalow. ";
                    }
                }
            } else {
                ! no torch
                switch(++Hints.NoTorch) {
                    1: "I could make a torch.
                        I need something long for the base of the torch,
                        something that will work as a wick,
                        and some kind of fuel. ";
                    2: "A stick or bone, but not a stone, 
                        will work as a base for a torch. ";
                    3: "The jungle should be full of sticks. ";
                    default: "Search the jungle. ";
                }
            }
        }
    }
    
    ! Catch a chicken
    if (ItemInPlayer(sun_drawing)) {
        if (box_trap has moved) {
            switch (++Hints.CatchChic) {
                1: "Set the trap down on the ground. ";
                2: "There should be seed in the trap, to lure the chicken in. ";
                3: "Remember to set the trap. ";
                4: "Pull the string when the chicken is in the trap. ";
                default: "drop trap. put seed in it. set it. wait.
                    pull the string. ";
            }
        } else {
            ! trap has not moved
            if (Tribe has visited) {
                switch (++Hints.PlanBribe) {
                    1: "I suspect the carver can make a replica key,
                        given the drawing. ";
                    2: "Show the drawing to the carver. ";
                    3: "The carver wants payment to make a carving. ";
                    4: "There must be a way to trap the chicken. ";
                    default: "Rom, my guide, has a something 
                        to help catch chickens. ";
                }
            } else {
                ! tribe not visited
                "I should visit the tribe. ";
            }
        }
    }
    
    ! Waiting for the carver
    if (carver.carving_state > 1 && carver.carving_state < 50) {
        "The carver is busy making a replica of the sun key.
        I can go to him and WAIT until he is done with it. ";
    }
    
    ! Lowering the altar
    if (Tomb has visited && stone_altar notin Tomb) {
        
        ! using the key
        if (location == Tomb) {
            if (ItemInPlayer(sun_key)) {
                "Usually one inserts a key into a keyhole. ";
            }
            if (sun_key in sun_key_hole) {
                "You have to turn the key a few times,
                until it can't turn any more. ";
            }
        } 

        ! return to the tomb
        if (ItemInPlayer(sun_key)) {
            "Time to use the sun key. Return to the tomb,
            via the alcove by the waterfall. ";
        }

        ! collect the key
        if (sun_key in Tribe) {
            "The carver has finished making the replica of the sun key. ";
        }

        ! Carver has not made the sun key
        if (Carver.carving_state == 0) {
            if (~~ItemInPlayer(sun_drawing)) {
                switch (++Hints.KeyHole) {
                    1: "Examine the stone column in the tomb. ";
                    2: "Examine the hole next to the stone column in the tomb. ";
                    3: "Look inside the hole in the tomb. ";
                    default: "Note the symbol you see when looking inside the hole.
                        Read about that symbol in your journal. ";
                }
            }
        }
    }
    
    ! Taking the treasure
    if (stone_altar in Tomb) {
        if (ItemInPlayer(golden_egg)) {
            "I have the treasure already, hooray for me!
            Guess I won't need a hint then. ";
        } else {
            if (stone_egg in stone_altar) {
                "With the weight on the plate, the prize should be safe to take. ";
            } else {
                if (ItemInPlayer(stone_egg)) {
                    "To stop the pressure plate from activating, I should put
                    this heavy item on the altar, before taking the treasure. ";
                } else {
                    ! no weighted object
                    switch (++Hints.NoWeightedObject) {
                        1: "The altar has a pressure sensitive surface. ";
                        2: "I can put something heavy on the altar
                        to prevent the pressure plate from activating. ";
                        3: "I can find something heavy in the temple. ";
                        default: "Put a heavy thing on the altar,
                            then take the treasure. ";
                    }
                }
            }
        }
    }
    
    ! Reclaim your compass from the monkey
    ! (this hint listed last, so that hints resume even without the device)
    if (lodestar in monkey) {
        style bold;
        print "The monkey has my compass: ";
        style roman;
        itemA = ItemOfClassInPlayer(EdibleFruitObject);
        if (itemA) {
            ! has banana
            switch (++Hints.HasBanana) {
                1: "Show ",(the) itemA," to the monkey. ";
                2: "Leave the banana on the ground. ";
                default: "Drop the banana and wait. ";
            }
        } else {
            ! no banana
            switch (++Hints.NoBanana) {
                1: "Distract it with something else. ";
                2: "They are fond of bananas. ";
                3: "Look in the garden for a banana. ";
                4: "My whip is useful to grab things out of reach. ";
                default: "Whip the bananas. ";
            }
        }
    }
    
    ! No hints
    "I don't have any hints right now. Try exploring a bit more. ";
];

Verb meta 'hint' * -> Hint;
Verb meta 'hints' = 'hint';