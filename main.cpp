#include <iostream>
#include <vector>
#include <algorithm>
#include <random>




  int howManyPlayers{};
  int amountOfTurns = 0;
   std::vector<int> usableDeck;
   std::vector<int> discardedDeck;
    std::random_device rd; 
    std::default_random_engine rng = std::default_random_engine{rd()};





inline  int absoluteVale(const int& number) {
  int otherNumber  = number;  
  if (number < 0) {
    otherNumber *= -1;
  }
  return otherNumber;
}

template <typename t>
void displayList(t &list) {
  if (std::is_array<t>::value) {
    for (int i =0; i < sizeof(list)/sizeof(list[0]); i++) {
        std::cout << list[i] << "\n";
    }
  } else {
    for (int i =0; i < list.size(); i++) {
        std::cout << list[i] << "\n";
    }
  } 
}

class Player {   
  private:
  bool boolean = false;
  int howManyTimes{0};
  int previosNumber{0};

  bool deckIsSorted() {
    for (int i = 1; i < 10; i++) {
      if (deck[i] < deck[i-1]) {
        return false;
      }
    }
    return true;
  }

 public:   
   int turnsUntilWin = 0;
    bool wonGame = false;
    int deck[10];
    void biggestGoesFirstStrategy() {
         int i = 0;
      int Displacement = 0;


   for  (int n =0; n < 10; n++) {
  if (absoluteVale(deck[n]-((n+1)*6))>Displacement && ((absoluteVale(deck[n+1]-((n+2)*6))>5 || deck[n] > deck[n+1]) || (absoluteVale(deck[n-1]-((n)*6))>5 || deck[n-1] > deck[n]))) {
    if (howManyTimes < 10 || n != previosNumber || n == 0) {
          Displacement = absoluteVale(deck[n]-((n+1)*6));
           i = n;
    } else {
            Displacement = absoluteVale(deck[n-1]-((n)*6));
           i = n-1;
           howManyTimes = 0;
          }
        }
      }
    if (i == previosNumber) {
          howManyTimes++;
        }
        
    previosNumber = i;
if (!discardedDeck.empty()  && (absoluteVale(discardedDeck[0]-((i+1)*6)) <5) && (discardedDeck[0] < deck[i+1] ||  (absoluteVale(deck[i+1]-((i+2)*6)) <5))) {
      Displacement = deck[i];
      deck[i] = discardedDeck[0];
      discardedDeck[0] = Displacement;
    } else {
      discardedDeck.insert(discardedDeck.begin(),deck[i]);
      deck[i] = usableDeck[0];
      usableDeck.erase(usableDeck.begin());
    }
    turnsUntilWin++;

    }

    void tunnelStrategy() {
      int Displacement = 0;
      int i = 0;
      int firstNumber = 0;
      int secondNumber = 0;
      for (i = 0; i < 10; i++) {
        if (absoluteVale(deck[i]-((i+1)*6))< 5) {
          if (!boolean) {
          firstNumber = i;
          break;
        }
       }  else {
          boolean = true;
       }
      }
      if (i == 10) {
          biggestGoesFirstStrategy();
          return;
        }
      for (i = 0; i < 10; i++) {
        if (absoluteVale(deck[i]-((i+1)*6))< 5 && i != firstNumber && i != firstNumber - 1 && i != firstNumber + 1) { // makes sure i is not the first number
          secondNumber = i;
          break;
        }
      }
      if (i == 10) {
          biggestGoesFirstStrategy();
          return;
        }

      if (firstNumber > secondNumber) {
        i = secondNumber;
        secondNumber = firstNumber;
        firstNumber = i;
      }
      
      for (i = firstNumber+1; i < secondNumber; i++) {
        if (deck[i] < deck[i-1] || deck[i]+(secondNumber-i) > secondNumber) {
          if (!discardedDeck.empty() && discardedDeck[0] > deck[i] && discardedDeck[0]+(secondNumber-i) < secondNumber) {
                Displacement = deck[i];
              deck[i] = discardedDeck[0];
              discardedDeck[0] = Displacement;
          } else {
                    discardedDeck.insert(discardedDeck.begin(),deck[i]);
                deck[i] = usableDeck[0];
                usableDeck.erase(usableDeck.begin());
          }
          break;
        }
      }
      if (i == secondNumber) {
        boolean = true;
      }

      turnsUntilWin++;
    }

    void replacementStrategy() {
      int i = 0;
      int Displacement = 0;
      if (!discardedDeck.empty()) {


        i = discardedDeck[0] / 6;
         if (discardedDeck[0] % 6 < 3 && i != 0) {
          i-=1;
        } 
        else if (absoluteVale(deck[i]-((i+1)*6)) < 5  && discardedDeck[0] < deck[i] && i != 0) {
          i-=1;
       } else if (absoluteVale(deck[i]-((i+1)*6)) < 5  && discardedDeck[0] > deck[i] && i != 9) {
          i +=1;
        }

 

        if (absoluteVale(deck[i]-((i+1)*6)) > 5) {
              Displacement = deck[i];
              deck[i] = discardedDeck[0];
              discardedDeck[0] = Displacement;
              turnsUntilWin++;
              return;
        }
      } 
       biggestGoesFirstStrategy();
    }


    void pickCard() {   
      wonGame = deckIsSorted();
      if (usableDeck.empty()) {
        usableDeck = discardedDeck;
        discardedDeck.clear();
        std::shuffle(usableDeck.begin(),usableDeck.end(),rng);
      }
    }
};









int main() {
  const int amountOfPlayers = 3;
  const int amountOfGames = 1000000;
       std::vector <Player> players;
    std::vector <int> gamesWon{};
    Player samplePlayer;
    for (int b = 0; b < amountOfPlayers; b++) {
      players.push_back(samplePlayer);
      gamesWon.push_back(0);
    }

  for (long int a = 0; a < amountOfGames; a++) {
    usableDeck.clear();
    discardedDeck.clear();
    for (int i = 1; i < 61; i++) { // fills the deck with number 1-60
      usableDeck.push_back(i);
    }
    std::shuffle(usableDeck.begin(),usableDeck.end(),rng);
  for (int b = 0; b < amountOfPlayers; b++) {
    for (int i = 0; i < 10; i++) {
        players[b].deck[i] = usableDeck[0];
        usableDeck.erase(usableDeck.begin());
    }
  }
  bool breakLoop = false;
    while (true) {
      breakLoop = false;
      for (int b = 0; b < amountOfPlayers; b++) {
       // the following commented out code is an example of how to set up a specific matchup , this makes replacementStrategy vs  tunnelStrategy vs biggestGoesFirstStrategy
       /* if (b == 2) {
          players[b].biggestGoesFirstStrategy();
        } else if (b == 1){
          players[b].tunnelStrategy();
        } else if (b == 0){
          players[b].replacementStrategy();
        } */
        players[b].pickCard();

        if (players[b].wonGame) {
          gamesWon[b]++;
          amountOfTurns += players[b].turnsUntilWin;
          breakLoop = true;
          break;
        }
      }
      if (breakLoop) {
        for (int b = 0; b < amountOfPlayers; b++) {
            players[b].turnsUntilWin = 0;
         }
        break;  
      }
  }
      std::cout << a << "\n";

  }


    for (int b = 0; b < amountOfPlayers; b++) {
      std::cout << "Player " << b+1 << ": " << gamesWon[b] << "\n";
    }
    std::cout << "Average amount of turns is: " << amountOfTurns / amountOfGames << "\n";
   return 0;
}