Object Hints "hint options"
with
    ! Warn the first time hints are used.
    Warning true,
    Printed,
    NoBanana,
    HasBanana,
    ValleySeen,
    GlyphsNotSeen,
    GlyphsSeen,
    NoTorch,
    HasTorch,
    KeyHole,
    PlanBribe,
    CatchChic,
    SunKey,
    LowerColumn,
    GoldEgg,
    ;

[ HintPrint str;
    Hints.Printed = true;
    style roman;
	style underline;
	print (string) str; 
	style roman;
    print "^";
];

[ HintSub;
    Hints.Printed = false;
    if (Hints.Warning) {
        Hints.Warning = false;
        HintPrint("You are about to ask Dr Hint for advice. Each time you type HINT
        you are given the next clue, based on your current situation, and each will be more of a spoiler.
        If you are sure you want a clue, type HINT again.");
        return;
    }
    ! Reclaim your compass from the monkey
    if (lodestar in monkey) {
        style bold;
        print "The monkey has your compass, ";
        if (banana notin player) {
            switch (++Hints.NoBanana) {
                1: HintPrint("perhaps you could distract it with something else...");
                2: HintPrint("maybe something edible will distract it...");
                3: HintPrint("I hear they are fond of bananas...");
                default: HintPrint("look for a banana in the garden, outside the bungalow.");
            }
        }
        if (banana in player) {
            switch (++Hints.HasBanana) {
                1: HintPrint("give it a fruit, it may just forget about your compass.");
                2: HintPrint("try leaving the fruit where the monkey can see it.");
                default: HintPrint("DROP the banana on the ground, then WAIT.");
            }
        }
    }
    ! Seeing the way to the Valley
    if (Clearing has visited && Clearing.ne_to ~= valley_way) {
        style bold;
        print "To find the way, ";
        switch (++Hints.ValleySeen) {
            1: HintPrint("perhaps the path is overgrown and not immediately visible...");
            2: HintPrint("you might be able to see the path from a higher vantage point...");
            3: HintPrint("you could try climbing up something...");
            default: "climb up the fig tree and LOOK in all directions.";
        }
    }
    if (Clearing has visited && Valley hasnt visited) {
        HintPrint("You should try go the way which you saw from the tree-top.");
    }
    ! Finding the alcove behind the waterfall
    if (Temple has visited && alcove_door notin Waterfall) {
        style bold;
        print "To find the way, ";
        if (temple_glyphs hasnt examined) {
            switch (++Hints.GlyphsNotSeen) {
                1: HintPrint("examine all the details in the Temple...");
                2: HintPrint("an ancient form of writing may give you a clue...");
                default: HintPrint("examine the symbols engraved in the Temple walls.");
            }
        }
        if (temple_glyphs has examined) {
            switch (++Hints.GlyphsSeen) {
                1: HintPrint("maybe your research notes can be of help...");
                2: HintPrint("consult your journal on the glyph you see in the Temple...");
                default: HintPrint("look behind the waterfall.");
            }
        }
    }
    ! Entering the tomb
    if (alcove_door in Waterfall && Tomb hasnt visited) {
        if (GetPlayerTorchObject()) {
            switch (++Hints.HasTorch) {
                1: HintPrint("oil makes good fuel for a wick...");
                1: HintPrint("there is an urn of oil in the Temple...");
                2: HintPrint("dip the torch in the oil...");
                3: HintPrint("if your matches are wet, perhaps you could make sparks using a special stone...");
                4: HintPrint("flint is a stone that throws sparks, they are commonly found in riverbeds or near waterfalls...");
                5: HintPrint("flint has a distinctive blue glint....");
                default: HintPrint("burn the torch with the flint.");
            }
        }
        else {
            style bold;
            print "You need a light, ";
            switch (++Hints.NoTorch) {
                1: HintPrint("you could try make a torch...");
                2: HintPrint("look for a stick or a bone, I am pretty sure you can find a stick in the jungle...");
                3: HintPrint("you can tie some canvas to a stick, to make the wick...");
                4: HintPrint("search the rubble in the bungalow...");
                default: HintPrint("tie some cloth to the stick.");
            }
        }
    }
    ! lowering the alter
    if (Tomb has visited && stone_altar notin Tomb) {
        ! Carver has not made the sun key
        if (Carver.carving_state == 0) {
            if (sun_drawing notin player && sun_drawing notin satchel) {
                switch (++Hints.KeyHole) {
                    1: HintPrint("Examine that stone column in the Tomb...");
                    2: HintPrint("Examine the hole next to the stone column in the Tomb...");
                    default: HintPrint("Look inside the sun shaped hole in the Tomb.");
                }
            }
            else if (box_trap hasnt moved) {
                switch (++Hints.PlanBribe) {
                    1: HintPrint("Did you visit the Tribe...");
                    2: HintPrint("Did you notice the Carver in the Tribe...");
                    3: HintPrint("You would think the Carver can make a replica, given the drawing...");
                    4: HintPrint("The Carver wants a chicken as payment...");
                    5: HintPrint("There must be a way to trap the chicken...");
                    default: HintPrint("Go see Rom, your guide, for advice on catching chickens.");
                }
            }
            else if (box_trap has moved) {
                switch (++Hints.CatchChic) {
                    1: HintPrint("Go where you saw a chicken...");
                    2: HintPrint("There is a chicken in the Tribe...");
                    3: HintPrint("Set the trap down on the ground first...");
                    4: HintPrint("There should be seed in the trap, to lure the chicken in...");
                    5: HintPrint("Remember to set the trap...");
                    default: HintPrint("You need to pull the string, but only when the chicken is inside the trap.");
                }
            }
        }
        ! Use the key to lower the altar
        if (sun_key in player || sun_key in satchel || sun_key in sun_key_hole) {
            switch (++Hints.LowerColumn) {
                1: HintPrint("Now that you have the sun key, or a replica of it, it is time to use it...");
                2: HintPrint("Usually one insert a key into a keyhole...");
                3: HintPrint("It may take a few turns of the key...");
                default: HintPrint("Insert the sun key in the key hole, and turn it.");
            }
        }
    }
    ! Taking the treasure
    if (stone_altar in Tomb && golden_egg in stone_altar) {
        switch (++Hints.GoldEgg) {
            1: HintPrint("The treasure may be booby trapped...");
            2: HintPrint("The treasure rests on a pressure sensitive surface...");
            3: HintPrint("Before taking the treasure, put something heavy next to it, to prevent the pressure plate from activating...");
            4: HintPrint("You may find something heavy in the Temple...");
            default: HintPrint("The stone egg from the Temple should be placed on the altar, before taking the Golden Egg.");
        }
    }
    ! Player has the prize
    if (golden_egg in player || golden_egg in satchel) {
        HintPrint("It seems you have the treasure already, congrats! Guess you won't be needing that hint then. ");
    }
    ! No more hints
    if (~~Hints.Printed) {
        HintPrint("I don't have any hints for you right now, try exploring a bit more.");
    }
    !print "^";
];

Verb meta 'hint' * -> Hint;
Verb meta 'hints' = 'hint';