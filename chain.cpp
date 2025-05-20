#include "chain.h"
#include <cmath>
#include <iostream>


// PA1 functions
// Complete all of the missing implementation
// and submit this file for grading.

/**
 * Destroys the current Chain. This function should ensure that
 * memory does not leak on destruction of a chain.
 */
Chain::~Chain() {
	Clear();
}

/**
 * Inserts a new node after the node pointed to by p in the
 * chain (so p->next is the new node) and returns a pointer to
 * the newly created node.
 * If p is NULL, inserts a new head node to the chain.
 * This function **SHOULD** create a new Node and increase length_.
 *
 * @param p = The new node should be pointed to by p->next.
 *            If p is NULL, the new node becomes the head of the chain.
 * @param ndata = The data to be inserted.
 */
Chain::Node * Chain::InsertAfter(Node * p, const Block &ndata) {
    Node* newNode = new Node(ndata);
    length_++;
	if (p == NULL) {
        if (head_ == NULL) {
            head_ = newNode;
        } else {
            newNode->next = head_;
            head_->prev = newNode;
            head_ = newNode;
        }
    } else {
        newNode->prev = p;
        if (p->next != NULL) {
            newNode->next = p->next;
            p->next->prev = newNode;
        }
        p->next = newNode;
    }
    return newNode;
}

/**
 * Swaps the position in the chain of the two nodes pointed to
 * by p and q.
 * If p or q is NULL or p==q, do nothing.
 * Change the chain's head pointer if necessary.
 */
void Chain::Swap(Node *p, Node *q) {
	if (p != NULL && q != NULL && p != q) {
        if (p->next == q) {
            if (p->prev != NULL) {
                p->prev->next = q;
            } else {
                head_ = q;
            }
            if (q->next != NULL) {
                q->next->prev = p;
            }
            p->next = q->next;
            q->next = p;
            q->prev = p->prev;
            p->prev = q;
        } else if (q->next == p) {
            if (q->prev != NULL) {
                q->prev->next = p;
            } else {
                head_ = p;
            }
            if (p->next != NULL) {
                p->next->prev = q;
            }
            q->next = p->next;
            p->prev = q->prev;
            p->next = q;
            q->prev = p;
        } else {
            if (p->prev != NULL) {
                p->prev->next = q;
            } else {
                head_ = q;
            }
            if (q->prev != NULL) {
                q->prev->next = p;
            } else {
                head_ = p;
            }
            if (p->next != NULL) {
                p->next->prev = q;
            }
            if (q->next != NULL) {
                q->next->prev = p;
            }

            Node* prevP = p->prev;
            p->prev = q->prev;
            q->prev = prevP;

            Node* nextP = p->next;
            p->next = q->next;
            q->next = nextP;
        }
    }
}

/**
 * Destroys all dynamically allocated memory associated with the
 * current Chain class.
 */
void Chain::Clear() {
	Node* toDelete = head_;
    while (toDelete != NULL) {
        head_ = toDelete->next;
        delete toDelete;
        toDelete = head_;
    }
    head_ = NULL;
    length_ = 0;
}

/**
 * Makes the current object into a copy of the parameter:
 * All member variables should have the same value as
 * those of other, but the memory should be completely
 * independent. This function is used in both the copy
 * constructor and the assignment operator for Chains.
 */
void Chain::Copy(Chain const &other) {
    Node* oldCurr = other.head_;
    Node* nextOld = oldCurr->next;
    if (nextOld != NULL) {
        length_ = 1;
        head_ = new Node(oldCurr->data);
        Node* curr = head_;
        while (nextOld != NULL) {
            curr->next = new Node(nextOld->data);
            curr->next->prev = curr;
            curr = curr->next;
            nextOld = nextOld->next;
            length_++;
        }
    } else {
        length_ = 0;
        head_ = NULL;
    }
}

/**
 * Takes the current chain and renders it into a
 * correctly sized PNG. The blocks in the chain
 * are placed in the image left to right in order
 * of their occurrence in the chain.
 */
PNG Chain::Render() {
    if (head_ == NULL) {
        return PNG();
    }

    Node* curr = head_;
    unsigned int width = 0;
    unsigned int height = curr->data.Height();
    while (curr != NULL) {
        width += curr->data.Width();
        curr = curr->next;
    }

    int x = 0;
    PNG image(width, height);
    curr = head_;
    Block blockData;
    while (curr != NULL) {
        blockData = curr->data;
        blockData.Render(image, x);
        x += blockData.Width();
        curr = curr->next;
    }
    return image;
}

/* Modifies the current chain:
 * 1) Find the node with the first (leftmost) block in the unscrambled
 *    image and move it to the head of the chain.
 *	This block is the one whose closest match (to the left) is the
 *	largest.  That is, the distance (using distanceTo) to this block
 *	is big for all other blocks.
 *	For each block B, find the distanceTo B from every other block
 *	and take the minimum of these distances as B's "value".
 *	Choose the block B with the maximum value over all blocks and
 *	swap its node to the head of the chain.
 *
 * 2) Starting with the (just found) first block B, find the node with
 *    the block that is the closest match to follow B (to the right)
 *    among the remaining blocks, move (swap) it to follow B's node,
 *    then repeat to unscramble the chain/image.
 */
void Chain::Unscramble() {
    if (head_ != NULL && head_->next != NULL) {
        Node* curr = head_;
        Node* first = curr;
        double maxDist = 0;

        while (curr != NULL) {
            Node* compare = head_;
            double minDist = __DBL_MAX__;

            while (compare != NULL) {
                double dist;
                if (compare != curr) {
                    dist = compare->data.DistanceTo(curr->data);
                    if (dist < minDist) {
                        minDist = dist;
                    }
                }
                compare = compare->next;
            }
            if (minDist > maxDist) {
                maxDist = minDist;
                first = curr;
            }
            curr = curr->next;
        }

        Swap(first, head_);
        head_ = first;

        curr = head_;
        Node* nextNode;
        while (curr->next != NULL) {
            nextNode = curr->next;
            double minDist = curr->data.DistanceTo(nextNode->data);
            Node* toSwap = nextNode;
            
            while (nextNode != NULL) {
                double dist = curr->data.DistanceTo(nextNode->data);
                if (dist < minDist) {
                    toSwap = nextNode;
                    minDist = dist;
                }
                nextNode = nextNode->next;
            }
            Swap(curr->next, toSwap);
            curr = curr->next;
        }
    }
}

/**************************************************
* IF YOU HAVE DECLARED PRIVATE FUNCTIONS IN       *
* chain-private.h, COMPLETE THEIR IMPLEMENTATIONS *
* HERE                                            *
**************************************************/

