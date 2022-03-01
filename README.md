# Pokemon-Type-Ranking
A project to try and rank pokemon types.

## Principle
When looking at the [pokemon type chart](https://upload.wikimedia.org/wikipedia/commons/9/97/Pokemon_Type_Chart.svg) of strengths, weaknesses and immunities, we can almost see it as the payoff matrix of a simultaneous-turn game like rock, paper, scissors.

While in chess, players alternate turns, in simultaneous-turn games like rock paper scissors both players play at the same time and a "payoff matrix" can be defined as follows:
|          | Rock | Paper | Scissors |
|----------|------|-------|----------|
| Rock     | 0    | -1    | 1        |
| Paper    | 1    | 0     | -1       |
| Scissors | -1   | 1     | 0        |

where 1 represents winning, -1 represents losing and 0 represents a draw. Game-theory of simultaneous-turn games tells us that there exists a "Nash Equilibrium" of optimal play out of which no player has any incentive to deviate. The Nash equilibrium would colloquially be referred to as "the meta" by players.

However, the pokemon type chart does not directly give the outcomes of games, playing fire against grass does not give "2 points", one also has to take into account the 0.5 effectiveness of grass against fire. A natural thing to look at in this case is Effectiveness_Fire_Grass/Effectiveness_Grass_Fire. That way, playing fire against grass gives "4 points" thanks to both an attack and a defensive advantage but matchups like dragon vs dragon correctly give a ratio of 1. However, it is arbitrary to say that playing fire against grass is twice as good as, say, electric against water. A lot of questions are also raised when looking at type immunities which give an infinite effectiveness ratio, whereas in real play, off-type moves will simply be used to bypass the immunity at the cost of STAB (same-type attack bonus). In a first approximation, I choose to represent effectiveness ratios above 1 as a winning matchup, effectiveness ratios of 1 as a drawing matchup and effectiveness ratios below 1 as a losing matchup. As a tie-breaking mechanism winning/losing matchups with an effectiveness ratio strictly above 2/below 0.5 will be represented as 1.01/-1.01 respectively. This choice gives us the following payoff matrix

|          | Normal | Fire  | Water | Grass | Electric | Ice  | Fighting | Poison | Ground | Flying | Psychic | Bug   | Rock  | Ghost | Dragon | Dark  | Steel | Fairy |
|----------|--------|-------|-------|-------|----------|------|----------|--------|--------|--------|---------|-------|-------|-------|--------|-------|-------|-------|
| Normal   | 0      | 0     | 0     | 0     | 0        | 0    | -1       | 0      | 0      | 0      | 0       | 0     | -1    | 0     | 0      | 0     | -1    | 0     |
| Fire     | 0      | 0     | -1.01 | 1.01  | 0        | 1.01 | 0        | 0      | -1     | 0      | 0       | 1.01  | -1.01 | 0     | -1     | 0     | 1.01  | 1     |
| Water    | 0      | 1.01  | 0     | -1.01 | -1       | 1    | 0        | 0      | 1      | 0      | 0       | 0     | 1     | 0     | -1     | 0     | 1     | 0     |
| Grass    | 0      | -1.01 | 1.01  | 0     | 1        | -1   | 0        | -1.01  | 1.01   | -1.01  | 0       | -1.01 | 1     | 0     | -1     | 0     | -1    | 0     |
| Electric | 0      | 0     | 1     | -1    | 0        | 0    | 0        | 0      | -1.01  | 1.01   | 0       | 0     | 0     | 0     | -1     | 0     | 1     | 0     |
| Ice      | 0      | -1.01 | -1    | 1     | 0        | 0    | -1       | 0      | 1      | 1      | 0       | 0     | -1    | 0     | 1      | 0     | -1.01 | 0     |
| Fighting | 1      | 0     | 0     | 0     | 0        | 1    | 0        | -1     | 0      | -1.01  | -1.01   | 0     | 1.01  | -1.01 | 0      | 1.01  | 1     | -1.01 |
| Poison   | 0      | 0     | 0     | 1.01  | 0        | 0    | 1        | 0      | -1.01  | 0      | -1      | 1     | -1    | -1    | 0      | 0     | -1.01 | 1.01  |
| Ground   | 0      | 1     | -1    | -1.01 | 1.01     | -1   | 0        | 1.01   | 0      | -1.01  | 0       | -1    | 1.01  | 0     | 0      | 0     | 1     | 0     |
| Flying   | 0      | 0     | 0     | 1.01  | -1.01    | -1   | 1.01     | 0      | 1.01   | 0      | 0       | 1.01  | -1.01 | 0     | 0      | 0     | -1    | 0     |
| Psychic  | 0      | 0     | 0     | 0     | 0        | 0    | 1.01     | 1      | 0      | 0      | 0       | -1    | 0     | -1    | 0      | -1.01 | -1    | 0     |
| Bug      | 0      | -1.01 | 0     | 1.01  | 0        | 0    | 0        | -1     | 1      | -1.01  | 1       | 0     | -1    | -1    | 0      | 1     | -1    | -1    |
| Rock     | 1      | 1.01  | -1    | -1    | 0        | 1    | -1.01    | 1      | -1.01  | 1.01   | 0       | 1     | 0     | 0     | 0      | 0     | -1.01 | 0     |
| Ghost    | 0      | 0     | 0     | 0     | 0        | 0    | 1.01     | 1      | 0      | 0      | 1       | 1     | 0     | 0     | 0      | -1.01 | 0     | 0     |
| Dragon   | 0      | 1     | 1     | 1     | 1        | -1   | 0        | 0      | 0      | 0      | 0       | 0     | 0     | 0     | 0      | 0     | -1    | -1.01 |
| Dark     | 0      | 0     | 0     | 0     | 0        | 0    | -1.01    | 0      | 0      | 0      | 1.01    | -1    | 0     | 1.01  | 0      | 0     | 0     | -1.01 |
| Steel    | 1      | -1.01 | -1    | 1     | -1       | 1.01 | -1       | 1.01   | -1     | 1      | 1       | 1     | 1.01  | 0     | 1      | 0     | 0     | 1.01  |
| Fairy    | 0      | -1    | 0     | 0     | 0        | 0    | 1.01     | -1.01  | 0      | 0      | 0       | 1     | 0     | 0     | 1.01   | 1.01  | -1.01 | 0     |

## Results

We can then solve the game using algorithms like fictitious play, or in this case, simplex to find the following Nash Equilibrium

| Type     | Frequency | Value     |
|----------|-----------|-----------|
| Steel    | 0.178338  | 0         |
| Dragon   | 0.178338  | 0         |
| Water    | 0.177743  | 0         |
| Ground   | 0.117711  | 0         |
| Fairy    | 0.115374  | 0         |
| Ghost    | 0.115374  | 0         |
| Grass    | 0.058855  | 0         |
| Electric | 0.058267  | 0         |
| Dark     | 0         | 0         |
| Ice      | 0         | -0.00296  |
| Fighting | 0         | -0.054718 |
| Flying   | 0         | -0.058855 |
| Fire     | 0         | -0.12063  |
| Normal   | 0         | -0.178338 |
| Bug      | 0         | -0.231931 |
| Poison   | 0         | -0.238411 |
| Psychic  | 0         | -0.293712 |
| Rock     | 0         | -0.535608 |

It is interesting to see that popular types like Steel, fairy, water and dragon rank so highly. Many questions remain open because here we have considered a game of 1 pokemon vs 1 pokemon, whereas the actual game uses teams of 6 pokemon (depending on the format). Furthermore, dual-typing has been completely neglected.

For curiosities sake, here are the equivalent matrices for gen 2

| Type     | Frequency | Value     |
|----------|-----------|-----------|
| Dragon   | 0.214791  | 0         |
| Steel    | 0.143313  | 0         |
| Fighting | 0.141894  | 0         |
| Ground   | 0.107399  | 0         |
| Water    | 0.107392  | 0         |
| Ghost    | 0.105614  | 0         |
| Flying   | 0.071841  | 0         |
| Electric | 0.071838  | 0         |
| Ice      | 0.035917  | 0         |
| Psychic  | 0         | -0.105614 |
| Grass    | 0         | -0.177804 |
| Dark     | 0         | -0.179955 |
| Bug      | 0         | -0.214087 |
| Poison   | 0         | -0.216939 |
| Fire     | 0         | -0.249635 |
| Normal   | 0         | -0.285207 |
| Rock     | 0         | -0.395447 |

and gen 1

| Type     | Frequency | Value     |
|----------|-----------|-----------|
| Dragon   | 0.266579  | 0         |
| Psychic  | 0.199932  | 0         |
| Rock     | 0.1996    | 0         |
| Bug      | 0.100463  | 0         |
| Fighting | 0.099468  | 0         |
| Water    | 0.033823  | 0         |
| Ice      | 0.033823  | 0         |
| Ground   | 0.033156  | 0         |
| Flying   | 0.033156  | 0         |
| Ghost    | 0         | -0.001005 |
| Grass    | 0         | -0.168108 |
| Electric | 0         | -0.232756 |
| Normal   | 0         | -0.299069 |
| Poison   | 0         | -0.333551 |
| Fire     | 0         | -0.400202 |