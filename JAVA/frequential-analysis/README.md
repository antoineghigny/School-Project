# SECG4 - Frequential analysisDossier

## Group 
- 56359 - Antoine Ghigny  
- 57034 - Massimo Russo

## Explication

This app has implemented Caesar's cryptanalysis and
Vigenère figures, with frequency analysis.

- It is possible to encode and decode a text using a key.  
- But also to decode a cyphered text without the key.

```shell
│   data.txt
│   README.md
│
└───td1
    │   answer.txt
    │   nbactions.xml
    │   pom.xml
    │
    └───src
        ├───main
        │   ├───java
        │   │   ├───command
        │   │   │       Command.java
        │   │   │       Crack.java
        │   │   │       Cypher.java
        │   │   │       Decypher.java
        │   │   │       Help.java
        │   │   │
        │   │   ├───controller
        │   │   │       Controller.java
        │   │   │
        │   │   ├───factory
        │   │   │       Factory.java
        │   │   │
        │   │   ├───main
        │   │   │       Main.java
        │   │   │
        │   │   ├───model
        │   │   │       Model.java
        │   │   │       Preprocess.java
        │   │   │
        │   │   └───view
        │   │           View.java
        │   │
        │   └───resources
        └───test
            └───java
```
## How to launch the app
These compilation and execution commands are to be executed in the head directory
```shell
javac -d .\td1\src\main\java\  -cp .\td1\src\main\java\   .\td1\src\main\java\main\*.java

java -cp  .\td1\src\main\java\   .\td1\src\main\java\main\main.java
```
![alt text](https://media.discordapp.net/attachments/934924497767792671/957363573309468732/unknown.png?width=720&height=343)

## How to use the app
To __perform the Vigenère cryptanalysis__,
enter the following command in a shell: 
- follow the example below
```shell
ENCODE&MESSAGE&KEY&VIGENERE
```
To __perform the Caesar cryptanalysis__,
enter the following command in a shell:  
- follow the example below
```shell
ENCODE&MESSAGE&1&CAESAR
ENCODE&MESSAGE&2&CAESAR
ENCODE&MESSAGE&3&CAESAR
...
``` 
To __decode the Vigenère cryptanalysis__,
enter the following command in a shell:
- follow the example below
```shell
DECODE&MESSAGE&KEY&VIGENERE
```
To __decode the Caesar cryptanalysis__,
enter the following command in a shell:
- follow the example below
```shell
DECODE&MESSAGE&KEY&CAESAR
```
And to __decode a cryptanalysis without knowing the method or the key__, use the following command.
```shell
CRACK&MESSAGE
```
- __MESSAGE__ is the message you want to encode or decode.
- __KEY__ is the key you want to use (An integer for Caesar and a String for Vigenere)
- __METHOD__ You have the right to indicate "CAESAR" or "VIGENERE" depending on the encryption method you wish to use.


### Here are some examples of the above methods

Here are some examples of above methods

- Encode under vigenere:
```shell
ENCODE&Too cultivated use solicitude frequently. Dashwood likewise up consider continue entrance ladyship oh. Wrong guest given purse power is no. Friendship to connection an am considered difficulty. Country met pursuit lasting moments why calling certain the. Middletons boisterous our way understood law. Among state cease how and sight since shall. Material did pleasure breeding our humanity she contempt had. So ye really mutual no cousin piqued summer result.&ALOPIUNB&VIGENERE
```
Answer : 
```
TZCRCFGJVLHTLOFFSZZXKCGVDPTGMKHFNEZNLUFIWZCSTCXFWTGTCJPPNDWSMLPPNEWCCYROTCOCKYYBDJGWQJBIWCCCOAHFSEUXDYAQUCGTXIJFRTGCWZEJEYRHPCCUONCCVYPUIZBPVUZDOYGXLYEFDOWUNCPVLEMRWOAURJATBJHSSFWITUFUIYUBWGROTDKWGWNMLTBVKYEUATBIPYZJDOZTBIATBZWHBYEPUDCJZQNZUYRTZMGPOOZPEUZPNRGIINRDELGTPIJBNOGXOBGTIYQTABNMLXOIMLVBLOWSXFRBSFFTJLRFDTBVWOEIUXOCQNLTHPQDVNRNPEVPLMBZECSPTFLNUEIPTHBDOFGXVJVRUPRHCGZFRCSHCFG
```
- Crack : 
```shell
CRACK&TZCRCFGJVLHTLOFFSZZXKCGVDPTGMKHFNEZNLUFIWZCSTCXFWTGTCJPPNDWSMLPPNEWCCYROTCOCKYYBDJGWQJBIWCCCOAHFSEUXDYAQUCGTXIJFRTGCWZEJEYRHPCCUONCCVYPUIZBPVUZDOYGXLYEFDOWUNCPVLEMRWOAURJATBJHSSFWITUFUIYUBWGROTDKWGWNMLTBVKYEUATBIPYZJDOZTBIATBZWHBYEPUDCJZQNZUYRTZMGPOOZPEUZPNRGIINRDELGTPIJBNOGXOBGTIYQTABNMLXOIMLVBLOWSXFRBSFFTJLRFDTBVWOEIUXOCQNLTHPQDVNRNPEVPLMBZECSPTFLNUEIPTHBDOFGXVJVRUPRHCGZFRCSHCFG
```
Answer : 
```shell
TOOCULTIVATEDUSESOLICITUDEFREQUENTLYDASHWOODLIKEWISEUPCONSIDERCONTINUEENTRANCELADYSHIPOHWRONGGUESTGIVENPURSEPOWERISNOFRIENDSHIPTOCONNECTIONANAMCONSIDEREDDIFFICULTYCOUNTRYMETPURSUITLASTINGMOMENTSWHYCALLINGCERTAINTHEMIDDLETONSBOISTEROUSOURWAYUNDERSTOODLAWAMONGSTATECEASEHOWANDSIGHTSINCESHALLMATERIALDIDPLEASUREBREEDINGOURHUMANITYSHECONTEMPTHADSOYEREALLYMUTUALNOCOUSINPIQUEDSUMMERRESULT
```
