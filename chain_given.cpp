#include "chain.h"

/**
 * Given functions for the Chain class.
 *
 * ****WARNING****
 *
 * You should not modify this file.  It is not one of the files
 * you will submit.  We will grade your submission using the
 * original version of this file.
 */

/* no-argument constructor */
Chain::Chain() {
    length_ = 0;
    head_ = NULL;
}

/* Most useful constructor. requires your
 * implementation of Block and insertAfter.
 * Builds a chain out of the blocks in the
 * given image. The blocks we create
 * have width equal to imIn.width()/k
 * (rounded down to an integer)
 * and height equal to imIn.height().
 *
 * @param imIn The image providing the blocks
 * @param k    The number of blocks to extract.
 */
Chain::Chain(PNG & imIn, int k) {
    int w = imIn.width()/k; // width of all blocks
    head_ = NULL;
    length_ = 0;

    Node *p = NULL;
    for( int i=0; i < k; i++ ) {
        Block b;
        b.Build(imIn , i*w, w);
        p = InsertAfter(p, b);
    }
}

/**
 * accessor for the length of the chain.
 */
int Chain::Size() const {
    return length_;
}

/* copy constructor */
Chain::Chain(Chain const& other) {
    length_ = 0;
    head_ = NULL;
    Copy(other);
}

/* assignment operator */
Chain & Chain::operator=(Chain const& rhs) {
    if (this != &rhs) {
        Clear(); // you'll implement clear
        Copy(rhs);
    }
    return *this;
}

/**
 * checks for empty list
 */
bool Chain::Empty() const {
    return head_ == NULL;
}

/**
 * Public function to test the private function swap.
 * Swap the i-th and j-th nodes in the chain.
 * The 0-th node is the head_.
 */
void Chain::TestSwap( int i, int j ) {
    Node *p = head_;
    Node *q = head_;
    for( int a=0; a < i; ++a )
        p = p->next;
    for( int b=0; b < j; ++b )
        q = q->next;
    Swap(p,q);
}

/**
 * scramble : randomly permute the nodes in the chain.
 */
void Chain::Scramble() {
    if ( head_ == NULL ) return;
  
    Node *p = head_;
    for( int k=length_; k > 1; k-- ) {
        int j = rand() % k; // j = 0..k-1
        Node *q = p;
        for( int i=0; i<j; ++i )
            q = q->next;
        Swap(p,q);
        // Node q is now in the position of Node p.  We need set p to q->next
        // to allow the for-loop to continue properly.
        p = q->next;
    }
}
