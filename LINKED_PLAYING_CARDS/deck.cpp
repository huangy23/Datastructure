// ==================================================================================
// Implement all functions that you listed by prototype in deck.h
// You may include additional helper functions as necessary
// All of your code must be in deck.h and deck.cpp
//
// NOTE: These are standalone functions, not part of a class.
// ==================================================================================

#include <iostream>
#include <cassert>
#include "playing_card.h"
#include "node.h"
#include "deck.h"

//===========================================================================
// Count and return Decksize
//===========================================================================
int DeckSize(const Node* deck) {
    int count = 0;
    if (deck->after == NULL)
    {
        count += 1;
    }
    if (deck == NULL)
    {
        count = 0;
    }
    while (deck->after != NULL)
    {
        deck = deck->after;
        count += 1;
    }
    count += 1;

    return count;
}

//===========================================================================
// Copy the orignal deck and return the new one
//===========================================================================
Node* CopyDeck(const Node* deck) {
    Node *newdeck = NULL;
    while(deck) { //for every node in the original deck
        const PlayingCard& playingCard = deck->getCard();
        const std::string& suit = playingCard.getSuit();
        int card = playingCard.getCard();
        DeckPushBackCard(newdeck, suit, card);
        deck = deck->after; //nexe one
    }
    return newdeck;
}

//===========================================================================
// Cut the deck to two small almost same size decks
//===========================================================================
void CutDeck(Node* &deck, Node* &top, Node* &bottom, const std::string&) {
    top = deck;
    int count = DeckSize(deck);

    Node* p = top;
    for(int i = 0; i < count/2; ++i) {
        p = p->after; //set p to the middle
    }
    bottom = p;
    if(p) {
        p->before->after = NULL;
        p->before = NULL;
    }
    deck = NULL;
}

// =================================================================
// Merge top and bottom together one by one, only support perfect shuffle
// =================================================================
Node* Shuffle(Node* &top, Node* &bottom, const std::string&) {
    int count1 = DeckSize(top);
    int count2 = DeckSize(bottom);
    if(count1 - count2 > 1 || count2 - count1 > 1) {
        return NULL;
    }

    //one is null?
    if(count1 == 0 && count2 == 0) {
        return NULL;
    } 
    if(count1 == 0 && count2 == 1) {
        Node* ret = bottom;
        bottom = NULL;
        return ret;
    }
    if(count1 == 1 && count2 == 0) {
        Node* ret = top;
        top = NULL;
        return ret;
    }
    Node* head = top;
    top = top->after;
    Node* p = head;
    while(top && bottom) {
        bottom->before = p; //append the bottom
        p->after = bottom;
        p = bottom;
        bottom = bottom->after;

        top->before = p; //append the top
        p->after = top;
        p = top;
        top = top->after;
    }

    p->after = bottom;
    if(count1 == count2) {
        bottom->before = p;
    }
    return head;
}

// =================================================================
// Check the deck1 and deck2 are the same order in primary
// =================================================================
bool SamePrimaryOrder(const Node* deck1, const Node* deck2) {
    if(deck1 == NULL && deck2 == NULL) {
        return true;
    }
    if(deck1 == NULL && deck2 != NULL) {
        return false;
    }
    if(deck1 != NULL && deck2 == NULL) {
        return false;
    }
    //check the first card
    const PlayingCard& c1 = deck1->getCard();
    const PlayingCard& c2 = deck2->getCard();
    if(c1 != c2) {
        return false;
    }

    return SamePrimaryOrder(deck1->after, deck2->after); //recusive check
}

// =================================================================
// Check the deck1 and deck2 are the same order in reverse
// =================================================================
bool ReversePrimaryOrder(const Node* deck1, const Node* deck2) {
    //deck1 go to end end
    const Node* deck1_prev = NULL;
    int count = 0;
    for(deck1_prev = NULL; deck1 != NULL; deck1 = deck1->after) {
        deck1_prev = deck1;
        ++count;
    }
    //they should be the same size
    if(count == DeckSize(deck2)) {
        bool ret = true;

        deck1 = deck1_prev;
        while(deck1) {
            if(deck1->getCard() != deck2->getCard()) {
                ret = false;
                break;
            }
            deck1 = deck1->before; //deck1 go before
            deck2 = deck2->after; //deck2 go after
        }
        return ret;
    }
    return false;
}

// =================================================================
// Selection sort in sorted_prev/next, donot change primary order
// =================================================================
Node* SortHand(Node* deck) {
    int count = DeckSize(deck);
    if(count == 0) {
        return NULL;
    }
    bool* flag = new bool[count];
    int i,j;
    for(i = 0; i < count; ++i) {
        flag[i] = false; //false not sorted， true sorted
    }
    
    Node* sorthead = NULL;
    Node* sortCurrent = NULL;
    for(i = 0; i < count; ++i) { //select a smalled every time
        Node* p = deck;
        for(j = 0; j < count; ++j) {
            if(flag[j]) {
                p = p->after;
            } else {
                break;
            }
        }
        //std::cout << "hhh" << p->getCard().getString() << std::endl;
        //assume p is the smallest, check next ones
        Node* p2 = p->after;
        int min = j;
        for(++j; j < count; ++j, p2 = p2->after) {
            //std::cout << "check " << p2->getCard().getString() << std::endl;
            if(!flag[j] && p->getCard() > p2->getCard()) {
                p = p2;
                min = j;
            }
        }
        //std::cout << "I found the smallest" << p->getCard().getString() << std::endl;
        if(!sorthead) {
            sorthead = p;
            sortCurrent = p;
        } else {
            sortCurrent->sorted_next = p;
            p->sorted_prev = sortCurrent;
            sortCurrent = p;
        }
        flag[min] = true;
    }
    delete [] flag;
    return sorthead;
}

// =================================================================
// Deal the card to serveral peoples(save them in hands)
// =================================================================
void Deal(Node* &deck,Node* hands[], int handcount , const std::string &, int each) {
    Node** phand = new Node*[handcount]; //save the tail of the hands
    for(int i = 0; i < handcount; ++i) {
        hands[i] = NULL;
    }
    for(int ee = 0; ee < each; ++ee) { 
        for(int i = 0; i < handcount; ++i) { 
            if(hands[i] != NULL) { //the second to last card
                deck->before = phand[i];
                phand[i]->after = deck;
                deck = deck->after;
                phand[i] = phand[i]->after;
                phand[i]->after = NULL; 
            } else { //the first card
                hands[i] = deck;
                phand[i] = hands[i];
                deck = deck->after; 
                hands[i]->after = NULL;
                hands[i]->before = NULL;
            }
        }
    }
    delete []phand;

    if(deck != NULL) {
        deck->before = NULL;
    }
}

// =================================================================
// Print the deck on one line
// =================================================================
void PrintDeckSorted(const std::string &description, Node* deck) {
    std::cout << description;
    for(; deck != NULL; deck = deck->sorted_next) {
        const PlayingCard card = deck->getCard();
        std::cout << " ";
        std::cout << card.getString();
    }

    std::cout << std::endl;
}

// =================================================================
// Destroy everything
// =================================================================
void DeleteAllCards(Node* &deck) {
    while (deck->after != NULL)
    {
        Node *orign = deck;
        deck = deck->after;
        delete orign;
    }
    delete deck;
}
