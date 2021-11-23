# RISIKO Probability Calculator

So my friends can hate me even more :)

## Problem
We're talking about the RisiKo game (a.k.a. 'Risk'). I have N armies in Kamchatka. My opponent has M armies in Alaska. If I attack, what's the probability of conquering the Alaska?  

## How
I do many simulations of the battle. Probability = Number of winning battles / Total number of battles.

## Fun facts
- N vs N it's a suicide for the attacker:  
2 vs 2:   10.7%  
3 vs 3:   10.0%  
4 vs 4:   17.3%  
5 vs 5:   15.9%  
6 vs 6:   14.8%  
...  
10 vs 10 :  12.2%  
20 vs 20 :  7.1%  
50 vs 50 :  1.5%  
100 vs 100 :  0.1%
- According to a famous rule of thumb, the attacker should have twice the armies of the defender for leading a hopeful attack. Let's see if it's true:  
2 vs 1: 41.5%  
4 vs 2: 51.2%  
6 vs 3: 48.4%  
8 vs 4: 52.1%  
10 vs 5: 54.2%  
12 vs 6: 55.4%  
14 vs 7: 56.5%  
16 vs 8: 57.7%  
18 vs 9: 58.4%  
20 vs 10: 59.6%  
...  
50 vs 25: 67.8%  
100 vs 50: 75.3%  
200 vs 100: 83.8%  
500 vs 250: 94.3%  
In conclusion, the rule seems to be more truthful for large battles. 
