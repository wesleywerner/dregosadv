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

[ HintSub;
    Hints.Printed = false;
    if (Hints.Warning) {
        Hints.Warning = false;
        "You are about to ask Dr Hint for advice. Each time you type HINT
        you are given the next clue, based on your current situation, and each will be more of a spoiler.
        If you are sure you want a clue, type HINT again.";
    }
    ! Exit a dark Tomb
    if (location == thedark && real_location == Tomb) {
        "You can feel your way to the stairs, and still go up. ";
    }
    ! Reclaim your compass from the monkey
    if (lodestar in monkey) {
        if (banana notin player) {
            switch (++Hints.NoBanana) {
                1: "The monkey has your compass, it seems very interested in the
                device, perhaps you could distract it with something else...";
                2: "Something edible will distract the monkey...";
                3: "Monkeys are fond of bananas...";
                4: "Look in the garden near the bungalow...";
                5: "Your whip may be useful to get the fruit down from the tree...";
                default: "Whip the bananas.";
            }
        }
        if (banana in player) {
            switch (++Hints.HasBanana) {
                1: "Try give a fruit to the monkey...";
                2: "If the monkey seems too skittish to go near you, try leaving
                the fruit on the ground...";
                default: "DROP the banana then WAIT.";
            }
        }
    }
    ! Seeing the way to the Valley
    if (Clearing has visited && Clearing.ne_to ~= valley_way) {
        switch (++Hints.ValleySeen) {
            1: "The path you seek may be overgrown, and not immediately visible...";
            2: "You might be able to see the path from a higher vantage point...";
            3: "Try climbing up something tall...";
            4: "Climb the fig tree and LOOK in all directions...";
            default: "The river is to the south, so you want to look for a path
            in the opposite direction -- one of the three northern directions
            NW, N or NE. ";
        }
    }
    ! Finding the alcove behind the waterfall
    if (Temple has visited && alcove_door notin Waterfall) {
        if (temple_glyphs hasnt examined) {
            switch (++Hints.GlyphsNotSeen) {
                1: "Examine all the details in the Temple...";
                2: "An ancient form of writing may give you a clue...";
                default: "Examine the symbols engraved in the Temple walls...";
            }
        }
        if (temple_glyphs has examined) {
            switch (++Hints.GlyphsSeen) {
                1: "Your journal will be useful here...";
                2: "Examine symbols in the Temple, then read notes on
                the symbol you see...";
                default: "Look behind the waterfall.";
            }
        }
    }
    ! Entering the tomb
    if (alcove_door in Waterfall && Tomb hasnt visited) {
        if (GetPlayerTorchObject()) {
            switch (++Hints.HasTorch) {
                1: "Oil makes good fuel for a wick...";
                1: "There is an urn in the Temple...";
                2: "Dip the torch in the urn...";
                3: "If your matches are wet, you could make sparks using a special stone...";
                4: "Flint is a stone that throws sparks, and is commonly found in riverbeds or near waterfalls...";
                5: "Flint has a distinctive blue glint....";
                default: "Burn the torch with the flint.";
            }
        }
        else {
            switch (++Hints.NoTorch) {
                1: "You need a light to enter the alcove, 
                you could try make a torch...";
                2: "Look for a stick or a bone...";
                3: "You can tie some canvas to a stick, to make the wick...";
                4: "Maybe you can find something useful in some rubble...";
                5: "Search the rubble in the bungalow...";
                default: "Tie the canvas to the stick.";
            }
        }
    }
    ! lowering the alter
    if (Tomb has visited && stone_altar notin Tomb) {
        ! Carver has not made the sun key
        if (Carver.carving_state == 0) {
            if (sun_drawing notin player && sun_drawing notin satchel) {
                switch (++Hints.KeyHole) {
                    1: "Examine that stone column in the Tomb...";
                    2: "Examine the hole next to the stone column in the Tomb...";
                    default: "Look inside the sun shaped hole in the Tomb.";
                }
            }
            else if (box_trap hasnt moved) {
                switch (++Hints.PlanBribe) {
                    1: "Did you visit the Tribe...";
                    2: "Did you notice the Carver in the Tribe...";
                    3: "You would think the Carver can make a replica, given the drawing...";
                    4: "The Carver wants a chicken as payment...";
                    5: "There must be a way to trap the chicken...";
                    default: "Go see Rom, your guide, for advice on catching chickens.";
                }
            }
            else if (box_trap has moved) {
                switch (++Hints.CatchChic) {
                    1: "Go where you saw a chicken...";
                    2: "There is a chicken in the Tribe...";
                    3: "Set the trap down on the ground first...";
                    4: "There should be seed in the trap, to lure the chicken in...";
                    5: "Remember to set the trap...";
                    default: "You need to pull the string, but only when the chicken is inside the trap.";
                }
            }
        }
        ! Use the key to lower the altar
        if (sun_key in player || sun_key in satchel || sun_key in sun_key_hole) {
            switch (++Hints.LowerColumn) {
                1: "Time to use the sun key...";
                2: "Usually one inserts a key into a keyhole...";
                3: "Did you notice the hole in the Tomb...";
                default: "Insert the key in the hole and turn it.";
            }
        }
    }
    ! Taking the treasure
    if (stone_altar in Tomb && golden_egg in stone_altar) {
        switch (++Hints.GoldEgg) {
            1: "The treasure may be booby trapped...";
            2: "The treasure rests on a pressure sensitive surface...";
            3: "Before taking the treasure, put something heavy on the altar
            to prevent the pressure plate from activating...";
            4: "You may find something heavy in the Temple...";
            default: "Put the stone egg on the altar, then take the golden egg.";
        }
    }
    ! Player has the prize
    if (golden_egg in player || golden_egg in satchel) {
        "It seems you have the treasure already, congrats!
        Guess you won't be needing that hint then. ";
    }
    ! No more hints
    if (~~Hints.Printed) {
        "I don't have any hints for you right now, try exploring a bit more. ";
    }
    !print "^";
];

Verb meta 'hint' * -> Hint;
Verb meta 'hints' = 'hint';