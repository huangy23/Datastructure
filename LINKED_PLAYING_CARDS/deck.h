#include "playing_card.h"
#include "node.h"

// ==================================================================================
// prototypes for provided functions (implemented in main.cpp)
// ==================================================================================

bool SanityCheckPrimary(Node* top);
bool SanityCheckSorted(Node* first);
Node* CreateDeck(int numCards);
void DeckPushBackCard(Node* &deck, const std::string& suit, int num);
void PrintDeckPrimary(const std::string &description, Node* deck);


// ==================================================================================
//
// Write all the prototypes for the your functions here
// (they will be implemented in deck.cpp)
//
// NOTE: These are standalone functions, not part of a class.

bool SamePrimaryOrder(const Node* deck1, const Node* deck2); 
bool ReversePrimaryOrder(const Node* deck1, const Node* deck2); 
Node* SortHand(Node* deck);
void PrintDeckSorted(const std::string &description, Node* deck);
void Deal(Node* &deck,Node* hands[], int, const std::string &des, int each);
int DeckSize(const Node* deck);
Node* CopyDeck(const Node* deck);
void CutDeck(Node* &deck, Node* &top, Node* &bottom, const std::string&);
Node *Shuffle(Node *&top_head, Node *&bottom_head, const std::string &command);
void DeleteAllCards(Node* &deck);


// You may include additional helper functions as necessary
// All of your code must be in deck.h and deck.cpp
//
// ==================================================================================


