
## **13453 - Stack Invader**
### **Description**
*\*\*\**

*3/20 Update: Added another example to clearify the order of enemy effects and the bullets effects in the supplementary information, which is marked red. Slightly modified the supplementary information to make it more clear.*

*3/15 Update: Supplementary information about applying enemy effects when shooting special bullets is added in the description, marked with red color.*

*3/14 Update: An additional line has added to the descripition of FRONT\_ROW in the Ouptut section in order to clearify the level you need to print.*

*\*\*\**

![](https://github.com/Wennyyyy/2022_DSC/blob/main/docs/img/HW1_001.png)


### **Brief:**
This is a partial judge problem.

This homework is inspired by the classic arcade game Space Invader, but the rules and the mechanics are different from the original game.

Students need to implement an internal control system that monitoring the enemies’ positions. The game logic is modified and simplified to make sure the problem can be solved with C/C++ basic and the understanding of the queue and stack.
### **Problem Detail:**
In this homework, a player can shoot an enemy and the enemy will be killed. There are 5 different kinds of enemies, represented by number 1–5. The enemies will be placed in a grid. Their positions along with their types will be specified in the input.

![](https://github.com/Wennyyyy/2022_DSC/blob/main/docs/img/HW1_002.png)

The player movements (shooting bullets or querying front row enemies) will also be specified in the input. Students need to print out the remaining enemies’ location after several moves of the player. The detailed I/O will be clarified in the end of this section.

A player can fire normal bullets or special bullets. A normal bullet just kills an enemy that is closest to the player (bottom) in a column without any other effects but the ammo is unlimitied. Special bullets, consists of shotgun shells **<SG>**, penetration bullets **<P>**, and super bullets **<SB>**, are limited. Each one of them has their own effect and can be obtained by killing different type of enemy. A player does not have any special bullets in the beginning of the game. Once a player earned some special bullets, the player can shoot them one by one in the same order as the bullets are collected, which means the player cannot decide which bullets to be fired first.

Notice that, if a bullet is shot at a column that is empty, nothing will happen.


#### **Enemies types and special bullets types:**
There are 5 types of enemies. When they are killed by a player, they will generate different effects.

1. **Enemy #1**: A normal enemy, and it dies when a player shoots it. Nothing special will happen.
2. **Enemy #2**: Killing an enemy #2 will give the player a shotgun shell **<SG>.**
3. **Enemy #3**: Killing an enemy #3 will give the player a penetration bullet **<P>.**
4. **Enemy #4**: Killing an enemy #4 will give the player a super bullet **<SB>.**
5. **Enemy #5**: If a player kills an enemy #5 located in column numbered **x**, after the enemy dies, ∀ column whose number **y** ∈ [**x-2,** **x+2**] will generate three normal enemies (#1). If **y** < 0 or **y** is larger than the maximum column number in the game stage, ignore the column. Let the maximum level that at least 1 enemy exists at in these 5 columns be **p**, the 3 new enemies will be placed at level **p+1, p+2, p+3** for each column.

(See the example below, the **#5** enemy is killed in the column **2**, so the column **2-2 to 2+2**, i.e. column **0 to 4**, will generate 3 new #1 enemies for each one of them. The maximum level that at least 1 enemy exists in these 5 columns is **max(4, 3, 1, 2, 3) = 4**. So the position to generate the enemies will be level **5, 6** and **7.**

​         ![](https://github.com/Wennyyyy/2022_DSC/blob/main/docs/img/HW1_003.png)

​         (Here, the SHOOT 2 above the left red arrow means shooting the column 2 with a normal bullet, the details will be explained later.)


There are 3 different kinds of special bullets.

1. **Shotgun shell <SG>**: It allows the player to aim at a column numbered **x** and hit 5 front enemies from 5 columns (**x-2** to **x+2**) with one shot. Firing a <SG> equals firing 5 successive normal bullets to 5 different columns, one shot for each one of them. The smaller numbered column will be firing first. For example, if a player aims at column 3, the player will end up hitting column 1 to 5. But if a player aims at column 1, the player will end up only hitting column 0 to 3.     

​         ![](https://github.com/Wennyyyy/2022_DSC/blob/main/docs/img/HW1_004.png)

(Here, the SPECIAL 2 above the left red arrow means shooting the column 2 with a special bullet.)

​         If a player kills multiple enemies so that the player earns multiple special bullets with one **<SG>** shot, the bullet which is earned from an enemy belongs to a smaller-numbered column will be fired first.

2. **Penetration Bullet <P>**: It can kill 3 front enemies in a columns with one shot. It equals firing 3 successive normal bullets to a column.

​         ![](https://github.com/Wennyyyy/2022_DSC/blob/main/docs/img/HW1_005.png)

If a player kills multiple enemies so that the player earns multiple special bullets with one **<P>** shot, the bullet which is earned from an enemy that is closer to the player will be fired first.

3. **Super bullet <SB>**: It can kill the same kind of enemy in a single column as many as possible until the front is a different kind of enemy. It equals firing multiple successive normal bullets to a column until a different type of enemy is at the front.

​         ![](https://github.com/Wennyyyy/2022_DSC/blob/main/docs/img/HW1_006.png)

Notice: Because a special bullet shot can be considered as successive normal bullets shot, when a special bullet is going to hit multiple enemies, the enemies will be killed one by one. Their effects will be applied to the game immediately after they are shot by a normal bullet that is derived from a special bullet. Here are some supplementary information and examples.

As mentioned earlier, a <SG> shot is equal to 5 normal bullet shots. So if two #5 enemies are hit in these 5 shots, after the first one is hit, it will generate new enemies immediately. And then, when the later shot hit the other #5 enemy, it will use the new state of the game to decide the max level. (That means the later #5 enemy might generate some #1 enemies in front of the #1 enemies generated by the earlier #5 enemy)

Also, It is possible for a <SG> to hit a #1 enemy which is just generated by a #5 enemy killed by the same <SG>.
​         ![](https://github.com/Wennyyyy/2022_DSC/blob/main/docs/img/HW1_007.png)



-----
### **Animation Example**
![](https://github.com/Wennyyyy/2022_DSC/blob/main/docs/img/HW1_008.jpg)
### **Input**
` `The first line contains three integers.

1. ` `Integer ***W***, representing the number of columns on the stage;
1. Integer ***H***, representing the maximum level that an enemy might exists in each column in the initial state;
1. Integer ***M***, representing the number of movements a player will do.

Starts from the second lines, there are ***H*** lines that each of them contains ***W*** characters. The ***W*** characters are separated by a space between each two of them. Every character represents an enemy and its type. So in the initial state, there will be at most ***W*** x ***H*** enemies. We use a underline “**\_**” to represent the empty space in the grid of the stage that doesn't contain any enemy.

After the lines above, the following ***M*** lines representing the movements. Each line starts with an instruction string ***Si***. And the string will only be one of the following: **SHOOT, SPECIAL, FRONT\_ROW.**

If ***Si*** is **SHOOT,** it means the player wants to fire a normal bullet. ***Si*** is followed by a space and an integer ***Ci*** which indicates the column that the player is aiming at. If ***Ci*** is not a valid column, simply skip this turn.

If ***Si*** is **SPECIAL,** it means the player wants to fire a special bullet. ***Si*** is followed by a space and an integer ***Ci*** which indicates the column that the player is aiming at. If ***Ci*** is not a valid column or the player doesn't have any special bullets, simply skip this turn. 

If ***Si*** is **FRONT\_ROW**, It means the player wants to check the highest level of all the columns that contains at least 1 enemy and see the type of the enemy located at that level in every single column. There is no more following input in the same line.

It is guaranteed that:

Test case #1: Sample Input

Test case #2 ~ #7: ***W*** ≤ 10, ***H*** ≤ 10, ***M*** ≤ 102, ***E*** ≤ 102

Test case #8 ~ #9: ***W*** ≤ 105, ***H*** ≤ 105, ***M*** ≤ 104, ***E*** ≤ 106

Test case #10: ***W*** ≤ 106, ***H*** ≤ 106, ***M*** ≤ 2x106, ***E*** ≤ 106

- ***W*** represents the number of the columns a stage contains.
- ***H*** represents the maximum level that an enemy might exists at in the initial state.
- ***M*** represents the number of the movements a player will do.
- ***E*** represents the maximum number of the enemies that will simultaneously exist in the stage through the whole process.
### **Output**
If a player is doing **SHOOT** or **SPECIAL**, there’s no need to print anything.

If a player checks **FRONT\_ROW**, you need to print a string “**FRONT\_ROW, LEVEL:**” followed by a integer ***Lf*** which represents the maximum level that contains at least 1 enemy. Noted, that the maximum level you need to print is based on the current state of the game stage, NOT the initial state. After that, finish the line with a new line symbol. If there is not any enemy existing on the stage, the ***Lf*** will be 0.

In the next line, print the type of the enemy at the level ***Lf*** in each column. Separate each enemy by a space. If there isn't enemy existing at the level ***Lf*** for some columns, print a underline “**\_**” to fill the empty slot. Print a new line symbol at the end of the line. Notice that, if the ***Lf*** is 0, you don’t need to print anything.

After all ***M*** movements are done, you need to print a string “**END\_RESULT:**”, following by a new line symbol.

Starts from the next line, print the positions and types for each enemy, starts from level 1 to the max level that contains at least 1 enemy. Separate each enemy from the same level by a space and separate each level by a new line symbol. Print a underline “**\_**” to fill the empty slot if no enemy exists at some places. Notice that, if there is not any enemy existing on the stage, you don’t need to print anything.
### **Sample Input**
6 3 10 1 1 1 1 2 1 1 2 1 1 1 1 1 2 3 4 5 1 SHOOT 0 SHOOT 2 FRONT\_ROW SHOOT 4 SPECIAL 3 SHOOT 3 SPECIAL 4 SPECIAL 1 SHOOT 1 SPECIAL 1

### **Sample Output**
FRONT\_ROW, LEVEL:3 \_ 2 \_ 4 5 1 END\_RESULT: 1 1 1 1 2 1 \_ \_ 1 \_ \_ 1 \_ \_ \_ \_ \_ 1 \_ \_ 1 \_ \_ 1 \_ \_ 1 \_ \_ 1 \_ \_ \_ \_ \_ 1 
